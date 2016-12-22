
/* ########################################################################## */
/*
 * This file was created for www.DavesMotleyProjects.com
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
 * Rev. 2.0, Modified code to increase core voltage by single steps as
 *           recommended by the TI family user's guide.
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

    static void Set_Core_Voltage(uint16_t level);


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
    /**************************************************************************
     *  IMPORTANT:
     * The Watchdog timer on the MSP430 is enabled by default after reset in
     * watchdog mode with an initial ~32 ms timeout. The user must halt or
     * reconfigure the watchdog before it expires or the processor will reset.
     * Since this CLOCK initialization must be called for every project that
     * uses the Operating Environment, disabling the watchdog is being placed
     * here. Note that if excessive memory initialization is performed by the
     * standard library start-up (which occurs before execution of the main()
     * function), then watchdog disable will have to be done as part of C
     * library start-up. This code will come too late to prevent continuous
     * re-booting in that case. The need to modify library startup is unusual,
     * except for very large projects. This should be sufficient.
     *
     **************************************************************************/
    WDTCTL = WDTPW + WDTHOLD;           // Stop the watchdog timer


    //##########################################################################
    /* Set VCORE for High Frequency operation
     * By default the MSP430 is configured for Low Power operation and the max
     * clock frequency is limited to less than 8 MHz. It is much more likely
     * for maker projects that a High Frequency clock, such as 24 MHz would be
     * desired. To support this the core voltage must be increased before
     * selecting a higher clock frequency, otherwise the results will be
     * unpredictable. Additionally, TI indicates that it is critical that the
     * core voltage only be increased one level at a time. These next commands
     * execute an algorithm to increase the core voltage and supply supervisors
     * and monitors to the required level, one step at a time.
     *
     **************************************************************************/
    Set_Core_Voltage(1);    // Max Freq. 12 MHz
    Set_Core_Voltage(2);    // Max Freq. 20 MHx
    Set_Core_Voltage(3);    // Max Freq. 25 MHz (now we're ready!)


    //##########################################################################
    /* Configure the Unified Clock System
     **************************************************************************/

    /***************************************************************************
     *  For debugging purposes, SMCLK can be output on Pin 2.2. If this is
     * desired, it is recommended to place the following in the application
     * code:
     *      P2DIR_bits.P2DIR2 = 1;
     *      P2SEL_bits.P2SEL2 = 1;
     * Modifying the library for this purpose is not recommended.
     **************************************************************************/

    // on the MSP430F5529LP the XT1 and XT2 inputs are shared with gpio and are
    // disabled at power-on until the port functions are selected. These pins
    // must be enabled to operate the 32.768 KHz crystal
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
    } while (1u == SFRIFG1_bits.OFIFG);     // Test oscillator fault flag

    UCSCTL6_bits.XT2DRIVEx = 3;		// Decrease XT2 Drive for 4MHz

    UCSCTL4_bits.SELAx = 0;          // ACLK source = XT1CLK (32.768KHz)
    UCSCTL4_bits.SELSx = 4;          // SMCLK source = DCOCLKDIV (24MHz)
    UCSCTL4_bits.SELMx = 4;          // MCLK source = DCOCLKDIV (24MHz)

    return;
}


/******************************************************************************
    Subroutine:     Set_Core_Voltage
    Description:    This function runs through the sequence for incrementing
                    the core voltage to the next level.
    Inputs:         uint16_t level - Defines the VCORE level to set next. It is
                    up to the user to make sure the the levels are sequential.
    Outputs:        None

******************************************************************************/
static void Set_Core_Voltage(uint16_t level)
{
    // NOTE: Writing the byte access password unlocks all PMM registers
    PMMCTL0_H = PMMPW_byte;            // unlock PMM registers

    /* Set the SVS high-side reset voltage level. If DVCC falls short of the
     * SVSH voltage level selected by SVSHRVL, a reset is triggered (if
     * SVSHPE = 1 (default)). The voltage levels are defined in the
     * device-specific data sheet.
     * Setting         Min     Typ     Max
     * SVSHRVL = 0     1.57    1.68    1.78 (default)
     * SVSHRVL = 1     1.79    1.88    1.98
     * SVSHRVL = 2     1.98    2.08    2.21
     * SVSHRVL = 3     2.10    2.18    2.31
     */
    SVSMHCTL_bits.SVSHRVLx = level;

    /* Set the SVS and SVM high-side reset release voltage level. These bits
     * define the reset release voltage level of the SVSH. It is also used for
     * the SVMH to define the voltage reached level. The voltage levels are
     * defined in the device-specific data sheet.
     * Setting         Min     Typ     Max
     * SVSMHRRL = 0    1.62    1.74    1.85 (default)
     * SVSMHRRL = 1    1.88    1.94    2.07
     * SVSMHRRL = 2    2.07    2.14    2.28
     * SVSMHRRL = 3    2.20    2.30    2.42
     * SVSMHRRL = 4    2.32    2.40    2.55
     * SVSMHRRL = 5    2.52    2.70    2.88
     * SVSMHRRL = 6    2.90    3.10    3.23
     * SVSMHRRL = 7    2.90    3.10    3.23
     */
    SVSMHCTL_bits.SVSMHRRLx = level;

    /* Set the SVS and SVM low-side reset release voltage level. These bits
     * define the reset release voltage level of the SVSL. It is also used
     * for the SVML to define the voltage reached level.
     * Setting         DVCC Setting
     * SVSMLRRL = 0    > 1.8V
     * SVSMLRRL = 1    > 2.0V
     * SVSMLRRL = 2    > 2.2V
     * SVSMLRRL = 3    > 2.4V
     */
    SVSMLCTL_bits.SVSMLRRLx = level;

    /* Wait until the SVM is settled. This bit is the SVS and SVM low-side
     * delay expired interrupt flag. This interrupt flag is set if the delay
     * element expired. The bit is cleared by software or by reading the
     * interrupt vector word.
     */
    while (0u == PMMIFG_bits.SVSMHDLYIFG);
    while (0u == PMMIFG_bits.SVSMLDLYIFG);

    // Clear any pre-existing interrupt flags
    PMMIFG_bits.SVMLVLRIFG = 0u;   // SVM low-side voltage level reached IFG
    PMMIFG_bits.SVMLIFG = 0u;      // SVM low-side IFG.

    // Set the new Core Voltage level
    PMMCTL0_bits.PMMCOREVx = level;

    /* If the core voltage is below the SVM level reached voltage, wait here
     * until VCORE reaches the new voltage level.
     */
    if (1u == PMMIFG_bits.SVMLIFG)
    {
        while (0u == PMMIFG_bits.SVMLVLRIFG);
    }

    /* Set the SVS low-side reset voltage level. If VCORE falls short of the
     * SVSL voltage level selected by SVSLRVL, a reset is triggered (if
     * SVSLPE = 1).
     */
    SVSMLCTL_bits.SVSLRVLx = level;

    /* Wait until the SVS is settled. This bit is the SVS and SVM low-side
     * delay expired interrupt flag. This interrupt flag is set if the delay
     * element expired. The bit is cleared by software or by reading the
     * interrupt vector word.
     */
    while (0u == PMMIFG_bits.SVSMLDLYIFG);

    // lock all of PMM registers
    PMMCTL0_H = !PMMPW_byte;

    return;
}


/******************************************************************************
	End of File: MSP430F5529LP_CLOCK.c
******************************************************************************/
