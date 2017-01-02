
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
 * FileName:      MSP430F5529LP_TIMERA2.c
 *
 * This file provides functions for the Timer A2 module in the
 * Texas Instruments MSP430F5529 Launchpad development board.
 *
 * Version 1.1
 *
 * Rev. 1.0, Initial Release
 * Rev. 1.1, Updated static variable debugging info
 * Rev. 2.0, Modified Set_Button_Service parameters to allow the Button module
 * to set the button service update interval. Added the Expired and Expired32
 * functions. made other minor editorial updates.
 *
 *                                                                            */
/* ===========================================================================*/

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

    typedef void (*TIMERA2_Button_Service) (void);

    static TIMERA2_Button_Service TimerA2_ButtonService;

    static uint16_t TimerA2_ButtonInterval;


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

    static  volatile uint16_t    s_CurrentTick;
    static  volatile uint32_t    s_CurrentTick32;


/******************************************************************************
    Subroutine:     MSP430F5529LP_TIMERA2_Initialize
    Description:    Initializes Timer A2 in up mode with a 1 millisecond
                    timeout interval.
    Inputs:         None
    Outputs:        None

******************************************************************************/
void MSP430F5529LP_TIMERA2_Initialize(void)
{
    // Setup Timer A2 to generate an interrupt every 1 ms.
    TA2CCTL0_bits.CCIE = 1;         // CCR0 interrupt enabled
    TA2CTL_bits.TACLR = 1;          // clear
    TA2CTL_bits.MCx = 1;            // upmode
    TA2CTL_bits.TASSELx = 2;        // SMCLK
    TA2CTL_bits.IDx = 0;            // divided by 1
    TA2CCR0 = 24000;                // 1ms
    
    // Initialize the current tick counters
    s_CurrentTick = 0;
    s_CurrentTick32 = 0; 

    // Initialize the button service (as inactive)
    TimerA2_ButtonService = (TIMERA2_Button_Service)NULL;
    TimerA2_ButtonInterval = 16;
}


/******************************************************************************
    Subroutine:     TIMER2_A0_ISR
    Description:    Timer A2 interrupt service routine for CC0 vector. This
                    ISR is configured to fire every 1ms. 
    Inputs:         None
    Outputs:        None     

******************************************************************************/
void __attribute__((__interrupt__(TIMER2_A0_VECTOR))) TIMER2_A0_ISR(void)
{
    // Increment each of the tick counters
    s_CurrentTick++;
    s_CurrentTick32++;

    // Check to see if button service was enabled. If so...
    if (NULL != TimerA2_ButtonService)
    {
        // and if the current tick is at the button interval...
        if (0 == (s_CurrentTick % TimerA2_ButtonInterval))
        {
            // call the button service in the button library module
            TimerA2_ButtonService();
        }
    }
}


/******************************************************************************
   Subroutine:    delay
   Description:   Provides an arduino style blocking delay function that takes 
                  a desired delay time in milliseconds, and returns when the
                  delay time expires.  
   Inputs:        uint16_t ms (number of milliseconds to delay)
   Outputs:       None

   Caution:       Actual delay times will be between +0 and +1 ms beyond the
                  requested delay value. 
******************************************************************************/
void delay(uint16_t ms)
{
    static uint16_t start;
    start = GetTick();
    while (ms >= Elapse(start, GetTick()))
    {
    	asm("NOP");
    }
}


/******************************************************************************
   Subroutine:    GetTick
   Description:   Provides public read-only access to the current 1ms tick
                  counter (16-bit). This should be used as the default, unless 
                  delays longer than 65.5 seconds are needed. 
   Inputs:        None
   Outputs:       s_CurrentTick

******************************************************************************/
uint16_t GetTick(void)
{
   return s_CurrentTick;
}


/******************************************************************************
   Subroutine:    Elapse
   Description:   Provides a public method to get the difference between two
                  16-bit values. The intention is that a tick value will be 
                  saved (start), and then compared against the current tick
                  (GetTick or stop), which is compared against a desired
                  elapsed time.
   Inputs:        start, stop (16-bit values)
   Outputs:       stop-start (difference)

******************************************************************************/
uint16_t Elapse(uint16_t start, uint16_t stop)
{
   return (stop - start);
}


/******************************************************************************
   Subroutine:    Expired
   Description:   Provides a public method to determine whether the difference
                  between two 16-bit values (stop - start) is greater than or
                  equal to the target duration. The intented use is that a tick
                  value will be saved (start), and then compared against the
                  current tick (GetTick or stop), which is compared against a
                  desired elapsed time.
   Inputs:        duration, start, stop (16-bit values)
   Outputs:       false if the difference (stop-start) is not greater than or
                  equal to the duration. true otherwise.

******************************************************************************/
uint16_t Expired(uint16_t duration, uint16_t start, uint16_t stop)
{
   return (duration <= (stop - start));
}


/******************************************************************************
   Subroutine:    millis
   Description:   Provides an arduino style library function that returns the
                  number of milliseconds since the program started. Roll-over
                  occurs at approximately 50 days.  
   Inputs:        None
   Outputs:       s_CurrentTick32 (milliseconds since start)

******************************************************************************/
uint32_t millis(void)
{
  return GetTick32();
}

/******************************************************************************
   Subroutine:    GetTick32
   Description:   Provides public read-only access to the current 1ms tick
                  counter (32-bit). This requires access protection since it
                  exceeds the intrinsic processor size. This should only be 
                  used for delays over 65.5 seconds. Roll-over occurs after
                  approximately 50 days.  
   Inputs:        None
   Outputs:       s_CurrentTick32

******************************************************************************/
uint32_t GetTick32(void)
{
   static uint32_t retVal;
   
   /* The MSP430 is a 16-bit processor. 32-bit operations are not atomic and
    * can be interrupted resulting in incorrect behavior. Disable interrupts
    * first before proceeding.
    */
   __disable_interrupt();

   // IMPORTANT: one NOP is required after __disable_interrupt to ensure that
   // interrupts are truly disabled before continuing execution!
   asm("NOP");
  
   retVal = s_CurrentTick32;
   
   __enable_interrupt();
   
   return retVal;
}


/******************************************************************************
   Subroutine:    Elapse32
   Description:   Provides a public method to get the difference between two
                  32-bit values. The intention is that a tick value will be 
                  saved (start), and then compared against the current tick
                  (GetTick32 or stop), which is compared against a desired 
                  elapsed time.
   Inputs:        start, stop (32-bit values)
   Outputs:       stop-start (difference 32-bit)

******************************************************************************/
uint32_t Elapse32(uint32_t start, uint32_t stop)
{
    static uint32_t retVal;

    /* The MSP430 is a 16-bit processor. 32-bit operations are not atomic and
     * can be interrupted resulting in incorrect behavior. Disable interrupts
     * first before proceeding.
     */
    __disable_interrupt();

    // IMPORTANT: one NOP is required after __disable_interrupt to ensure that
    // interrupts are truly disabled before continuing execution!
    asm("NOP");

    retVal = stop - start;

    __enable_interrupt();

    return retVal;
}


/******************************************************************************
   Subroutine:    Expired32
   Description:   Provides a public method to determine whether the difference
                  between two 32-bit values (stop - start) is greater than or
                  equal to the target duration. The intented use is that a tick
                  value will be saved (start), and then compared against the
                  current tick (GetTick or stop), which is compared against a
                  desired elapsed time.
   Inputs:        duration, start, stop (32-bit values)
   Outputs:       false if the difference (stop-start) is not greater than or
                  equal to the duration. true otherwise.

******************************************************************************/
uint32_t Expired32(uint32_t duration, uint32_t start, uint32_t stop)
{
    static uint32_t retVal;

    /* The MSP430 is a 16-bit processor. 32-bit operations are not atomic and
     * can be interrupted resulting in incorrect behavior. Disable interrupts
     * first before proceeding.
     */
    __disable_interrupt();

    // IMPORTANT: one NOP is required after __disable_interrupt to ensure that
    // interrupts are truly disabled before continuing execution!
    asm("NOP");

    retVal = (duration <= (stop - start));

    __enable_interrupt();

    return retVal;
}


/******************************************************************************
    Subroutine:     Set_Button_Service
    Description:    This function provides a public method (although not
                    in the .h file) that allows the BUTTON library to create
                    a callback to a button service at a pre-defined interval.
    Inputs:         uint16_t intvl_ms: The interval defined in ms at which the
                    callback function will be executed.
                    void *callback: The address of the callback function to be
                    executed when the interval is reached.
    Outputs:        None

******************************************************************************/
void Set_Button_Service(uint16_t intvl_ms, TIMERA2_Button_Service callback)
{
    TimerA2_ButtonService = callback;
    TimerA2_ButtonInterval = intvl_ms;
}


/******************************************************************************
	End of File: MSP430F5529LP_TIMERA2.c
******************************************************************************/
