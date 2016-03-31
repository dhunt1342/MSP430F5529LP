
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
 * <write a basic description of the program here>
 *
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
 *
 *                                                                            */
/* ===========================================================================*/

#include "MSP430F5529LP.h"
#include "MSP430F5529LP_CLOCK.h"
#include "MSP430F5529LP_TIMERA2.h"


/******************************************************************************
   PUBLIC DEFINITIONS
******************************************************************************/


/******************************************************************************
   PUBLIC VARIABLES
******************************************************************************/


/******************************************************************************
   PRIVATE DEFINITIONS (static const)
******************************************************************************/

typedef enum {
    LED_STATE_1,
    LED_STATE_2,
    LED_STATE_3,
    LED_STATE_4
} LED_States_t;



/******************************************************************************
   PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/

    static void initialize(void);


/******************************************************************************
   PRIVATE VARIABLES (static)
******************************************************************************/

    LED_States_t LED_State;


/******************************************************************************
    Subroutine:     main
    Description:    program entry point at startup.
    Inputs:         None
    Outputs:        0

******************************************************************************/
int main( void )
{
    uint16_t    start;

    // perform initialization
    initialize();

    LED_State = LED_STATE_1;
    start = GetTick();

    for (;;)    // Loop forever...
    {
        switch (LED_State)
        {
            case (LED_STATE_1):
            {
                if (50 <= Elapse(start, GetTick()))
                {
                    P1OUT_bits.P1OUT0 ^= 1;     // Toggle P1.0 (LED1)
                    start = GetTick();
                    LED_State = LED_STATE_2;
                }
            }
            break;

            case (LED_STATE_2):
            {
                if (500 <= Elapse(start, GetTick()))
                {
                    P1OUT_bits.P1OUT0 ^= 1;     // Toggle P1.0 (LED1)
                    P4OUT_bits.P4OUT7 ^= 1;     // Toggle P4.7 (LED2)
                    start = GetTick();
                    LED_State = LED_STATE_3;
                }
            }
            break;

            case (LED_STATE_3):
            {
                if (50 <= Elapse(start, GetTick()))
                {
                    P4OUT_bits.P4OUT7 ^= 1;     // Toggle P4.7 (LED2)
                    start = GetTick();
                    LED_State = LED_STATE_4;
                }
            }
            break;

            case (LED_STATE_4):
            {
                if (500 <= Elapse(start, GetTick()))
                {
                    P1OUT_bits.P1OUT0 ^= 1;     // Toggle P1.0 (LED1)
                    P4OUT_bits.P4OUT7 ^= 1;     // Toggle P4.7 (LED2)
                    start = GetTick();
                    LED_State = LED_STATE_1;
                }
            }
            break;

        }

    }

    return 0;
}


/******************************************************************************
    Subroutine:     initialize
    Description:    Performs the initalization of the main program. This also
                    initializes the MSP430F5529LP operating environment.
    Inputs:         None
    Outputs:        None

******************************************************************************/
void initialize(void)
{
    // ###################################################################
    // This section initializes the operating environment

    WDTCTL = WDTPW + WDTHOLD;   // Stop the watchdog timer
    MSP430F5529LP_CLOCK_Initialize();
    MSP430F5529LP_TIMERA2_Initialize();


    // ###################################################################
    // Add program specific initialization here

    // Enable the Debug LEDs
    P1DIR_bits.P1DIR0 = 1;         // Set P1.0 (LED1) to an Output
    P4DIR_bits.P4DIR7 = 1;         // Set P4.7 (LED2) to an Output
    P1OUT_bits.P1OUT0 = 0;         // Set P1.0 initial value
    P4OUT_bits.P4OUT7 = 1;         // Set P4.7 initial value


    // Even though the main code does not use interrupts in this example, it
    // is necessary to enable interrupts so that the rest of the operating
    // environment operates correctly.
    __enable_interrupt();
}


/******************************************************************************
   End of File: main.c
******************************************************************************/
