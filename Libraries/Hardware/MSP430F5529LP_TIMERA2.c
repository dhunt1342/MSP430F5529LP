
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
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
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


/******************************************************************************
    PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/


/******************************************************************************
    PRIVATE VARIABLES (static)
******************************************************************************/

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//                  ---- READ ME - DEBUGGING INFO ----
//
//  There is a bug in CCS ver 6, where static (file scope) variables can not
//  be viewed in the debug watch window. It is bad programming style to make
//  these variables permanently global, so here is a middle-of-the-road
//  solution. If it is necesary to debug variables in this file, comment the
//  line "#define STATIC static", and uncomment the line "#define STATIC".
//  When you are done debugging, put it back the way it was.
//  #define STATIC
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#define STATIC static


    STATIC  uint16_t    s_CurrentTick;
    STATIC  uint32_t    s_CurrentTick32;


/******************************************************************************
    Subroutine:     MSP430F5529LP_TIMERA2_Initialize
    Description:
    Inputs:         None
    Outputs:        None

******************************************************************************/
void MSP430F5529LP_TIMERA2_Initialize(void)
{
    // Setup Timer A2
    TA2CCTL0_bits.CCIE = 1;         // CCR0 interrupt enabled
    TA2CTL_bits.TACLR = 1;          // Clear
    TA2CTL_bits.MCx = 1;            // upmode
    TA2CTL_bits.TASSELx = 2;        // SMCLK
    TA2CTL_bits.IDx = 0;            // divide by 0
    TA2CCR0 = 24000;                // 1ms
    
    s_CurrentTick = 0;
    s_CurrentTick32 = 0; 

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
    s_CurrentTick++;
    s_CurrentTick32++;
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
                  (GetTick or stop), which is compared against a desired elapsed
                  time.   
   Inputs:        start, stop (16-bit values)
   Outputs:       stop-start (difference)

******************************************************************************/
uint16_t Elapse(uint16_t start, uint16_t stop)
{
   return stop - start;
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
   
   __disable_interrupt();
  
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
    return stop - start;
}


/******************************************************************************
	End of File: MSP430F5529LP_TIMERA2.c
******************************************************************************/
