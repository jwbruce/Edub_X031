/* F031K6 or L031K6 + Edubase-V2 support Library
 *
 * basic functions to support programming and development of F and L
 * series Nucleo targets on EduBase-V2 targets.
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

// get the macros, prototypes, externs, etc.
#include    "TTU_X031.h"
#include    "mbed.h"

// create the communications ports
SPI             spi(MOSI_PIN, MISO_PIN, SCLK_PIN);
#ifdef USE_I2C
I2C             i2c(SDA_PIN, SCL_PIN);
#endif

// not sure why other PinNames cause error..... Investigate further.
Serial          pc(USBTX, USBRX, 57600);

// create the LEDs
DigitalOut      led0(LED0_PIN);
DigitalOut      led1(LED1_PIN);
DigitalOut      led2(LED2_PIN);

// led3 only works if the solder jumper SB18 on the Nucleo32
// board (back side) has been removed. The default state of SB18
// (shorted) ties LED3_PIN (PB_7) to SW5_PIN (PA_5).
//
// UNCOMMENT ONLY **** ONE **** OF THE FOLLOWING TWO LINES
//DigitalOut      led3(LED3_PIN);
DigitalIn       __PinPB7(LED3_PIN);     // not very useful as it only reads the status of sw5


// create the speaker
DigitalOut      speaker(SPK_PIN);

//create the chip-selects
DigitalOut      cs_sd(CS_SD_PIN);
DigitalOut      cs_lcd(CS_LCD_PIN);
DigitalOut      cs_7seg(CS_7SEG_PIN);

// create the switches
DigitalIn       sw4(SW4_PIN);
DigitalIn       sw5(SW5_PIN);

// create the analog sensors
AnalogIn        lightSensor(LGT_SENS_PIN);
AnalogIn        pot(POT_PIN);
AnalogIn        tempSensor(TEMP_SENS_PIN);

void init_spi(int i_spiBaud) {
    // Deassert the chip-selects. Remember our chip-selects are active-low.
    cs_sd = 1;
    cs_lcd = 1;
    cs_7seg = 1;
    // configure the SPI port
    spi.format(8,0);               // 8-bit SPI mode 0
    if (i_spiBaud == 0) {
        spi.frequency(1000000);     // default to 1Mbps     
    } else {
        spi.frequency(i_spiBaud);  // else, set the user-defined bitrate
    }
} // end init_spi()


#ifdef USE_I2C
void init_i2c(int i_i2cBaud) {
    if (i_i2cBaud == I2C_SPEED_FAST) {
        // 400 kbps (most chips should be able to handle this speed)
        i2c.frequency(I2C_SPEED_FAST);          
    } else if (i_i2cBaud == I2C_SPEED_FASTPLUS) {
        // 1Mbps (many chips can't go this fast)
        i2c.frequency(I2C_SPEED_FASTPLUS);      
    } else { 
        // 100 kbps (the original I2C bitrate)
        i2c.frequency(I2C_SPEED_STD);      
    }
} // end init_i2c()
#endif

void init_serial(int i_serialBaud) {
    // for now, we will use
    //  19200 Baud, 8 data bits, no parity, and 1 stop bit (8N1)
    
    //pc.baud(19200);         // default to 19.2 kBaud for now
    //pc.format(8, SerialBase::None, 1);       
    
} // end init_serial()

void init_leds(void) {
    // turn off all LEDs
    led0 = 0;
    led1 = 0;
    led2 = 0;
} // end init_leds()

void init_all() {
    // a single call to initialize all hardware to something reasonable
    init_spi(500000);           // 500 kbps
    #ifdef USE_I2C
    init_i2c(I2C_SPEED_STD);  // 100 kbps
    #endif
    init_serial(0);             // 19.2k/8/N/1
    init_leds();
} // end init_all()
