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
 
#ifndef TTU_X031_TEXTLCD_H
#define TTU_X031_TEXTLCD_H
 
#include "mbed.h" 
 
/**  A TextLCD interface for driving 4-bit HD44780-based LCDs
 *
 * Supports only the 16x2 display on the EduBase-V2 board
 *
 * @code
 * #include "mbed.h"
 * #include "TextLCD.h"
 * 
 * TextLCD lcd(TextLCD::LCD_CURSOR_ON_BLINKING_ON);     // select your cursor style
 * 
 * int main() {
 *     lcd.printf("Hello World!\n");
 * }
 * @endcode
 */
class TextLCD : public Stream {
public:

    typedef enum {
        LCD_CURSOR_OFF_BLINKING_OFF = 0,
        LCD_CURSOR_OFF_BLINKING_ON = 0x01,        
        LCD_CURSOR_ON_BLINKING_OFF = 0x02,
        LCD_CURSOR_ON_BLINKING_ON = 0x03,
        LCD_CURSOR_DEFAULT = 0x03
    } LCDCursor;
  
    /** Declare a TextLCD interface */
    TextLCD(LCDCursor cur);      // default constructor
 
#if DOXYGEN_ONLY
    /** Write a character to the LCD
     *
     * @param c The character to write to the display
     */
    int putc(int c);
 
    /** Write a formated string to the LCD
     *
     * @param format A printf-style format string, followed by the
     *               variables to use in formating the string.
     */
    int printf(const char* format, ...);
#endif
 
    /** Locate to a screen column and row
     *
     * @param column  The horizontal position from the left, indexed from 0
     * @param row     The vertical position from the top, indexed from 0
     */
    void setLocation(int column, int row);
 
    /** Clear the screen and locate to 0,0 */
    void cls();
 
    /** low-level single character putter **/
    void setCharacter(int row, int column, int c);
    void setCursor(LCDCursor c);
 
protected:
 
    // Stream implementation functions
    virtual int _putc(int value);
    virtual int _getc();
 
    int address(int column, int row);
    void writeNibble(char incoming, unsigned char rs);
    void writeCommand(int command);
    void writeData(int data);
 
    int _column;
    int _row;
    int _maxColumns;
    int _maxRows;
    int _cursorState;
    
};
 
#endif
