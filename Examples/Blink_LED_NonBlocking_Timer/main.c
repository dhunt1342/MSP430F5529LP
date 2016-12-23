
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
 * This program blinks the LEDs on the Texas Instruments MSP430F5529 Launchpad
 * development board using a non-blocking delay function using the GetTick and
 * Elapse functions in the TIMER_A2 peripheral files. This demonstrates how to
 * use a more versatile delay function than the basic "delay".
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
    LED_STATE_2
} LED_States_t;



/******************************************************************************
   PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/

    static void initialize(void);


/******************************************************************************
   PRIVATE VARIABLES (static)
******************************************************************************/

    static LED_States_t LED_State;
    static uint16_t start;


/******************************************************************************
    Subroutine:     main
    Description:    program entry point at startup.
    Inputs:         None
    Outputs:        0

******************************************************************************/
int main( void )
{
    // perform initialization
    initialize();

    for (;;)    // Loop forever...
    {
        switch (LED_State)
        {
            case (LED_STATE_1):
            {
                if (Expired(500, start, GetTick()))
                {
                    P1OUT_bits.P1OUT0 ^= 1;     // toggle P1.0 (LED1)
                    start = GetTick();          // collect new start time
                    LED_State = LED_STATE_2;    // advance to state 2
                }
            }
            break;

            case (LED_STATE_2):
            {
                if (Expired(500, start, GetTick()))
                {
                    P1OUT_bits.P1OUT0 ^= 1;     // toggle P1.0 (LED1)
                    P4OUT_bits.P4OUT7 ^= 1;     // toggle P4.7 (LED2)
                    start = GetTick();          // collect new start time
                    LED_State = LED_STATE_1;    // advance to state 1
                }
            }
            break;

            default:
            {
                start = GetTick();          // collect new start time
                LED_State = LED_STATE_1;    // advance to state 1
            }

        }   // end switch (LED_State)
    }   // end for (;;)

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
    // Add operating environment initialization here

    MSP430F5529LP_CLOCK_Initialize();
    MSP430F5529LP_TIMERA2_Initialize();


    // ###################################################################
    // Add program specific initialization here

    // Enable the Debug LEDs
    P1DIR_bits.P1DIR0 = 1;         // Set P1.0 (LED1) to an Output
    P4DIR_bits.P4DIR7 = 1;         // Set P4.7 (LED2) to an Output
    P1OUT_bits.P1OUT0 = 0;         // Set P1.0 initial value
    P4OUT_bits.P4OUT7 = 1;         // Set P4.7 initial value


    LED_State = LED_STATE_1;    // Initialize the main loop state machine
    start = GetTick();          // Collect the inital start time


    // ###################################################################
    // Last step before exiting, enable global interrupts

    __enable_interrupt();
}


/******************************************************************************
   End of File: main.c
******************************************************************************/
