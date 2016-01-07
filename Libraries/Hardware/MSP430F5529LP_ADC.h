
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
 * FileName:      MSP430F5529LP_ADC.h
 *
 * This file provides functions for the 12-bit Analog to Digital Converter
 * (ADC12) module for the Texas Instruments MSP430F5529 Launchpad development
 * board.
 *
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
 *
 *                                                                            */
/* ===========================================================================*/

#ifndef __MSP430F5529LP_ADC_H__
#define __MSP430F5529LP_ADC_H__


/******************************************************************************
    PUBLIC DEFINITIONS
******************************************************************************/

    typedef void (*ADC_Callback) (void);


/******************************************************************************
    PUBLIC FUNCTION PROTOTYPES
******************************************************************************/

    void MSP430F5529LP_ADC_Initialize(void);

    void ADC_SetChannel(uint8_t mem, uint8_t channel, uint8_t eos);

    void ADC_RegisterErrorCallback(ADC_Callback callback);

    void ADC_RegisterConversionCallback(ADC_Callback callback);



/******************************************************************************
    PUBLIC VARIABLES (extern)
******************************************************************************/


/******************************************************************************
	End MSP430F5529LP_ADC.h
******************************************************************************/

#endif   // __MSP430F5529LP_ADC_H__

