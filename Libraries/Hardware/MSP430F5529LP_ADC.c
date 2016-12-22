
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
 * FileName:      MSP430F5529LP_ADC.c
 *
 * This file provides functions for the 12-bit Analog to Digital Converter
 * (ADC12) module for the Texas Instruments MSP430F5529 Launchpad development
 * board.
 *
 * Version 1.1
 *
 * Rev. 1.0, Initial Release
 * Rev. 1.1, Updated static variable debugging info
 *
 *                                                                            */
/* ===========================================================================*/

#include "MSP430F5529LP.h"
#include "MSP430F5529LP_ADC.h"


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
//  To view file scope static variables in the CCS debug watch window, the
//  following syntax must be used. 'filename.c'::variableName
//  The filename must be the full filename including the .c extension and
//  must be surrounded by the single quotes, followed by a double-colon.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    static ADC_Callback     adc_error_callback;
    static ADC_Callback     adc_conv_callback;


/******************************************************************************
    Subroutine:     MSP430F5529LP_ADC_Initialize
    Description:
    Inputs:
    Outputs:

******************************************************************************/
void MSP430F5529LP_ADC_Initialize(void)
{
    // Start with ADC peripheral disabled
    ADC12CTL0_bits.ADC12ON = 0u;         // ADC Turn Off

    // Disable conversions required to write most registers
    ADC12CTL0_bits.ADC12ENC = 0u;        // Disable Conversions

    // Set ADC12CTL0 control register
    ADC12CTL0_bits.ADC12SHT0x = 6u;      // MEM0-7:  128 ADC12CLK cycles
    ADC12CTL0_bits.ADC12SHT1x = 6u;      // MEM8-15: 128 ADC12CLK cycles
    ADC12CTL0_bits.ADC12MSC = 1u;        // Multiple sample and conversion enabled
    ADC12CTL0_bits.ADC12REFON = 0u;      // Internal reference off
    ADC12CTL0_bits.ADC12OVIE = 0u;       // Disable memory overflow interrupt
    ADC12CTL0_bits.ADC12TOVIE = 0u;      // Disable cnvrsn time overflow interrupt

    // Set ADC12CTL1 control register
    ADC12CTL1_bits.ADC12CSTARTADDx = 0u; // Sequence starts at ADC12MEM0
    ADC12CTL1_bits.ADC12SHSx = 0u;       // Use internal ADC12 start conv bit
    ADC12CTL1_bits.ADC12SHP = 1u;        // Pulse mode using internal sampling timer
    ADC12CTL1_bits.ADC12ISSH = 0u;       // No signal inversion
    ADC12CTL1_bits.ADC12DIVx = 4u;       // Clock divide by 5 = 4.8MHz
    ADC12CTL1_bits.ADC12SSELx = 3u;      // Clock source = SMCLK
    ADC12CTL1_bits.ADC12CONSEQx = 1u;    // Mode = sequence of channels

    adc_error_callback = NULL;
    adc_conv_callback = NULL;

    P6DIR_bits.P6DIR0 = 0;
    P6DIR_bits.P6DIR1 = 0;
    P6DIR_bits.P6DIR2 = 0;

    // Enable the ADC Input Pins
    P6SEL_bits.P6SEL0 = 1;         // Set P6.0 Select Analog Input A0
    P6SEL_bits.P6SEL1 = 1;         // Set P6.1 Select Analog Input A1
    P6SEL_bits.P6SEL2 = 1;         // Set P6.2 Select Analog Input A2
    P6SEL_bits.P6SEL3 = 1;         // Set P6.3 Select Analog Input A3
    P6SEL_bits.P6SEL4 = 1;         // Set P6.4 Select Analog Input A4
    P6SEL_bits.P6SEL5 = 1;         // Set P6.5 Select Analog Input A5
    P6SEL_bits.P6SEL6 = 1;         // Set P6.6 Select Analog Input A6
    P6SEL_bits.P6SEL7 = 1;         // Set P6.7 Select Analog Input A7

    // Turn on and enable the ADC peripheral
    ADC12CTL0_bits.ADC12ON = 1u;         // ADC Turn On
    ADC12CTL0_bits.ADC12ENC = 1u;        // Enable Conversions
}

   
 /******************************************************************************
   Subroutine:    ADC_SetChannel
   Description:   
   Inputs:
   Outputs:

******************************************************************************/
void ADC_SetChannel(uint8_t mem, uint8_t channel, uint8_t eos)  
{
    // Disable conversions required to write most registers
    ADC12CTL0_bits.ADC12ENC = 0u;        // Disable Conversions

    switch(mem)
    {
        case (0):
            ADC12MCTL0_bits.ADC12INCHx = channel;
            ADC12MCTL0_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE0 = eos;
            ADC12IFG_bits.ADC12IFG0 = 0u;
            break;
        case (1):
            ADC12MCTL1_bits.ADC12INCHx = channel;
            ADC12MCTL1_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE1 = eos;
            ADC12IFG_bits.ADC12IFG1 = 0u;
            break;
        case (2):
            ADC12MCTL2_bits.ADC12INCHx = channel;
            ADC12MCTL2_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE2 = eos;
            ADC12IFG_bits.ADC12IFG2 = 0u;
            break;
        case (3):
            ADC12MCTL3_bits.ADC12INCHx = channel;
            ADC12MCTL3_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE3 = eos;
            ADC12IFG_bits.ADC12IFG3 = 0u;
            break;
        case (4):
            ADC12MCTL4_bits.ADC12INCHx = channel;
            ADC12MCTL4_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE4 = eos;
            ADC12IFG_bits.ADC12IFG4 = 0u;
            break;
        case (5):
            ADC12MCTL5_bits.ADC12INCHx = channel;
            ADC12MCTL5_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE5 = eos;
            ADC12IFG_bits.ADC12IFG5 = 0u;
            break;
        case (6):
            ADC12MCTL6_bits.ADC12INCHx = channel;
            ADC12MCTL6_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE6 = eos;
            ADC12IFG_bits.ADC12IFG6 = 0u;
            break;
        case (7):
            ADC12MCTL7_bits.ADC12INCHx = channel;
            ADC12MCTL7_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE7 = eos;
            ADC12IFG_bits.ADC12IFG7 = 0u;
            break;
        case (8):
            ADC12MCTL8_bits.ADC12INCHx = channel;
            ADC12MCTL8_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE8 = eos;
            ADC12IFG_bits.ADC12IFG8 = 0u;
            break;
        case (9):
            ADC12MCTL9_bits.ADC12INCHx = channel;
            ADC12MCTL9_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE9 = eos;
            ADC12IFG_bits.ADC12IFG9 = 0u;
            break;
        case (10):
            ADC12MCTL10_bits.ADC12INCHx = channel;
            ADC12MCTL10_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE10 = eos;
            ADC12IFG_bits.ADC12IFG10 = 0u;
            break;
        case (11):
            ADC12MCTL11_bits.ADC12INCHx = channel;
            ADC12MCTL11_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE11 = eos;
            ADC12IFG_bits.ADC12IFG11 = 0u;
            break;
        case (12):
            ADC12MCTL12_bits.ADC12INCHx = channel;
            ADC12MCTL12_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE12 = eos;
            ADC12IFG_bits.ADC12IFG12 = 0u;
            break;
        case (13):
            ADC12MCTL13_bits.ADC12INCHx = channel;
            ADC12MCTL13_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE13 = eos;
            ADC12IFG_bits.ADC12IFG13 = 0u;
            break;
        case (14):
            ADC12MCTL14_bits.ADC12INCHx = channel;
            ADC12MCTL14_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE14 = eos;
            ADC12IFG_bits.ADC12IFG14 = 0u;
            break;
        case (15):
            ADC12MCTL15_bits.ADC12INCHx = channel;
            ADC12MCTL15_bits.ADC12EOS = eos;
            ADC12IE_bits.ADC12IE15 = eos;
            ADC12IFG_bits.ADC12IFG15 = 0u;
            break;
        default:
            // Do nothing. If the channel passed into the function was not valid
            // no action will be taken, no error will be returned.
            break;
    }
   ADC12CTL0_bits.ADC12ENC = 1u;        // Enable Conversions
}


/******************************************************************************
    Subroutine:     ADC_RegisterErrorCallback
    Description:    Use this function to register a function to be called in
                    the event that the ADC ISR fires for an overflow error.
                    If there is no desire to take action based on these events
                    it is not necessary to register a callback function. These
                    flags will be cleared upon reading the ADCIV register.
    Inputs:         callback is a function pointer to a function that takes
                    a uint16_t argument representing the ADC vector, and
                    returns no arguments.
    Outputs:        None

******************************************************************************/
void ADC_RegisterErrorCallback(ADC_Callback callback)
{
    adc_error_callback = callback;
}


/******************************************************************************
    Subroutine:     ADC_RegisterConversionCallback
    Description:    Use this function to register a function to be called in
                    the event that the ADC ISR fires for conversion completion.
                    In order to use the ADC, it is expected that a function
                    will be registered here. (otherwise, what's the point?)
                    The MEMx flag that fired the ISR must be cleared by either
                    reading the associated ADC12MEMx register, or by clearing
                    the flag explicitly.
    Inputs:         callback is a function pointer to a function that takes
                    a uint16_t argument representing the ADC vector, and
                    returns no arguments.
    Outputs:        None

******************************************************************************/
void ADC_RegisterConversionCallback(ADC_Callback callback)
{
    adc_conv_callback = callback;
}


/******************************************************************************
    Subroutine:     ADC_ISR
    Description:    Interrupt service routine for the watchdog interval timer.
                    If there are active WDT timers registered, the values will
                    be decremented, and upon expiration, the registered
                    callback function will be called. After a timer has
                    expired, it must be activated again with Set_WDT_Timer().
    Inputs:         None
    Outputs:        None

******************************************************************************/
void __attribute__((__interrupt__(ADC12_VECTOR))) ADC_ISR(void)
{
    static uint16_t ADC12IV_value;

    ADC12IV_value = ADC12IV;

    switch (ADC12IV_value)
    {
        case (ADC12IV_ADC12MEMx_OVFL):
        case (ADC12IV_ADC12CONV_OVFL):
            if (NULL != adc_error_callback)
            {
                // Call the ADC error/overflow callback function
                adc_error_callback();
            }
            break;
        case (ADC12IV_ADC12MEM0_IFG):
        case (ADC12IV_ADC12MEM1_IFG):
        case (ADC12IV_ADC12MEM2_IFG):
        case (ADC12IV_ADC12MEM3_IFG):
        case (ADC12IV_ADC12MEM4_IFG):
        case (ADC12IV_ADC12MEM5_IFG):
        case (ADC12IV_ADC12MEM6_IFG):
        case (ADC12IV_ADC12MEM7_IFG):
        case (ADC12IV_ADC12MEM8_IFG):
        case (ADC12IV_ADC12MEM9_IFG):
        case (ADC12IV_ADC12MEM10_IFG):
        case (ADC12IV_ADC12MEM11_IFG):
        case (ADC12IV_ADC12MEM12_IFG):
        case (ADC12IV_ADC12MEM13_IFG):
        case (ADC12IV_ADC12MEM14_IFG):
        case (ADC12IV_ADC12MEM15_IFG):
            if (NULL != adc_conv_callback)
            {
                // Call the ADC conversion complete callback function
                adc_conv_callback();
            }
            break;
        default:
            // Do nothing
            break;
    }
}


/******************************************************************************
	End of File: MSP430F5529LP_ADC.c
******************************************************************************/
