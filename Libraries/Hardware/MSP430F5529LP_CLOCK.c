
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
 * FileName:      MSP430F5529LP_CLOCK.c
 *
 * This file provides functions for the Unified Clock System (UCS) for the
 * Texas Instruments MSP430F5529 Launchpad development board.
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


/******************************************************************************
    PRIVATE DEFINITIONS (static const)
******************************************************************************/


/******************************************************************************
    PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/


/******************************************************************************
    PRIVATE VARIABLES (static)
******************************************************************************/


/******************************************************************************
    Subroutine:     MSP430F5529LP_CLOCK_Initialize
    Description:    Configures the core voltage and clock module to run the
                    MCLK and SMCLK sources at 24 MHz, and ACLK at 32.768 KHz.
    Inputs:         None
    Outputs:        None

******************************************************************************/
void MSP430F5529LP_CLOCK_Initialize(void)
{
    //##########################################################################
    /*-------------------------------------------------------------------------
    *   UCS  Unified System Clock - Defaults
    *-------------------------------------------------------------------------*/
    /*
    UCSCTL0_bits.DCOx = 0;
    UCSCTL0_bits.MODx = 0;
    UCSCTL1_bits.DCORSELx = 2;
    UCSCTL1_bits.DISMOD = 0;
    UCSCTL2_bits.FLLDx = 1;
    UCSCTL2_bits.FLLNx = 1;
    UCSCTL3_bits.FLLREFDIVx = 0;
    UCSCTL3_bits.SELREFx = 0;
    UCSCTL4_bits.SELAx = 0;
    UCSCTL4_bits.SELMx = 4;
    UCSCTL4_bits.SELSx = 4;
    UCSCTL5_bits.DIVAx = 0;
    UCSCTL5_bits.DIVMx = 0;
    UCSCTL5_bits.DIVPAx = 0;
    UCSCTL5_bits.DIVSx = 0;
    UCSCTL6_bits.XT2DRIVEx = 3;
    UCSCTL6_bits.XT2BYPASS = 0;
    UCSCTL6_bits.XT2OFF = 1;
    UCSCTL6_bits.XT1DRIVEx = 3;
    UCSCTL6_bits.XTS = 0;
    UCSCTL6_bits.XT1BYPASS = 0;
    UCSCTL6_bits.XCAPx = 3;
    UCSCTL6_bits.SMCLKOFF = 0;
    UCSCTL6_bits.XT1OFF = 1;
    UCSCTL7_bits.XT2OFFG = 0;
    UCSCTL7_bits.XT1HFOFFG = 0;
    UCSCTL7_bits.XT1LFOFFG = 1;
    UCSCTL7_bits.DCOFFG = 1;
    UCSCTL8_bits.MODOSCREQEN = 0;
    UCSCTL8_bits.SMCLKREQEN = 1;
    UCSCTL8_bits.MCLKREQEN = 1;
    UCSCTL8_bits.ACLKREQEN = 1;
    */
    //##########################################################################


    // Set VCORE for HF operation (word access only)
    PMMCTL0 = PMMPW + PMMCOREV_3;    // PMM Core Voltage 3 (1.85V)

    // For debugging purposes, the next two lines can be uncommented to output
    // SMCLK on Pin 2.2. Note: This pin is not used by the Grove system.
    P2DIR_bits.P2DIR2 = 1;
    P2SEL_bits.P2SEL2 = 1;

    // on the MSP430F5529LP the XT1 and XT2 inputs are shared with gpio and are
    // disabled at power-on until the port functions are selected.
    P5SEL_bits.P5SEL4 = 1;         // Enable XT1 Pin 5.4
    P5SEL_bits.P5SEL5 = 1;         // Enable XT1 Pin 5.5
    P5SEL_bits.P5SEL2 = 1;         // Enable XT2 Pin 5.2
    P5SEL_bits.P5SEL3 = 1;         // Enable XTs Pin 5.3

    UCSCTL6_bits.XCAPx = 3;        // XT1 cap = 12pF
    UCSCTL6_bits.XTS = 0;          // XT1 LF mode
    UCSCTL6_bits.XT1BYPASS = 0;    // XT1 source = internal
    UCSCTL6_bits.XT1OFF = 0;       // Enable XT1

    UCSCTL1_bits.DCORSELx = 7;     // Set DCO for HF operation
    UCSCTL6_bits.XT2OFF = 1;       // Enable XT2

    /*
    // Option 1: Use FLL with REFOCLK (32.768KHz) to get 23.986MHz
    UCSCTL3_bits.FLLREFDIVx = 0;   // Ref Divided by 1
    UCSCTL2_bits.FLLDx = 1;        // DCO Divided by 2
    UCSCTL3_bits.SELREFx = 2;      // FLL Reference = REFOCLK (32.768KHz)
    UCSCTL2_bits.FLLNx = 731;      // 23.986MHz
    // Average:   24.092MHz       +0.442%
    // Max:       24.885MHz       +3.75%
    // Min:       23.529MHz       -1.91%
    */

    // Option 2: Use FLL with XT2 (4MHz) to get 24.00MHz
    UCSCTL3_bits.FLLREFDIVx = 0;   // Ref Divided by 1
    UCSCTL2_bits.FLLDx = 1;        // DCO Divided by 2
    UCSCTL3_bits.SELREFx = 5;      // FLL Reference = XT2CLK (4.00MHz)
    UCSCTL2_bits.FLLNx = 5;        // 24.00MHz
    // Average:   24.004MHz       +0.0166%
    // Max:       24.856MHz       +3.54%
    // Min:       23.510MHz       -2.06%

    /*
    // Option 3: Use FLL with XT2 (4MHz) to get 24.00MHz with prescaler
    UCSCTL3_bits.FLLREFDIVx = 5;   // Ref Divided by 16
    UCSCTL2_bits.FLLDx = 1;        // DCO Divided by 2
    UCSCTL3_bits.SELREFx = 5;      // FLL Reference = XT2CLK (4.00MHz)
    UCSCTL2_bits.FLLNx = 95;       // 24.00MHz
    // Average:   23.997MHz       -0.013%
    // Max:       24.909MHz       +3.80%
    // Min:       23.500MHz       -2.07%
    */

    do // Loop until XT1, XT2 & DCO stabilizes
    {
        // Clear UCS individual oscillator fault flags
        UCSCTL7 &= ~(XT2OFFG + XT1HFOFFG + XT1LFOFFG + DCOFFG);
        SFRIFG1_bits.OFIFG = 0u;            // Clear Osc. fault flag
    }while (1u == SFRIFG1_bits.OFIFG);      // Test oscillator fault flag

    UCSCTL6_bits.XT2DRIVEx = 3;		// Decrease XT2 Drive for 4MHz

    UCSCTL4_bits.SELAx = 0;          // ACLK source = XT1CLK (32.768KHz)
    UCSCTL4_bits.SELSx = 4;          // SMCLK source = DCOCLKDIV (24MHz)
    UCSCTL4_bits.SELMx = 4;          // MCLK source = DCOCLKDIV (24MHz)

    return;
    }

/******************************************************************************
	End of File: MSP430F5529LP_CLOCK.c
******************************************************************************/
