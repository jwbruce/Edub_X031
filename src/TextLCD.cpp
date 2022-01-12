/* F/L031K6 + Edubase-V2 TextLCD Library
 * for a 4-bit HD44780 LCD inteface connected via a 74HC595 using SPI
 *
 * based upon the TextLCD mbed library by Simon Ford
 * found at https://os.mbed.com/users/simon/code/TextLCD/
 *
 * Copyright (c) 2007-2010, sford, http://mbed.org
 * Copyright (c) 2020-2021, jwbruce   (jwbruce@tntech.edu)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "TextLCD.h"
#include "TTU_X031.h"
#include "mbed.h"

// Some useful defines to make code more readable
// See HD44780 data sheet and the EduBase schematic for 74HC595 to LCD wiring
#define CMD_BIT     0           /* BIT0 mask for HD44780 commands */
#define RS_BIT      0x01        /* BIT0 mask for HD44780 register select */
#define E_BIT       0x02        /* BIT1 mask for ENABLE BIT */

// constructor
TextLCD::TextLCD(LCDCursor cur) : _cursorState(cur) {

    _maxRows = 2;       // set display size
    _maxColumns = 16;   // set display size
    wait_ms(15);        // Wait 15ms to ensure powered up

    // send data to initialize the LCD into 4-bit mode (via our shift register)
    // send "Display Settings" 3 times (Only top nibble of 0x30 as we've got 4-bit bus)
    for (int i=0; i<3; i++) {
        writeNibble(0x30, CMD_BIT);     // NOTE:  NOT SURE ABOUT THE CMD BIT (0) HERE
        wait_ms(2);                     // this command takes 1.64ms, so wait for it
    }
    writeNibble(0x20,CMD_BIT);   // 4-bit mode
    wait_us(40);                 // datasheet indicates most instructions take 40us

    /* OK, now the display should be alive, so we can send
    ** commands and data "normally" via the member functions
    */
    writeCommand(0x28);          /* set 4-bit data, 2-line, 5x7 font */
    writeCommand(0x06);          /* move cursor right */
    writeCommand(0x01);          /* clear screen, move cursor to home */
    /* turn on display and set cursor as requested */    
    writeCommand(0x0C | _cursorState);
    cls();
}

void TextLCD::setCursor(LCDCursor c) {
    writeCommand(0x0C | c);     // turn on display and set cursor request
    wait_us(1640);              // This command takes 1.64 ms
}

void TextLCD::setCharacter(int row, int column, int c) {
    int a = address(column, row);
    writeCommand(a);
    writeData(c);
}

void TextLCD::cls() {
    writeCommand(0x01);         // cls, and set cursor to 0
    wait_us(1640);              // This command takes 1.64 ms
    setLocation(0, 0);
}

void TextLCD::setLocation(int column, int row) {
    _column = column;
    _row = row;
}

// support _putc() so the .printf() member function works on TextLCD objects
int TextLCD::_putc(int value) {
    if (value == '\n') {
        _column = 0;
        _row++;
        if (_row >= _maxRows) {
            _row = 0;
        }
    } else {
        setCharacter(_row, _column, value);
        _column++;
        if (_column >= _maxColumns) {
            _column = 0;
            _row++;
            if (_row >= _maxRows) {
                _row = 0;
            }
        }
    }
    return value;
}

/* our hardware does not support "reading" the LCD display
** so we have no way to _getc()
**
** We could build a charater "buffer" in our class but that
** takes more memory and code ;-)
*/
int TextLCD::_getc() {
    return -1;
}

/* write 4 bits to LCD controller
**
** We need to assert/deassert /CS_LCD around each SPI
**   nibble write becase /CS_LCD is the register STROBE/CLK
**   on the 74HC595 shift register.  See EduBase_V2 1173D_2 schematic.
*/
void TextLCD::writeNibble(char incoming, unsigned char rs) {
    incoming &= 0xF0;                       /* keep upper nibble (data) */
    rs &= 0x0F;                             /* keep lower nibble (room for RS bit, R/W, and E bits) */
    cs_lcd = 0;                             /* ASSERT /CS_LCD */
    spi.write(incoming | rs);               /* RS = ?, R/W = 0 , E=0 */
    cs_lcd = 1;                             /* DE-ASSERT /CS_LCD which enables 595 parallel outputs */

    cs_lcd = 0;                             /* ASSERT /CS_LCD */
    spi.write(incoming | rs | E_BIT);       /* RS = ?, R/W = 0 , E=1 */
    cs_lcd = 1;                             /* DE-ASSERT /CS_LCD which enables 595 parallel outputs */
    wait_us(100);                           /* short delay to make E pulse */
    
    cs_lcd = 0;                             /* ASSERT /CS_LCD */
    spi.write(incoming);                    /* RS = 0, R/W = 0 , E=0 */
    cs_lcd = 1;                             /* DE-ASSERT /CS_LCD which enables 595 parallel outputs */
}    

void TextLCD::writeCommand(int command) {
    /* RS = 0 for "command writes", so 2nd argument is 0 */
    writeNibble(command & 0xF0, CMD_BIT);    /* upper nibble first */
    writeNibble(command << 4, CMD_BIT);      /* then lower nibble */

    if (command < 4)
        wait_us(1640);              /* command 1 and 2 needs up to 1.64ms */
    else
        wait_us(40);                /* all others 40 us */
}

void TextLCD::writeData(int data) {
    /* RS = 1 for "data writes", so 2nd argument is 1 */
    writeNibble(data & 0xF0, RS_BIT);      /* upper nibble first */
    writeNibble(data << 4, RS_BIT);        /* then lower nibble */
    wait_ms(1);                            /* wait 1ms (CAN WE REMOVE THIS?) */
}

// EduBase-V2 uses HD44780-compatible 16x2 display so hard-code the calculation
int TextLCD::address(int column, int row) {
    return 0x80 + (row * 0x40) + column;
}
