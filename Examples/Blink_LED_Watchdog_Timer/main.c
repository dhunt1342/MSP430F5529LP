
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
 * development board using the Watchdog Interval timer. This demonstrates how
 * the WDT Timer functions provided can be used to set long duration timeout
 * timers. In this example, two callback functions are registered with a
 * timeout value of 1 second, which then sets a flag used by the main loop to
 * trigger the toggling of the respective LED. Each time the registered timer
 * expires, it is re-registered for another 1 second period. This creates the
 * continuous blinking pattern.
 *
 * Although this example uses the minimum WDT Timer value of 1 second, the WDT
 * Timers are intended to be long duration timers. The maximum value of 65535
 * is approx. 18 hours.
 *
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
 *
 *                                                                            */
/* ===========================================================================*/

#include "MSP430F5529LP.h"


/******************************************************************************
   PUBLIC DEFINITIONS
******************************************************************************/


/******************************************************************************
   PUBLIC VARIABLES
******************************************************************************/

    // These flags are set by the callback functions to indicate to the main
    // loop that it is time to perform an action. Although this example is very
    // small, and it would be possible to have the interrupt perform these
    // actions, it is good to get used to not performing too many tasks
    // within the interrupts. This makes it easier when the designs start
    // becoming very heavily interrupt driven.

    uint16_t    LED1_toggle_flag;
    uint16_t    LED2_toggle_flag;


/******************************************************************************
   PRIVATE DEFINITIONS (static const)
******************************************************************************/


/******************************************************************************
   PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/

    static void initialize(void);

    void LED1_timeout(void);

    void LED2_timeout(void);


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
        // If the LED1 toggle flag is set...
        if (LED1_toggle_flag)
        {
            LED1_toggle_flag = 0u;      // Clear the flag
            P1OUT_bits.P1OUT0 ^= 1;     // Toggle P1.0 (LED1)
        }
        // If the LED2 toggle flag is set...
        if (LED2_toggle_flag)
        {
            LED2_toggle_flag = 0u;      // Clear the flag
            P4OUT_bits.P4OUT7 ^= 1;     // Toggle P4.7 (LED2)
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
    MSP430F5529LP_WDT_Initialize();


    // ###################################################################
    // Add program specific initialization here

    // Enable the Debug LEDs
    P1DIR_bits.P1DIR0 = 1;         // Set P1.0 (LED1) to an Output
    P4DIR_bits.P4DIR7 = 1;         // Set P4.7 (LED2) to an Output
    P1OUT_bits.P1OUT0 = 0;         // Set P1.0 initial value
    P4OUT_bits.P4OUT7 = 1;         // Set P4.7 initial value

    // Initialize the variables
    LED1_toggle_flag = 0u;
    LED2_toggle_flag = 0u;

    // Register the initial WDT Timers at 1 second
    Set_WDT_Timer(0, 1, LED1_timeout);
    Set_WDT_Timer(1, 1, LED2_timeout);

    __enable_interrupt();
}


/******************************************************************************
    Subroutine:     LED1_timeout
    Description:    This is the callback function for the LED1 WDT Timer
    Inputs:         None
    Outputs:        None

******************************************************************************/
void LED1_timeout(void)
{
    // Set the toggle flag. This lets the main loop know that it is time to
    // toggle the LED. Re-register the LED1 timer for another 1 second.
    LED1_toggle_flag = 1u;
    Set_WDT_Timer(0, 1, LED1_timeout);
}


/******************************************************************************
    Subroutine:     LED2_timeout
    Description:    This is the callback function for the LED2 WDT Timer
    Inputs:         None
    Outputs:        None

******************************************************************************/
void LED2_timeout(void)
{
    // Set the toggle flag. This lets the main loop know that it is time to
    // toggle the LED. Re-register the LED2 timer for another 1 second.
    LED2_toggle_flag = 1u;
    Set_WDT_Timer(1, 1, LED2_timeout);
}


/******************************************************************************
   End of File: main.c
******************************************************************************/
