
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
 * FileName:      MSP430F5529LP_WDT.c
 *
 * This file provides functions for the Watchdog module in the
 * Texas Instruments MSP430F5529 Launchpad development board.
 *
 * Version 1.1
 *
 * Rev. 1.0, Initial Release
 * Rev. 1.1, Updated static variable debugging info
 * Rev. 1.2, Moved WDT_Callback_t structure out of .h into .c
 *
 *                                                                            */
/* ===========================================================================*/

#include "MSP430F5529LP.h"
#include "MSP430F5529LP_WDT.h"


/******************************************************************************
   PUBLIC DEFINITIONS
******************************************************************************/


/******************************************************************************
   PUBLIC VARIABLES
******************************************************************************/


/******************************************************************************
   PRIVATE DEFINITIONS (static const)
******************************************************************************/

    // This defines the number of WDT timer callback functions that can be
    // registered at the same time. This value can be increased to accommodate
    // more timers as needed.

    #define MAX_WDT_TIMERS  3

    typedef struct
    {
        uint16_t        timeout;
        WDT_Callback    callback;
    } WDT_Callback_t;


/******************************************************************************
   PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/


/******************************************************************************
   PRIVATE VARIABLES (static)
******************************************************************************/

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//                  ---- READ ME - DEBUGGING INFO ----
//
//  To view file scope static variables in the CCS debug watch window, the
//  following syntax must be used. 'filename.c'::variableName
//  The filename must be the full filename including the .c extension and
//  must be surrounded by the single quotes, followed by a double-colon.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

     static volatile WDT_Callback_t  WDT_timers[MAX_WDT_TIMERS];


/******************************************************************************
    Subroutine:     MSP430F5529LP_WDT_Initialize
    Description:    Initializes the watchdog timer in interval mode with a
                    1 second timeout interval.
    Inputs:         None
    Outputs:        None

******************************************************************************/
void MSP430F5529LP_WDT_Initialize(void)
{
    // Stop the watchdog timer
    WDTCTL = WDTPW + WDTHOLD;

    // Restart the watchdog in the interval timer mode, running from ACLK at
    // 32.768 KHz, with a timeout interval of 1 second.
    WDTCTL = WDTPW + WDTSSEL0 + WDTTMSEL + WDTIS2;

    // Enable interrupts from the WDT interval timer
    SFRIE1_bits.WDTIE = 1;
}


/******************************************************************************
    Subroutine:     Set_WDT_Timer
    Description:    Use this function to create a watchdog timer, and register
                    the callback function to be executed when it expires.
    Inputs:         Index: The index of the WDT_timers[] array to place the
                    new WDT timer being registered. Valid values are from
                    zero to MAX_WDT_TIMERS-1.
                    timeout: The timeout value of the new timer in seconds.
                    For example, a value of 10, will expire after 10 seconds.
                    callback: The name of the function that will be called
                    when the registered timer expires.
    Outputs:        None

******************************************************************************/
void Set_WDT_Timer(uint16_t index, uint16_t timeout_in_sec, WDT_Callback callback)
{
    // If the index provided exceeds the size of WDT_timers, just exit.
    if (MAX_WDT_TIMERS <= index)    {return;}

    // Otherwise, register the new timer at the index position provided.
    WDT_timers[index].timeout = timeout_in_sec;
    WDT_timers[index].callback = callback;

}


/******************************************************************************
    Subroutine:     WDT_ISR
    Description:    Interrupt service routine for the watchdog interval timer.
                    If there are active WDT timers registered, the values will
                    be decremented, and upon expiration, the registered
                    callback function will be called. After a timer has
                    expired, it must be activated again with Set_WDT_Timer().
    Inputs:         None
    Outputs:        None

******************************************************************************/
void __attribute__((__interrupt__(WDT_VECTOR))) WDT_ISR(void)
{
    uint16_t    x;

    // Loop through all of the WDT timers
    for (x=0u; x<MAX_WDT_TIMERS; x++)
    {
        // If the current timer is active (not 0)...
        if (0u < WDT_timers[x].timeout)
        {
            // Decrement the timer
            WDT_timers[x].timeout--;

            // If the timer expired (just transitioned to 0)...
            if (0u == WDT_timers[x].timeout)
            {
                // Call the registered callback function
                WDT_timers[x].callback();
            }
        }
    }
}


/******************************************************************************
	End of File: MSP430F5529LP_WDT.c
******************************************************************************/
