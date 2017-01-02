
/* ########################################################################## */
/*
 * This file was created by www.DavesMotleyProjects.com
 *
 * This software is provided under the following conditions:
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *                                                                            */
/* ########################################################################## */


/* ===========================================================================*/
/*
 * FileName:      MSP430F5529LP_GPIO.c
 *
 * This file provides functions to control and configure the General Purpose
 * Input / Output (GPIO) pins on the Texas Instruments MSP430F5529 Launchpad
 * development board. These functions provide "arduino-style" control of the
 * pins based on pin number (as viewed from the external package).
 *
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
 *
 *                                                                            */
/* ===========================================================================*/

#include "MSP430F5529LP.h"
#include "MSP430F5529LP_GPIO.h"


/******************************************************************************
    PUBLIC DEFINITIONS
******************************************************************************/

   
/******************************************************************************
    PUBLIC VARIABLES
******************************************************************************/
  
 
/******************************************************************************
    PRIVATE DEFINITIONS (static const)
******************************************************************************/


/******************************************************************************
    PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/


/******************************************************************************
    PRIVATE VARIABLES (static)
******************************************************************************/


/******************************************************************************
    Subroutine:     pinDirection
    Description:    Function to set pin direction (input or output)
    Inputs:         pin (uint8_t) is a value between 1 and 80, corresponding to
                    a valid GPIO pin Passing in illegal values has no effect.
                    pinDir (pinDirection_enum) can have the values INPUT or
                    OUTPUT, which defines the desired direction.
    Outputs:        None

******************************************************************************/
void pinDirection(uint8_t pin, pinDirection_enum pinDir)
{
    switch(pin)
    {
        case (1):  P6DIR_bits.P6DIR4 = pinDir; break;    //P6.4, CB4, A4
        case (2):  P6DIR_bits.P6DIR5 = pinDir; break;    //P6.5, CB5, A5
        case (3):  P6DIR_bits.P6DIR6 = pinDir; break;    //P6.6, CB6, A6
        case (4):  P6DIR_bits.P6DIR7 = pinDir; break;    //P6.7, CB7, A7
        case (5):  P7DIR_bits.P7DIR0 = pinDir; break;    //P7.0, CB8, A12
        case (6):  P7DIR_bits.P7DIR1 = pinDir; break;    //P7.1, CB9, A13
        case (7):  P7DIR_bits.P7DIR2 = pinDir; break;    //P7.2, CB10, A14
        case (8):  P7DIR_bits.P7DIR3 = pinDir; break;    //P7.3, CB11, A15
        case (9):  P5DIR_bits.P5DIR0 = pinDir; break;    //P5.0, A8, VREF+, VeREF+
        case (10): P5DIR_bits.P5DIR1 = pinDir; break;    //P5.1, A9, VREF-, VeREF-
        case (12): P5DIR_bits.P5DIR4 = pinDir; break;    //P5.4, XIN
        case (13): P5DIR_bits.P5DIR5 = pinDir; break;    //P5.5, XOUT
        case (15): P8DIR_bits.P8DIR0 = pinDir; break;    //P8.0
        case (16): P8DIR_bits.P8DIR1 = pinDir; break;    //P8.1
        case (17): P8DIR_bits.P8DIR2 = pinDir; break;    //P8.2
        case (21): P1DIR_bits.P1DIR0 = pinDir; break;    //P1.0, TA0CLK, ACLK
        case (22): P1DIR_bits.P1DIR1 = pinDir; break;    //P1.1, TA0.0
        case (23): P1DIR_bits.P1DIR2 = pinDir; break;    //P1.2, TA0.1
        case (24): P1DIR_bits.P1DIR3 = pinDir; break;    //P1.3, TA0.2
        case (25): P1DIR_bits.P1DIR4 = pinDir; break;    //P1.4, TA0.3
        case (26): P1DIR_bits.P1DIR5 = pinDir; break;    //P1.5, TA0.4
        case (27): P1DIR_bits.P1DIR6 = pinDir; break;    //P1.6, TA1CLK, CBOUT
        case (28): P1DIR_bits.P1DIR7 = pinDir; break;    //P1.7, TA1.0
        case (29): P2DIR_bits.P2DIR0 = pinDir; break;    //P2.0, TA1.1
        case (30): P2DIR_bits.P2DIR1 = pinDir; break;    //P2.1, TA1.2
        case (31): P2DIR_bits.P2DIR2 = pinDir; break;    //P2.2, TA2CLK, SMCLK
        case (32): P2DIR_bits.P2DIR3 = pinDir; break;    //P2.3, TA2.0
        case (33): P2DIR_bits.P2DIR4 = pinDir; break;    //P2.4, TA2.1
        case (34): P2DIR_bits.P2DIR5 = pinDir; break;    //P2.5, TA2.2
        case (35): P2DIR_bits.P2DIR6 = pinDir; break;    //P2.6, RTCCLK, DMAE0
        case (36): P2DIR_bits.P2DIR7 = pinDir; break;    //P2.7, UCB0STE, UCA0CLK
        case (37): P3DIR_bits.P3DIR0 = pinDir; break;    //P3.0, UCB0SIMO, UCB0SDA
        case (38): P3DIR_bits.P3DIR1 = pinDir; break;    //P3.1, UCB0SOMI, UCB0SCL
        case (39): P3DIR_bits.P3DIR2 = pinDir; break;    //P3.2, UCB0CLK, UCA0STE
        case (40): P3DIR_bits.P3DIR3 = pinDir; break;    //P3.3, UCA0TXD, UCA0SIMO
        case (41): P3DIR_bits.P3DIR4 = pinDir; break;    //P3.4, UCA0RXD, UCA0SOMI
        case (42): P3DIR_bits.P3DIR5 = pinDir; break;    //P3.5, TB0.5
        case (43): P3DIR_bits.P3DIR6 = pinDir; break;    //P3.6, TB0.6
        case (44): P3DIR_bits.P3DIR7 = pinDir; break;    //P3.7, TB0OUTH, SVMOUT
        case (45): P4DIR_bits.P4DIR0 = pinDir; break;    //P4.0, PM_UCB1STE, PM_UCA1CLK
        case (46): P4DIR_bits.P4DIR1 = pinDir; break;    //P4.1, PM_UCB1SIMO, PM_UCB1SDA
        case (47): P4DIR_bits.P4DIR2 = pinDir; break;    //P4.2, PM_UCB1SOMI, PM_UCB1SCL
        case (48): P4DIR_bits.P4DIR3 = pinDir; break;    //P4.3, PM_UCB1CLK, PM_UCA1STE
        case (51): P4DIR_bits.P4DIR4 = pinDir; break;    //P4.4, PM_UCA1TXD, PM_UCA1SIMO
        case (52): P4DIR_bits.P4DIR5 = pinDir; break;    //P4.5, PM_UCA1RXD, PM_UCA1SOMI
        case (53): P4DIR_bits.P4DIR6 = pinDir; break;    //P4.6, PM_NONE
        case (54): P4DIR_bits.P4DIR7 = pinDir; break;    //P4.7, PM_NONE
        case (55): P5DIR_bits.P5DIR6 = pinDir; break;    //P5.6, TB0.0
        case (56): P5DIR_bits.P5DIR7 = pinDir; break;    //P5.7, TB0.1
        case (57): P7DIR_bits.P7DIR4 = pinDir; break;    //P7.4, TB0.2
        case (58): P7DIR_bits.P7DIR5 = pinDir; break;    //P7.5, TB0.3
        case (59): P7DIR_bits.P7DIR6 = pinDir; break;    //P7.6, TB0.4
        case (60): P7DIR_bits.P7DIR7 = pinDir; break;    //P7.7, TB0CLK, MCLK
        case (69): P5DIR_bits.P5DIR2 = pinDir; break;    //P5.2, XT2IN
        case (70): P5DIR_bits.P5DIR3 = pinDir; break;    //P5.3, XT2OUT
        case (77): P6DIR_bits.P6DIR0 = pinDir; break;    //P6.0, CB0, A0
        case (78): P6DIR_bits.P6DIR1 = pinDir; break;    //P6.1, CB1, A1
        case (79): P6DIR_bits.P6DIR2 = pinDir; break;    //P6.2, CB2, A2
        case (80): P6DIR_bits.P6DIR3 = pinDir; break;    //P6.3, CB3, A3
        default: break;
    }
}
   
   
 /******************************************************************************
    Subroutine:     pinResEnable
    Description:    Function to enable/disable the internal resistor on the
                    specified pin. The type of resistor (pullup/pulldown) is
                    specified seperately.
    Inputs:         pin (uint8_t) is a value between 1 and 80, corresponding to
                    a valid GPIO pin Passing in illegal values has no effect.
                    rEnable (pinEnable_enum) can have the values DISABLE or
                    ENABLE, which defines the connection state of the internal
                    resistor.
    Outputs:        None

******************************************************************************/  
void pinResEnable(uint8_t pin, pinEnable_enum rEnable)
{
    switch(pin)
    {
        case (1):  P6REN_bits.P6REN4 = rEnable; break;   //P6.4, CB4, A4
        case (2):  P6REN_bits.P6REN5 = rEnable; break;   //P6.5, CB5, A5
        case (3):  P6REN_bits.P6REN6 = rEnable; break;   //P6.6, CB6, A6
        case (4):  P6REN_bits.P6REN7 = rEnable; break;   //P6.7, CB7, A7
        case (5):  P7REN_bits.P7REN0 = rEnable; break;   //P7.0, CB8, A12
        case (6):  P7REN_bits.P7REN1 = rEnable; break;   //P7.1, CB9, A13
        case (7):  P7REN_bits.P7REN2 = rEnable; break;   //P7.2, CB10, A14
        case (8):  P7REN_bits.P7REN3 = rEnable; break;   //P7.3, CB11, A15
        case (9):  P5REN_bits.P5REN0 = rEnable; break;   //P5.0, A8, VREF+, VeREF+
        case (10): P5REN_bits.P5REN1 = rEnable; break;   //P5.1, A9, VREF-, VeREF-
        case (12): P5REN_bits.P5REN4 = rEnable; break;   //P5.4, XIN
        case (13): P5REN_bits.P5REN5 = rEnable; break;   //P5.5, XOUT
        case (15): P8REN_bits.P8REN0 = rEnable; break;   //P8.0
        case (16): P8REN_bits.P8REN1 = rEnable; break;   //P8.1
        case (17): P8REN_bits.P8REN2 = rEnable; break;   //P8.2
        case (21): P1REN_bits.P1REN0 = rEnable; break;   //P1.0, TA0CLK, ACLK
        case (22): P1REN_bits.P1REN1 = rEnable; break;   //P1.1, TA0.0
        case (23): P1REN_bits.P1REN2 = rEnable; break;   //P1.2, TA0.1
        case (24): P1REN_bits.P1REN3 = rEnable; break;   //P1.3, TA0.2
        case (25): P1REN_bits.P1REN4 = rEnable; break;   //P1.4, TA0.3
        case (26): P1REN_bits.P1REN5 = rEnable; break;   //P1.5, TA0.4
        case (27): P1REN_bits.P1REN6 = rEnable; break;   //P1.6, TA1CLK, CBOUT
        case (28): P1REN_bits.P1REN7 = rEnable; break;   //P1.7, TA1.0
        case (29): P2REN_bits.P2REN0 = rEnable; break;   //P2.0, TA1.1
        case (30): P2REN_bits.P2REN1 = rEnable; break;   //P2.1, TA1.2
        case (31): P2REN_bits.P2REN2 = rEnable; break;   //P2.2, TA2CLK, SMCLK
        case (32): P2REN_bits.P2REN3 = rEnable; break;   //P2.3, TA2.0
        case (33): P2REN_bits.P2REN4 = rEnable; break;   //P2.4, TA2.1
        case (34): P2REN_bits.P2REN5 = rEnable; break;   //P2.5, TA2.2
        case (35): P2REN_bits.P2REN6 = rEnable; break;   //P2.6, RTCCLK, DMAE0
        case (36): P2REN_bits.P2REN7 = rEnable; break;   //P2.7, UCB0STE, UCA0CLK
        case (37): P3REN_bits.P3REN0 = rEnable; break;   //P3.0, UCB0SIMO, UCB0SDA
        case (38): P3REN_bits.P3REN1 = rEnable; break;   //P3.1, UCB0SOMI, UCB0SCL
        case (39): P3REN_bits.P3REN2 = rEnable; break;   //P3.2, UCB0CLK, UCA0STE
        case (40): P3REN_bits.P3REN3 = rEnable; break;   //P3.3, UCA0TXD, UCA0SIMO
        case (41): P3REN_bits.P3REN4 = rEnable; break;   //P3.4, UCA0RXD, UCA0SOMI
        case (42): P3REN_bits.P3REN5 = rEnable; break;   //P3.5, TB0.5
        case (43): P3REN_bits.P3REN6 = rEnable; break;   //P3.6, TB0.6
        case (44): P3REN_bits.P3REN7 = rEnable; break;   //P3.7, TB0OUTH, SVMOUT
        case (45): P4REN_bits.P4REN0 = rEnable; break;   //P4.0, PM_UCB1STE, PM_UCA1CLK
        case (46): P4REN_bits.P4REN1 = rEnable; break;   //P4.1, PM_UCB1SIMO, PM_UCB1SDA
        case (47): P4REN_bits.P4REN2 = rEnable; break;   //P4.2, PM_UCB1SOMI, PM_UCB1SCL
        case (48): P4REN_bits.P4REN3 = rEnable; break;   //P4.3, PM_UCB1CLK, PM_UCA1STE
        case (51): P4REN_bits.P4REN4 = rEnable; break;   //P4.4, PM_UCA1TXD, PM_UCA1SIMO
        case (52): P4REN_bits.P4REN5 = rEnable; break;   //P4.5, PM_UCA1RXD, PM_UCA1SOMI
        case (53): P4REN_bits.P4REN6 = rEnable; break;   //P4.6, PM_NONE
        case (54): P4REN_bits.P4REN7 = rEnable; break;   //P4.7, PM_NONE
        case (55): P5REN_bits.P5REN6 = rEnable; break;   //P5.6, TB0.0
        case (56): P5REN_bits.P5REN7 = rEnable; break;   //P5.7, TB0.1
        case (57): P7REN_bits.P7REN4 = rEnable; break;   //P7.4, TB0.2
        case (58): P7REN_bits.P7REN5 = rEnable; break;   //P7.5, TB0.3
        case (59): P7REN_bits.P7REN6 = rEnable; break;   //P7.6, TB0.4
        case (60): P7REN_bits.P7REN7 = rEnable; break;   //P7.7, TB0CLK, MCLK
        case (69): P5REN_bits.P5REN2 = rEnable; break;   //P5.2, XT2IN
        case (70): P5REN_bits.P5REN3 = rEnable; break;   //P5.3, XT2OUT
        case (77): P6REN_bits.P6REN0 = rEnable; break;   //P6.0, CB0, A0
        case (78): P6REN_bits.P6REN1 = rEnable; break;   //P6.1, CB1, A1
        case (79): P6REN_bits.P6REN2 = rEnable; break;   //P6.2, CB2, A2
        case (80): P6REN_bits.P6REN3 = rEnable; break;   //P6.3, CB3, A3
        default: break;
    }
}
   

 /******************************************************************************
    Subroutine:     pinOutput
    Description:    Function to set the output state of the specified pin.
    Inputs:         pin (uint8_t) is a value between 1 and 80, corresponding to
                    a valid GPIO pin Passing in illegal values has no effect.
                    pLevel (pinLevel_enum) can have the values LOW or HIGH,
                    which defines the output level.
    Outputs:        None

******************************************************************************/ 
void pinOutput(uint8_t pin, pinLevel_enum pLevel)
{
    switch(pin)
    {
        case (1):  P6OUT_bits.P6OUT4 = pLevel; break;    //P6.4, CB4, A4
        case (2):  P6OUT_bits.P6OUT5 = pLevel; break;    //P6.5, CB5, A5
        case (3):  P6OUT_bits.P6OUT6 = pLevel; break;    //P6.6, CB6, A6
        case (4):  P6OUT_bits.P6OUT7 = pLevel; break;    //P6.7, CB7, A7
        case (5):  P7OUT_bits.P7OUT0 = pLevel; break;    //P7.0, CB8, A12
        case (6):  P7OUT_bits.P7OUT1 = pLevel; break;    //P7.1, CB9, A13
        case (7):  P7OUT_bits.P7OUT2 = pLevel; break;    //P7.2, CB10, A14
        case (8):  P7OUT_bits.P7OUT3 = pLevel; break;    //P7.3, CB11, A15
        case (9):  P5OUT_bits.P5OUT0 = pLevel; break;    //P5.0, A8, VREF+, VeREF+
        case (10): P5OUT_bits.P5OUT1 = pLevel; break;    //P5.1, A9, VREF-, VeREF-
        case (12): P5OUT_bits.P5OUT4 = pLevel; break;    //P5.4, XIN
        case (13): P5OUT_bits.P5OUT5 = pLevel; break;    //P5.5, XOUT
        case (15): P8OUT_bits.P8OUT0 = pLevel; break;    //P8.0
        case (16): P8OUT_bits.P8OUT1 = pLevel; break;    //P8.1
        case (17): P8OUT_bits.P8OUT2 = pLevel; break;    //P8.2
        case (21): P1OUT_bits.P1OUT0 = pLevel; break;    //P1.0, TA0CLK, ACLK
        case (22): P1OUT_bits.P1OUT1 = pLevel; break;    //P1.1, TA0.0
        case (23): P1OUT_bits.P1OUT2 = pLevel; break;    //P1.2, TA0.1
        case (24): P1OUT_bits.P1OUT3 = pLevel; break;    //P1.3, TA0.2
        case (25): P1OUT_bits.P1OUT4 = pLevel; break;    //P1.4, TA0.3
        case (26): P1OUT_bits.P1OUT5 = pLevel; break;    //P1.5, TA0.4
        case (27): P1OUT_bits.P1OUT6 = pLevel; break;    //P1.6, TA1CLK, CBOUT
        case (28): P1OUT_bits.P1OUT7 = pLevel; break;    //P1.7, TA1.0
        case (29): P2OUT_bits.P2OUT0 = pLevel; break;    //P2.0, TA1.1
        case (30): P2OUT_bits.P2OUT1 = pLevel; break;    //P2.1, TA1.2
        case (31): P2OUT_bits.P2OUT2 = pLevel; break;    //P2.2, TA2CLK, SMCLK
        case (32): P2OUT_bits.P2OUT3 = pLevel; break;    //P2.3, TA2.0
        case (33): P2OUT_bits.P2OUT4 = pLevel; break;    //P2.4, TA2.1
        case (34): P2OUT_bits.P2OUT5 = pLevel; break;    //P2.5, TA2.2
        case (35): P2OUT_bits.P2OUT6 = pLevel; break;    //P2.6, RTCCLK, DMAE0
        case (36): P2OUT_bits.P2OUT7 = pLevel; break;    //P2.7, UCB0STE, UCA0CLK
        case (37): P3OUT_bits.P3OUT0 = pLevel; break;    //P3.0, UCB0SIMO, UCB0SDA
        case (38): P3OUT_bits.P3OUT1 = pLevel; break;    //P3.1, UCB0SOMI, UCB0SCL
        case (39): P3OUT_bits.P3OUT2 = pLevel; break;    //P3.2, UCB0CLK, UCA0STE
        case (40): P3OUT_bits.P3OUT3 = pLevel; break;    //P3.3, UCA0TXD, UCA0SIMO
        case (41): P3OUT_bits.P3OUT4 = pLevel; break;    //P3.4, UCA0RXD, UCA0SOMI
        case (42): P3OUT_bits.P3OUT5 = pLevel; break;    //P3.5, TB0.5
        case (43): P3OUT_bits.P3OUT6 = pLevel; break;    //P3.6, TB0.6
        case (44): P3OUT_bits.P3OUT7 = pLevel; break;    //P3.7, TB0OUTH, SVMOUT
        case (45): P4OUT_bits.P4OUT0 = pLevel; break;    //P4.0, PM_UCB1STE, PM_UCA1CLK
        case (46): P4OUT_bits.P4OUT1 = pLevel; break;    //P4.1, PM_UCB1SIMO, PM_UCB1SDA
        case (47): P4OUT_bits.P4OUT2 = pLevel; break;    //P4.2, PM_UCB1SOMI, PM_UCB1SCL
        case (48): P4OUT_bits.P4OUT3 = pLevel; break;    //P4.3, PM_UCB1CLK, PM_UCA1STE
        case (51): P4OUT_bits.P4OUT4 = pLevel; break;    //P4.4, PM_UCA1TXD, PM_UCA1SIMO
        case (52): P4OUT_bits.P4OUT5 = pLevel; break;    //P4.5, PM_UCA1RXD, PM_UCA1SOMI
        case (53): P4OUT_bits.P4OUT6 = pLevel; break;    //P4.6, PM_NONE
        case (54): P4OUT_bits.P4OUT7 = pLevel; break;    //P4.7, PM_NONE
        case (55): P5OUT_bits.P5OUT6 = pLevel; break;    //P5.6, TB0.0
        case (56): P5OUT_bits.P5OUT7 = pLevel; break;    //P5.7, TB0.1
        case (57): P7OUT_bits.P7OUT4 = pLevel; break;    //P7.4, TB0.2
        case (58): P7OUT_bits.P7OUT5 = pLevel; break;    //P7.5, TB0.3
        case (59): P7OUT_bits.P7OUT6 = pLevel; break;    //P7.6, TB0.4
        case (60): P7OUT_bits.P7OUT7 = pLevel; break;    //P7.7, TB0CLK, MCLK
        case (69): P5OUT_bits.P5OUT2 = pLevel; break;    //P5.2, XT2IN
        case (70): P5OUT_bits.P5OUT3 = pLevel; break;    //P5.3, XT2OUT
        case (77): P6OUT_bits.P6OUT0 = pLevel; break;    //P6.0, CB0, A0
        case (78): P6OUT_bits.P6OUT1 = pLevel; break;    //P6.1, CB1, A1
        case (79): P6OUT_bits.P6OUT2 = pLevel; break;    //P6.2, CB2, A2
        case (80): P6OUT_bits.P6OUT3 = pLevel; break;    //P6.3, CB3, A3
        default: break;
    }
}

/******************************************************************************
    Subroutine:     pinSelect
    Description:    Function to select the alternate function for the
                    specified GPIO pin. (i.e. ADC Input, Clock Output...)
    Inputs:         pin (uint8_t) is a value between 1 and 80, corresponding to
                    a valid GPIO pin Passing in illegal values has no effect.
                    pSelect (pinSelect_enum) can have the values GPIO or
                    ALT_FUNC, which defines the desired pin function.
    Outputs:        None

******************************************************************************/ 
void pinSelect(uint8_t pin, pinSelect_enum pSelect)
{
    switch(pin)
    {
        case (1):  P6SEL_bits.P6SEL4 = pSelect; break;   //P6.4, CB4, A4
        case (2):  P6SEL_bits.P6SEL5 = pSelect; break;   //P6.5, CB5, A5
        case (3):  P6SEL_bits.P6SEL6 = pSelect; break;   //P6.6, CB6, A6
        case (4):  P6SEL_bits.P6SEL7 = pSelect; break;   //P6.7, CB7, A7
        case (5):  P7SEL_bits.P7SEL0 = pSelect; break;   //P7.0, CB8, A12
        case (6):  P7SEL_bits.P7SEL1 = pSelect; break;   //P7.1, CB9, A13
        case (7):  P7SEL_bits.P7SEL2 = pSelect; break;   //P7.2, CB10, A14
        case (8):  P7SEL_bits.P7SEL3 = pSelect; break;   //P7.3, CB11, A15
        case (9):  P5SEL_bits.P5SEL0 = pSelect; break;   //P5.0, A8, VREF+, VeREF+
        case (10): P5SEL_bits.P5SEL1 = pSelect; break;   //P5.1, A9, VREF-, VeREF-
        case (12): P5SEL_bits.P5SEL4 = pSelect; break;   //P5.4, XIN
        case (13): P5SEL_bits.P5SEL5 = pSelect; break;   //P5.5, XOUT
        case (15): P8SEL_bits.P8SEL0 = pSelect; break;   //P8.0
        case (16): P8SEL_bits.P8SEL1 = pSelect; break;   //P8.1
        case (17): P8SEL_bits.P8SEL2 = pSelect; break;   //P8.2
        case (21): P1SEL_bits.P1SEL0 = pSelect; break;   //P1.0, TA0CLK, ACLK
        case (22): P1SEL_bits.P1SEL1 = pSelect; break;   //P1.1, TA0.0
        case (23): P1SEL_bits.P1SEL2 = pSelect; break;   //P1.2, TA0.1
        case (24): P1SEL_bits.P1SEL3 = pSelect; break;   //P1.3, TA0.2
        case (25): P1SEL_bits.P1SEL4 = pSelect; break;   //P1.4, TA0.3
        case (26): P1SEL_bits.P1SEL5 = pSelect; break;   //P1.5, TA0.4
        case (27): P1SEL_bits.P1SEL6 = pSelect; break;   //P1.6, TA1CLK, CBOUT
        case (28): P1SEL_bits.P1SEL7 = pSelect; break;   //P1.7, TA1.0
        case (29): P2SEL_bits.P2SEL0 = pSelect; break;   //P2.0, TA1.1
        case (30): P2SEL_bits.P2SEL1 = pSelect; break;   //P2.1, TA1.2
        case (31): P2SEL_bits.P2SEL2 = pSelect; break;   //P2.2, TA2CLK, SMCLK
        case (32): P2SEL_bits.P2SEL3 = pSelect; break;   //P2.3, TA2.0
        case (33): P2SEL_bits.P2SEL4 = pSelect; break;   //P2.4, TA2.1
        case (34): P2SEL_bits.P2SEL5 = pSelect; break;   //P2.5, TA2.2
        case (35): P2SEL_bits.P2SEL6 = pSelect; break;   //P2.6, RTCCLK, DMAE0
        case (36): P2SEL_bits.P2SEL7 = pSelect; break;   //P2.7, UCB0STE, UCA0CLK
        case (37): P3SEL_bits.P3SEL0 = pSelect; break;   //P3.0, UCB0SIMO, UCB0SDA
        case (38): P3SEL_bits.P3SEL1 = pSelect; break;   //P3.1, UCB0SOMI, UCB0SCL
        case (39): P3SEL_bits.P3SEL2 = pSelect; break;   //P3.2, UCB0CLK, UCA0STE
        case (40): P3SEL_bits.P3SEL3 = pSelect; break;   //P3.3, UCA0TXD, UCA0SIMO
        case (41): P3SEL_bits.P3SEL4 = pSelect; break;   //P3.4, UCA0RXD, UCA0SOMI
        case (42): P3SEL_bits.P3SEL5 = pSelect; break;   //P3.5, TB0.5
        case (43): P3SEL_bits.P3SEL6 = pSelect; break;   //P3.6, TB0.6
        case (44): P3SEL_bits.P3SEL7 = pSelect; break;   //P3.7, TB0OUTH, SVMOUT
        case (45): P4SEL_bits.P4SEL0 = pSelect; break;   //P4.0, PM_UCB1STE, PM_UCA1CLK
        case (46): P4SEL_bits.P4SEL1 = pSelect; break;   //P4.1, PM_UCB1SIMO, PM_UCB1SDA
        case (47): P4SEL_bits.P4SEL2 = pSelect; break;   //P4.2, PM_UCB1SOMI, PM_UCB1SCL
        case (48): P4SEL_bits.P4SEL3 = pSelect; break;   //P4.3, PM_UCB1CLK, PM_UCA1STE
        case (51): P4SEL_bits.P4SEL4 = pSelect; break;   //P4.4, PM_UCA1TXD, PM_UCA1SIMO
        case (52): P4SEL_bits.P4SEL5 = pSelect; break;   //P4.5, PM_UCA1RXD, PM_UCA1SOMI
        case (53): P4SEL_bits.P4SEL6 = pSelect; break;   //P4.6, PM_NONE
        case (54): P4SEL_bits.P4SEL7 = pSelect; break;   //P4.7, PM_NONE
        case (55): P5SEL_bits.P5SEL6 = pSelect; break;   //P5.6, TB0.0
        case (56): P5SEL_bits.P5SEL7 = pSelect; break;   //P5.7, TB0.1
        case (57): P7SEL_bits.P7SEL4 = pSelect; break;   //P7.4, TB0.2
        case (58): P7SEL_bits.P7SEL5 = pSelect; break;   //P7.5, TB0.3
        case (59): P7SEL_bits.P7SEL6 = pSelect; break;   //P7.6, TB0.4
        case (60): P7SEL_bits.P7SEL7 = pSelect; break;   //P7.7, TB0CLK, MCLK
        case (69): P5SEL_bits.P5SEL2 = pSelect; break;   //P5.2, XT2IN
        case (70): P5SEL_bits.P5SEL3 = pSelect; break;   //P5.3, XT2OUT
        case (77): P6SEL_bits.P6SEL0 = pSelect; break;   //P6.0, CB0, A0
        case (78): P6SEL_bits.P6SEL1 = pSelect; break;   //P6.1, CB1, A1
        case (79): P6SEL_bits.P6SEL2 = pSelect; break;   //P6.2, CB2, A2
        case (80): P6SEL_bits.P6SEL3 = pSelect; break;   //P6.3, CB3, A3
        default: break;
    }
}


/******************************************************************************
    Subroutine:     pinInput
    Description:    Function to read the input value of the specified GPIO pin.
    Inputs:         pin (uint8_t) is a value between 1 and 80, corresponding to
                    a valid GPIO pin.
    Outputs:        uint8_t return value.
                    For legal values of pin, the return value will be 0 or 1.
                    For illegal values of pin, the return value will be 0xFF.

******************************************************************************/ 
uint8_t pinInput(uint8_t pin)
{
    switch(pin)
    {
        case (1):  return (P6IN_bits.P6IN4);             //P6.4, CB4, A4
        case (2):  return (P6IN_bits.P6IN5);             //P6.5, CB5, A5
        case (3):  return (P6IN_bits.P6IN6);             //P6.6, CB6, A6
        case (4):  return (P6IN_bits.P6IN7);             //P6.7, CB7, A7
        case (5):  return (P7IN_bits.P7IN0);             //P7.0, CB8, A12
        case (6):  return (P7IN_bits.P7IN1);             //P7.1, CB9, A13
        case (7):  return (P7IN_bits.P7IN2);             //P7.2, CB10, A14
        case (8):  return (P7IN_bits.P7IN3);             //P7.3, CB11, A15
        case (9):  return (P5IN_bits.P5IN0);             //P5.0, A8, VREF+, VeREF+
        case (10): return (P5IN_bits.P5IN1);             //P5.1, A9, VREF-, VeREF-
        case (12): return (P5IN_bits.P5IN4);             //P5.4, XIN
        case (13): return (P5IN_bits.P5IN5);             //P5.5, XOUT
        case (15): return (P8IN_bits.P8IN0);             //P8.0
        case (16): return (P8IN_bits.P8IN1);             //P8.1
        case (17): return (P8IN_bits.P8IN2);             //P8.2
        case (21): return (P1IN_bits.P1IN0);             //P1.0, TA0CLK, ACLK
        case (22): return (P1IN_bits.P1IN1);             //P1.1, TA0.0
        case (23): return (P1IN_bits.P1IN2);             //P1.2, TA0.1
        case (24): return (P1IN_bits.P1IN3);             //P1.3, TA0.2
        case (25): return (P1IN_bits.P1IN4);             //P1.4, TA0.3
        case (26): return (P1IN_bits.P1IN5);             //P1.5, TA0.4
        case (27): return (P1IN_bits.P1IN6);             //P1.6, TA1CLK, CBOUT
        case (28): return (P1IN_bits.P1IN7);             //P1.7, TA1.0
        case (29): return (P2IN_bits.P2IN0);             //P2.0, TA1.1
        case (30): return (P2IN_bits.P2IN1);             //P2.1, TA1.2
        case (31): return (P2IN_bits.P2IN2);             //P2.2, TA2CLK, SMCLK
        case (32): return (P2IN_bits.P2IN3);             //P2.3, TA2.0
        case (33): return (P2IN_bits.P2IN4);             //P2.4, TA2.1
        case (34): return (P2IN_bits.P2IN5);             //P2.5, TA2.2
        case (35): return (P2IN_bits.P2IN6);             //P2.6, RTCCLK, DMAE0
        case (36): return (P2IN_bits.P2IN7);             //P2.7, UCB0STE, UCA0CLK
        case (37): return (P3IN_bits.P3IN0);             //P3.0, UCB0SIMO, UCB0SDA
        case (38): return (P3IN_bits.P3IN1);             //P3.1, UCB0SOMI, UCB0SCL
        case (39): return (P3IN_bits.P3IN2);             //P3.2, UCB0CLK, UCA0STE
        case (40): return (P3IN_bits.P3IN3);             //P3.3, UCA0TXD, UCA0SIMO
        case (41): return (P3IN_bits.P3IN4);             //P3.4, UCA0RXD, UCA0SOMI
        case (42): return (P3IN_bits.P3IN5);             //P3.5, TB0.5
        case (43): return (P3IN_bits.P3IN6);             //P3.6, TB0.6
        case (44): return (P3IN_bits.P3IN7);             //P3.7, TB0OUTH, SVMOUT
        case (45): return (P4IN_bits.P4IN0);             //P4.0, PM_UCB1STE, PM_UCA1CLK
        case (46): return (P4IN_bits.P4IN1);             //P4.1, PM_UCB1SIMO, PM_UCB1SDA
        case (47): return (P4IN_bits.P4IN2);             //P4.2, PM_UCB1SOMI, PM_UCB1SCL
        case (48): return (P4IN_bits.P4IN3);             //P4.3, PM_UCB1CLK, PM_UCA1STE
        case (51): return (P4IN_bits.P4IN4);             //P4.4, PM_UCA1TXD, PM_UCA1SIMO
        case (52): return (P4IN_bits.P4IN5);             //P4.5, PM_UCA1RXD, PM_UCA1SOMI
        case (53): return (P4IN_bits.P4IN6);             //P4.6, PM_NONE
        case (54): return (P4IN_bits.P4IN7);             //P4.7, PM_NONE
        case (55): return (P5IN_bits.P5IN6);             //P5.6, TB0.0
        case (56): return (P5IN_bits.P5IN7);             //P5.7, TB0.1
        case (57): return (P7IN_bits.P7IN4);             //P7.4, TB0.2
        case (58): return (P7IN_bits.P7IN5);             //P7.5, TB0.3
        case (59): return (P7IN_bits.P7IN6);             //P7.6, TB0.4
        case (60): return (P7IN_bits.P7IN7);             //P7.7, TB0CLK, MCLK
        case (69): return (P5IN_bits.P5IN2);             //P5.2, XT2IN
        case (70): return (P5IN_bits.P5IN3);             //P5.3, XT2OUT
        case (77): return (P6IN_bits.P6IN0);             //P6.0, CB0, A0
        case (78): return (P6IN_bits.P6IN1);             //P6.1, CB1, A1
        case (79): return (P6IN_bits.P6IN2);             //P6.2, CB2, A2
        case (80): return (P6IN_bits.P6IN3);             //P6.3, CB3, A3
        default: return 0xFF;
    }
}


/******************************************************************************
    Subroutine:     pinValid
    Description:    Function to determine if the specified GPIO pin is valid.
    Inputs:         pin (uint8_t) is a value between 1 and 80, corresponding to
                    a GPIO pin, based on the physical package.
    Outputs:        uint8_t return value.
                    For legal pin values, the return value will be 1.
                    For illegal pin values, the return value will be 0.

******************************************************************************/
uint8_t pinValid(uint8_t pin)
{
    switch(pin)
    {
        case (1):  //P6.4, CB4, A4
        case (2):  //P6.5, CB5, A5
        case (3):  //P6.6, CB6, A6
        case (4):  //P6.7, CB7, A7
        case (5):  //P7.0, CB8, A12
        case (6):  //P7.1, CB9, A13
        case (7):  //P7.2, CB10, A14
        case (8):  //P7.3, CB11, A15
        case (9):  //P5.0, A8, VREF+, VeREF+
        case (10): //P5.1, A9, VREF-, VeREF-
        case (12): //P5.4, XIN
        case (13): //P5.5, XOUT
        case (15): //P8.0
        case (16): //P8.1
        case (17): //P8.2
        case (21): //P1.0, TA0CLK, ACLK
        case (22): //P1.1, TA0.0
        case (23): //P1.2, TA0.1
        case (24): //P1.3, TA0.2
        case (25): //P1.4, TA0.3
        case (26): //P1.5, TA0.4
        case (27): //P1.6, TA1CLK, CBOUT
        case (28): //P1.7, TA1.0
        case (29): //P2.0, TA1.1
        case (30): //P2.1, TA1.2
        case (31): //P2.2, TA2CLK, SMCLK
        case (32): //P2.3, TA2.0
        case (33): //P2.4, TA2.1
        case (34): //P2.5, TA2.2
        case (35): //P2.6, RTCCLK, DMAE0
        case (36): //P2.7, UCB0STE, UCA0CLK
        case (37): //P3.0, UCB0SIMO, UCB0SDA
        case (38): //P3.1, UCB0SOMI, UCB0SCL
        case (39): //P3.2, UCB0CLK, UCA0STE
        case (40): //P3.3, UCA0TXD, UCA0SIMO
        case (41): //P3.4, UCA0RXD, UCA0SOMI
        case (42): //P3.5, TB0.5
        case (43): //P3.6, TB0.6
        case (44): //P3.7, TB0OUTH, SVMOUT
        case (45): //P4.0, PM_UCB1STE, PM_UCA1CLK
        case (46): //P4.1, PM_UCB1SIMO, PM_UCB1SDA
        case (47): //P4.2, PM_UCB1SOMI, PM_UCB1SCL
        case (48): //P4.3, PM_UCB1CLK, PM_UCA1STE
        case (51): //P4.4, PM_UCA1TXD, PM_UCA1SIMO
        case (52): //P4.5, PM_UCA1RXD, PM_UCA1SOMI
        case (53): //P4.6, PM_NONE
        case (54): //P4.7, PM_NONE
        case (55): //P5.6, TB0.0
        case (56): //P5.7, TB0.1
        case (57): //P7.4, TB0.2
        case (58): //P7.5, TB0.3
        case (59): //P7.6, TB0.4
        case (60): //P7.7, TB0CLK, MCLK
        case (69): //P5.2, XT2IN
        case (70): //P5.3, XT2OUT
        case (77): //P6.0, CB0, A0
        case (78): //P6.1, CB1, A1
        case (79): //P6.2, CB2, A2
        case (80): //P6.3, CB3, A3
        {
            return 1u;
        }

        default: return 0u;
    }
}



/******************************************************************************
	End of File: MSP430F5529LP_GPIO.c
******************************************************************************/
