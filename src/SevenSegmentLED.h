/* F/L031K6 + Edubase-V2 7-segment LED Library
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
 
#ifndef TTU_X031_7SEGLED_H
#define TTU_X031_7SEGLED_H
 
#include "mbed.h" 
 
/**  A 7-segment LED interface for driving 4 connected seven-segment LEDs
 *
 * @code
 * #include "mbed.h"
 * #include "TextLCD.h"
 * 
 * TextLCD lcd(p10, p12, p15, p16, p29, p30); // rs, e, d4-d7
 * 
 * int main() {
 *     lcd.printf("Hello World!\n");
 * }
 * @endcode
 */
class SevenSegmentLED {
public:

    typedef enum {
        LED_PATTERN_0 = ~0x3F,
        LED_PATTERN_1 = ~0x06,
        LED_PATTERN_2 = ~0x5B,
        LED_PATTERN_3 = ~0x4F,
        LED_PATTERN_4 = ~0x66,
        LED_PATTERN_5 = ~0x6D,
        LED_PATTERN_6 = ~0x7D,
        LED_PATTERN_7 = ~0x07,
        LED_PATTERN_8 = ~0x7F,
        LED_PATTERN_9 = ~0x6F,
        LED_PATTERN_A = ~0x77,
        LED_PATTERN_B = ~0x7C,
        LED_PATTERN_C = ~0x39,
        LED_PATTERN_D = ~0x5E,
        LED_PATTERN_E = ~0x79,
        LED_PATTERN_F = ~0x71,
        LED_PATTERN_G = ~0x40,        
        LED_PATTERN_H = ~0x76,
        LED_PATTERN_I = ~0x30,
        LED_PATTERN_J = ~0x1E,
        LED_PATTERN_L = ~0x38,
        LED_PATTERN_N = ~0x54,      
        LED_PATTERN_O = ~0x3F,
        LED_PATTERN_P = ~0x73,        
        LED_PATTERN_Q = ~0x67,        
        LED_PATTERN_R = ~0x50,        
        LED_PATTERN_S = LED_PATTERN_5,        
        LED_PATTERN_T = ~0x78,
        LED_PATTERN_U = ~0x1C,        
        LED_PATTERN_V = ~0x2A,
        LED_PATTERN_Y = ~0x6E,        
        LED_PATTERN_BLANK = ~0x00,
        LED_PATTERN_SPACE = LED_PATTERN_BLANK,
        LED_PATTERN_DASH = ~0x40,         
        LED_PATTERN_DEGREES = ~0xC3, 
        LED_PATTERN_DECIMALPT = ~0x80,
        LED_PATTERN_QUESTION = ~0x53
    } LEDPattern;
 
    typedef enum {
        LED_DISPLAY1 = 0x08,
        LED_DISPLAY2 = 0x04,
        LED_DISPLAY3 = 0x02,
        LED_DISPLAY4 = 0x01
    } LEDDisplay;

  
    /** Declare a 7-segment LED interface */
    // constructor
    SevenSegmentLED(LEDPattern d1, LEDPattern d2, LEDPattern d3, LEDPattern d4);      
 
    /** Clear the LEDs */
    void cls();         // change patterns to blank and write the displays
    void allOff();      // turn off displays without changing stored pattern
 
    int getCharacter(LEDDisplay disp);
 
    /** low-level single character putter to a single display **/
    void setCharacter(LEDDisplay disp, LEDPattern patt);
    void illuminateDisplay(LEDDisplay disp);
 
protected:
    void _writeDisplay(LEDDisplay disp, LEDPattern patt);
    LEDPattern  _dp1;
    LEDPattern  _dp2;
    LEDPattern  _dp3;
    LEDPattern  _dp4;
    
};
 
#endif
