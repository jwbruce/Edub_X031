/* F031K6 & L031K6 + Edubase-V2 7-segment LED Library
 * for the 4 seven-segment LEDs inteface connected via two 74HC595s using SPI
 *
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

#include "SevenSegmentLED.h"
#include "TTU_X031.h"
#include "mbed.h"

// constructor
SevenSegmentLED::SevenSegmentLED(LEDPattern d1, LEDPattern d2, LEDPattern d3, LEDPattern d4) :
     _dp1(d1), _dp2(d2), _dp3(d3), _dp4(d4) {
    
    // something for the constructor to do     
    wait_ms(1);
    
}

/* write 16 bits to LED shift registers
**
** We need to assert/deassert /CS_LED around the 16-bit SPI
**   transfer becase /CS_LED is the register STROBE/CLK
**   on the 74HC595 shift registers.  See EduBase_V2 1173D_2 schematic.
*/
void SevenSegmentLED::_writeDisplay(LEDDisplay disp, LEDPattern patt) {
    cs_7seg = 0;                            /* ASSERT /CS_7 */
    spi.write(patt);                        /* write segment pattern */
    spi.write(disp);                        /* write display cathode */
    cs_7seg = 1;                            /* DEASSERT /CS_7 */
}

/* write 16 bits to LED shift registers
**
** We need to assert/deassert /CS_LED around the 16-bit SPI
**   transfer becase /CS_LED is the register STROBE/CLK
**   on the 74HC595 shift registers.  See EduBase_V2 1173D_2 schematic.
*/
void SevenSegmentLED::setCharacter(LEDDisplay disp, LEDPattern patt) {
    if (disp == LED_DISPLAY1)
        _dp1 = patt;
    else if (disp == LED_DISPLAY2)
        _dp2 = patt;
    else if (disp == LED_DISPLAY3)
        _dp3 = patt;
    else if (disp == LED_DISPLAY4)
        _dp4 = patt;
        
    // and finally, write the requested display
    _writeDisplay(disp, patt);
}

/* Illuminate the requested display with the last
** pattern written to the attribute
*/
void SevenSegmentLED::illuminateDisplay(LEDDisplay disp) {
    LEDPattern  patt;
    
    if (disp == LED_DISPLAY1)
        patt = _dp1;
    else if (disp == LED_DISPLAY2)
        patt = _dp2;
    else if (disp == LED_DISPLAY3)
        patt = _dp3;
    else if (disp == LED_DISPLAY4)
        patt = _dp4;
    else
        return;

    // and finally, write the requested display
    _writeDisplay(disp, patt);
}

void SevenSegmentLED::cls() {
    _dp1= LED_PATTERN_BLANK;
    _dp2= LED_PATTERN_BLANK;
    _dp3= LED_PATTERN_BLANK;
    _dp4= LED_PATTERN_BLANK;            
    illuminateDisplay(LED_DISPLAY1);
    illuminateDisplay(LED_DISPLAY2);
    illuminateDisplay(LED_DISPLAY3);
    illuminateDisplay(LED_DISPLAY4);            
}

void SevenSegmentLED::allOff() {
     // turn off displays without changing stored patterns
    _writeDisplay(LED_DISPLAY1, LED_PATTERN_BLANK);
    _writeDisplay(LED_DISPLAY2, LED_PATTERN_BLANK);
    _writeDisplay(LED_DISPLAY3, LED_PATTERN_BLANK);
    _writeDisplay(LED_DISPLAY4, LED_PATTERN_BLANK);
}

/* Since we stored the display pattern in an attribute
** return that to the caller.
**
** NOTE: Later we may add pattern to ASCII character decoding
** but that takes more memory and code ;-)
*/
int SevenSegmentLED::getCharacter(LEDDisplay disp) {
    if (disp == LED_DISPLAY1)
        return (int) _dp1;
    else if (disp == LED_DISPLAY2)
        return (int) _dp2;
    else if (disp == LED_DISPLAY3)
        return (int) _dp3;
    else if (disp == LED_DISPLAY4)
        return (int) _dp4;
    else
        return -1;
}
