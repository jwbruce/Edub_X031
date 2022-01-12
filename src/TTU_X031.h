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


// macros, defines, globals,and prototypes for the TTU_F031 library

//#define USE_I2C

#ifndef TTU_X031_H
#define TTU_X031_H

#include "mbed.h"

/*************************************************************************
 * 
 * DEFINES and MACROS
 * 
 **************************************************************************/
#define     FALSE           0
#define     TRUE            (~FALSE)

#define     BIT0            0x00000001
#define     BIT1            0x00000002
#define     BIT2            0x00000004
#define     BIT3            0x00000008
#define     BIT4            0x00000010
#define     BIT5            0x00000020
#define     BIT6            0x00000040
#define     BIT7            0x00000080
#define     BIT8            0x00000100
#define     BIT9            0x00000200
#define     BIT10           0x00000400
#define     BIT11           0x00000800
#define     BIT12           0x00001000
#define     BIT13           0x00002000
#define     BIT14           0x00004000
#define     BIT15           0x00008000
#define     BIT16           0x00010000
#define     BIT17           0x00020000
#define     BIT18           0x00040000
#define     BIT19           0x00080000
#define     BIT20           0x00100000
#define     BIT21           0x00200000
#define     BIT22           0x00400000
#define     BIT23           0x00800000
#define     BIT24           0x01000000
#define     BIT25           0x02000000
#define     BIT26           0x04000000
#define     BIT27           0x08000000
#define     BIT28           0x10000000
#define     BIT29           0x20000000
#define     BIT30           0x40000000
#define     BIT31           0x80000000

#ifdef TARGET_NUCLEO_L031K6
#define     TARGET_NAME     "xL031"
#endif

#ifdef TARGET_NUCLEO_F031K6
#define     TARGET_NAME     "xF031"
#endif


/*************************************************************************
 * 
 * HW to peripheral pin mappings
 * 
**************************************************************************/
#define     SCL_PIN         PA_9
#define     SDA_PIN         PA_10
#define     LED0_PIN        PA_12
#define     LED1_PIN        PB_0
#define     LED3_PIN        PB_7
#define     PWM1_PIN        PB_1

#ifdef TARGET_NUCLEO_L031K6
#define     LED2_PIN        PC_14
#define     CS_SD_PIN       PC_15
#endif

#ifdef TARGET_NUCLEO_F031K6
#define     LED2_PIN        PF_0
#define     CS_SD_PIN       PF_1
#endif

#define     SPK_PIN         PA_8
#define     CS_LCD_PIN      PA_11
#define     MOSI_PIN        PB_5
#define     MISO_PIN        PB_4
#define     SCLK_PIN        PB_3
#define     LGT_SENS_PIN    PA_0
#define     POT_PIN         PA_1
#define     TEMP_SENS_PIN   PA_3
#define     PWM2_PIN        PA_4
#define     SW4_PIN         PA_5
#define     SW5_PIN         PA_6
#define     CS_7SEG_PIN     PA_7
#define     TX_PIN          PA_12
#define     RX_PIN          PA_15          

/*************************************************************************
 * 
 * Other useful defines
 * 
 **************************************************************************/
#define     I2C_SPEED_STD       100000
#define     I2C_SPEED_FAST      400000
#define     I2C_SPEED_FASTPLUS  1000000

/*************************************************************************
 *
 * USEFUL MACROS
 *
 *************************************************************************/

/*************************************************************************
 *
 * G L O B A L     V A R I A B L E S
 *
 *************************************************************************/
extern SPI         spi;
#ifdef USE_i2C
  extern I2C         i2c;
#endif
extern Serial      pc;

// create the LEDs
extern DigitalOut      led0;
extern DigitalOut      led1;
extern DigitalOut      led2;

// UNCOMMENT ONLY **** ONE **** OF THE FOLLOWING TWO LINES
//extern DigitalOut      led3;
extern DigitalIn       __PinPB7;


// create the speaker
extern DigitalOut      speaker;

//create the chip-selects
extern DigitalOut      cs_sd;
extern DigitalOut      cs_lcd;
extern DigitalOut      cs_7seg;

// create the switches
extern DigitalIn       sw4;
extern DigitalIn       sw5;

// create the analog sensors
extern AnalogIn        lightSensor;
extern AnalogIn        pot;
extern AnalogIn        tempSensor;
 
/*************************************************************************
 *
 * P R O T O T Y P E S
 *
 *************************************************************************/
void init_spi(int i_spiBaud);
#ifdef USE_I2C
  void init_i2c(int i_i2cBaud);
#endif
void init_serial(int i_serialBaud);
void init_leds(void);
void init_all(void);

#endif
