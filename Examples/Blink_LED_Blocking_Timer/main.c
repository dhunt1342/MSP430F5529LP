
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
 * development board using the arduino style blocking delay function provided
 * in the TIMERA2 peripheral files.
 *
 * This example code demonstrates how to use basic "delay" functionality to
 * perform tasks. These can make it extremely simple to write a small program.
 * However, this example code also spends all of its time doing nothing but
 * performing this task, which is a significant waste of the processor's
 * capability.
 *
 * An alternative method would be to use non-blocking delays, and allow the
 * main loop to perform other tasks until the delay expires. This will be
 * explained in a separate non-blocking delay example.
 *
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
 * Rev. 1.1, Minor editorial updates and cleanup
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


/******************************************************************************
   PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/

    static void initialize(void);


/******************************************************************************
   PRIVATE VARIABLES (static)
******************************************************************************/



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
        delay(500);                 // blocking delay of 1/2 second
        P1OUT_bits.P1OUT0 ^= 1;     // Toggle P1.0 (LED1)
        delay(500);                 // blocking delay of 1/2 second
        P1OUT_bits.P1OUT0 ^= 1;     // Toggle P1.0 (LED1)
        P4OUT_bits.P4OUT7 ^= 1;     // Toggle P4.7 (LED2)
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


    // ###################################################################
    // Last step before exiting, enable global interrupts

    __enable_interrupt();

    // IMPORTANT: Even though the main code does not use interrupts in this
    // example, it is necessary to enable interrupts so that the rest of the
    // operating environment operates correctly.
}


/******************************************************************************
   End of File: main.c
******************************************************************************/
