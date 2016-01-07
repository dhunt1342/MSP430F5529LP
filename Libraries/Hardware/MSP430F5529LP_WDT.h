
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
 * FileName:      MSP430F5529LP_WDT.h
 *
 * This file provides functions for the Watchdog module on the
 * Texas Instruments MSP430F5529 Launchpad development board.
 *
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
 *
 *                                                                            */
/* ===========================================================================*/

#ifndef __MSP430F5529LP_WDT_H__
#define __MSP430F5529LP_WDT_H__


/******************************************************************************
    PUBLIC DEFINITIONS
******************************************************************************/

    typedef void (*WDT_Callback) (void);

    typedef struct
    {
        uint16_t        timeout;
        WDT_Callback    callback;
    } WDT_Callback_t;


/******************************************************************************
    PUBLIC FUNCTION PROTOTYPES
******************************************************************************/

   void MSP430F5529LP_WDT_Initialize(void);
   
   void Set_WDT_Timer(uint16_t index, uint16_t timeout, WDT_Callback callback);


/******************************************************************************
    PUBLIC VARIABLES (extern)
******************************************************************************/



/******************************************************************************
	End MSP430F5529LP_WDT.h
******************************************************************************/

#endif   // __MSP430F5529LP_WDT_H__

