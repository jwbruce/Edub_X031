/* **********************************************************
 *  A quick (and ugly) program to exercise many of the 
 *  X031 to EduBase-V2 connections
 * **********************************************************
 */

// TEST PROGRAM
#include "TTU_X031.h"
#include "TextLCD.h"
#include "SevenSegmentLED.h"
#include "mbed.h"

int main() {
    TextLCD             lcd(TextLCD::LCD_CURSOR_OFF_BLINKING_OFF);
    SevenSegmentLED     seg7(SevenSegmentLED::LED_PATTERN_A, SevenSegmentLED::LED_PATTERN_B, SevenSegmentLED::LED_PATTERN_C, SevenSegmentLED::LED_PATTERN_D);
    bool                b_sw4, b_sw5;
    
    init_all();
    
    lcd.setCursor(TextLCD::LCD_CURSOR_OFF_BLINKING_OFF);
    /*          TTU-ECE led:                   */                  
    lcd.printf("X031    led:\n");
    lcd.printf("sw:      ss:");
    
    // on-screen (PC) instructions
    pc.printf("\nTTU_X031 Test compiled on %s at %s\n", __DATE__, __TIME__);
    pc.printf("Press '1'-'3' to turn LEDs 0,1,2,3\n");
    pc.printf("   Press the shift-'1'-shift-'3' to turn off LEDs\n");
    pc.printf("Press 'a'-'d' to illuminate seven-segment LEDs\n");
    pc.printf("   Press 'e' to turn off LED displays\n");

    b_sw4 = sw4;
    b_sw5 = sw5;
    
    while(TRUE) {
        // Read hardware switches
        if (sw4 != b_sw4) {
            b_sw4 = sw4;
            if (b_sw4) {
                lcd.setCharacter(1,3,'4');
            } else {
                lcd.setCharacter(1,3,' ');            
            }
        } // end if()

        if (sw5 != b_sw5) {
            b_sw5 = sw5;
            if (b_sw5) {
                lcd.setCharacter(1,4,'5');
            } else {
                lcd.setCharacter(1,4,' ');            
            }
        } // end if()

        if (pc.readable()) {   
            // Read terminal for user input....
            char c = pc.getc(); 
            if (c == '1') {
                led0 = 1; // ON
                lcd.setCharacter(0,15,'0');
            }
            if (c == '2') {
                led1 = 1; // ON
                lcd.setCharacter(0,14,'1');
            }
            if (c == '3') {
                led2 = 1; // ON
                lcd.setCharacter(0,13,'2');
            }
            
            // only do the following if we have the ability to 
            // control LED3
            #ifdef  USE_LED3
            if (c == '4') {
                led3 = 1; // ON
                lcd.setCharacter(0,12,'3');
            }
            #endif
            
            if (c == '!') {
                led0 = 0; // OFF
                lcd.setCharacter(0,15,' ');
            }
            if (c == '@') {
                led1 = 0; // OFF
                lcd.setCharacter(0,14,' ');
            }
            if (c == '#') {
                led2 = 0; // OFF
                lcd.setCharacter(0,13,' ');
            }

            // only do the following if we have the ability to 
            // control LED3
            #ifdef  USE_LED3
            if (c == '$') {
                led3 = 0; // OFF
                lcd.setCharacter(0,12,' ');
            }
            #endif
    
            if (c == 'a') {
                seg7.illuminateDisplay(SevenSegmentLED::LED_DISPLAY1);
                lcd.setCharacter(1,13,' ');
                lcd.setCharacter(1,14,' ');
                lcd.setCharacter(1,15,' ');
                lcd.setCharacter(1,12,'A');            
            }
            if (c == 'b') {
                seg7.illuminateDisplay(SevenSegmentLED::LED_DISPLAY2);
                lcd.setCharacter(1,12,' ');
                lcd.setCharacter(1,14,' ');
                lcd.setCharacter(1,15,' ');
                lcd.setCharacter(1,13,'b');                        
            }
            if (c == 'c') {
                seg7.illuminateDisplay(SevenSegmentLED::LED_DISPLAY3);
                lcd.setCharacter(1,12,' ');
                lcd.setCharacter(1,13,' ');
                lcd.setCharacter(1,15,' ');
                lcd.setCharacter(1,14,'C');                        
            }
            if (c == 'd') {
                seg7.illuminateDisplay(SevenSegmentLED::LED_DISPLAY4);
                lcd.setCharacter(1,12,' ');
                lcd.setCharacter(1,13,' ');
                lcd.setCharacter(1,14,' ');
                lcd.setCharacter(1,15,'d');                        
            }       
            if (c == 'e') {
                seg7.allOff();
                lcd.setCharacter(1,12,' ');
                lcd.setCharacter(1,13,' ');
                lcd.setCharacter(1,14,' ');
                lcd.setCharacter(1,15,' ');
            } // end if()   
        }
    } // end if()
} // end main()
