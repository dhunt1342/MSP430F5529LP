
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
 * FileName:      MSP430F5529LP.h
 *
 * This file provides the standard register and bit definitions for the
 * Texas Instruments MSP430F5529 Launchpad development board.
 *
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
 *
 *                                                                            */
/* ===========================================================================*/

#ifndef __MSP430F5529LP__
#define __MSP430F5529LP__


#ifdef __cplusplus
    #define __READ    /* not supported */
#else
    #define __READ    const
#endif

#ifdef __cplusplus
    extern "C" {
#endif


#include <in430.h>
#include <iomacros.h>


#ifndef NULL
    #define NULL 0
#endif


/************************************************************
* DEFINE STANDARD TYPES
************************************************************/

// Define machine dependant types
typedef unsigned char         uint8_t;
typedef signed char           int8_t;
typedef unsigned short        uint16_t;
typedef signed short          int16_t;
typedef unsigned long         uint32_t;
typedef signed long           int32_t;


/************************************************************
* STANDARD BITS
************************************************************/

#define BIT0                (0x0001)
#define BIT1                (0x0002)
#define BIT2                (0x0004)
#define BIT3                (0x0008)
#define BIT4                (0x0010)
#define BIT5                (0x0020)
#define BIT6                (0x0040)
#define BIT7                (0x0080)
#define BIT8                (0x0100)
#define BIT9                (0x0200)
#define BITA                (0x0400)
#define BITB                (0x0800)
#define BITC                (0x1000)
#define BITD                (0x2000)
#define BITE                (0x4000)
#define BITF                (0x8000)


/************************************************************
* STATUS REGISTER BITS
************************************************************/

#define C                   (0x0001)
#define Z                   (0x0002)
#define N                   (0x0004)
#define V                   (0x0100)
#define GIE                 (0x0008)
#define CPUOFF              (0x0010)
#define OSCOFF              (0x0020)
#define SCG0                (0x0040)
#define SCG1                (0x0080)

/* Low Power Modes coded with Bits 4-7 in SR */

#define LPM0_bits           (CPUOFF)
#define LPM1_bits           (SCG0+CPUOFF)
#define LPM2_bits           (SCG1+CPUOFF)
#define LPM3_bits           (SCG1+SCG0+CPUOFF)
#define LPM4_bits           (SCG1+SCG0+OSCOFF+CPUOFF)


#define LPM0      __bis_SR_register(LPM0_bits)          /* Enter LPM0 */
#define LPM0_EXIT __bic_SR_register_on_exit(LPM0_bits)  /* Exit LPM0 */
#define LPM1      __bis_SR_register(LPM1_bits)          /* Enter LPM1 */
#define LPM1_EXIT __bic_SR_register_on_exit(LPM1_bits)  /* Exit LPM1 */
#define LPM2      __bis_SR_register(LPM2_bits)          /* Enter LPM2 */
#define LPM2_EXIT __bic_SR_register_on_exit(LPM2_bits)  /* Exit LPM2 */
#define LPM3      __bis_SR_register(LPM3_bits)          /* Enter LPM3 */
#define LPM3_EXIT __bic_SR_register_on_exit(LPM3_bits)  /* Exit LPM3 */
#define LPM4      __bis_SR_register(LPM4_bits)          /* Enter LPM4 */
#define LPM4_EXIT __bic_SR_register_on_exit(LPM4_bits)  /* Exit LPM4 */







/*#########################################################################
 *   ADC12
*##########################################################################*/


typedef volatile union
{
    uint16_t reg;             /* ADC12+ Control 0 */
    struct
    {
        uint16_t ADC12SC              : 1; /* ADC12 Start Conversion */
        uint16_t ADC12ENC             : 1; /* ADC12 Enable Conversion */
        uint16_t ADC12TOVIE           : 1; /* ADC12 Timer Overflow interrupt enable */
        uint16_t ADC12OVIE            : 1; /* ADC12 Overflow interrupt enable */
        uint16_t ADC12ON              : 1; /* ADC12 On/enable */
        uint16_t ADC12REFON           : 1; /* ADC12 Reference on */
        uint16_t ADC12REF2_5V         : 1; /*  */
        uint16_t ADC12MSC             : 1; /* ADC12 Multiple SampleConversion */
        uint16_t ADC12SHT0x           : 4; /* ADC12 Sample Hold 0 Select Bits */
        uint16_t ADC12SHT1x           : 4; /* ADC12 Sample Hold 1 Select Bits */
    } bits;
} ADC12CTL0_t;

#define p_ADC12CTL0                 ((ADC12CTL0_t        *) 0x0700u)
#define ADC12CTL0                   p_ADC12CTL0->reg
#define ADC12CTL0_bits              p_ADC12CTL0->bits


typedef volatile union
{
    uint16_t reg;           /* ADC12+ Control 1 */
    struct
    {
        uint16_t ADC12BUSY            : 1; /* ADC12 Busy */
        uint16_t ADC12CONSEQx         : 2; /* ADC12 Conversion Sequence Select Bits */
        uint16_t ADC12SSELx           : 2; /* ADC12 Clock Source Select Bits */
        uint16_t ADC12DIVx            : 3; /* ADC12 Clock Divider Select Bits */
        uint16_t ADC12ISSH            : 1; /* ADC12 Invert Sample Hold Signal */
        uint16_t ADC12SHP             : 1; /* ADC12 Sample/Hold Pulse Mode */
        uint16_t ADC12SHSx            : 2; /* ADC12 Sample/Hold Source Bits */
        uint16_t ADC12CSTARTADDx      : 4; /* ADC12 Conversion Start Address Bits */
    } bits;
} ADC12CTL1_t;

#define p_ADC12CTL1                 ((ADC12CTL1_t        *) 0x0702u)
#define ADC12CTL1                   p_ADC12CTL1->reg
#define ADC12CTL1_bits              p_ADC12CTL1->bits


typedef volatile union
{
    uint16_t reg;           /* ADC12+ Control 2 */
    struct
    {
        uint16_t ADC12REFBURST        : 1; /* ADC12+ Reference Burst */
        uint16_t ADC12REFOUT          : 1; /* ADC12+ Reference Out */
        uint16_t ADC12SR              : 1; /* ADC12+ Sampling Rate */
        uint16_t ADC12DF              : 1; /* ADC12+ Data Format */
        uint16_t ADC12RESx            : 2; /* ADC12+ Resolution Bits */
        uint16_t                      : 1;
        uint16_t ADC12TCOFF           : 1; /* ADC12+ Temperature Sensor Off */
        uint16_t ADC12PDIV            : 1; /* ADC12+ predivider 0:/1   1:/4 */
    } bits;
} ADC12CTL2_t;

#define p_ADC12CTL2                 ((ADC12CTL2_t        *) 0x0704u)
#define ADC12CTL2                   p_ADC12CTL2->reg
#define ADC12CTL2_bits              p_ADC12CTL2->bits


typedef volatile union
{
    uint16_t reg;           /* ADC12+ Interrupt Flag */
    struct
    {
        uint16_t ADC12IFG0            : 1; /* ADC12 Memory 0 Interrupt Flag */
        uint16_t ADC12IFG1            : 1; /* ADC12 Memory 1 Interrupt Flag */
        uint16_t ADC12IFG2            : 1; /* ADC12 Memory 2 Interrupt Flag */
        uint16_t ADC12IFG3            : 1; /* ADC12 Memory 3 Interrupt Flag */
        uint16_t ADC12IFG4            : 1; /* ADC12 Memory 4 Interrupt Flag */
        uint16_t ADC12IFG5            : 1; /* ADC12 Memory 5 Interrupt Flag */
        uint16_t ADC12IFG6            : 1; /* ADC12 Memory 6 Interrupt Flag */
        uint16_t ADC12IFG7            : 1; /* ADC12 Memory 7 Interrupt Flag */
        uint16_t ADC12IFG8            : 1; /* ADC12 Memory 8 Interrupt Flag */
        uint16_t ADC12IFG9            : 1; /* ADC12 Memory 9 Interrupt Flag */
        uint16_t ADC12IFG10           : 1; /* ADC12 Memory 10 Interrupt Flag */
        uint16_t ADC12IFG11           : 1; /* ADC12 Memory 11 Interrupt Flag */
        uint16_t ADC12IFG12           : 1; /* ADC12 Memory 12 Interrupt Flag */
        uint16_t ADC12IFG13           : 1; /* ADC12 Memory 13 Interrupt Flag */
        uint16_t ADC12IFG14           : 1; /* ADC12 Memory 14 Interrupt Flag */
        uint16_t ADC12IFG15           : 1; /* ADC12 Memory 15 Interrupt Flag */
    } bits;
} ADC12IFG_t;

#define p_ADC12IFG                  ((ADC12IFG_t        *) 0x070Au)
#define ADC12IFG                    p_ADC12IFG->reg
#define ADC12IFG_bits               p_ADC12IFG->bits


typedef volatile union
{
    uint16_t reg;         /* ADC12+ Interrupt Enable */
    struct
    {
        uint16_t ADC12IE0             : 1; /* ADC12 Memory 0 Interrupt Enable */
        uint16_t ADC12IE1             : 1; /* ADC12 Memory 1 Interrupt Enable */
        uint16_t ADC12IE2             : 1; /* ADC12 Memory 2 Interrupt Enable */
        uint16_t ADC12IE3             : 1; /* ADC12 Memory 3 Interrupt Enable */
        uint16_t ADC12IE4             : 1; /* ADC12 Memory 4 Interrupt Enable */
        uint16_t ADC12IE5             : 1; /* ADC12 Memory 5 Interrupt Enable */
        uint16_t ADC12IE6             : 1; /* ADC12 Memory 6 Interrupt Enable */
        uint16_t ADC12IE7             : 1; /* ADC12 Memory 7 Interrupt Enable */
        uint16_t ADC12IE8             : 1; /* ADC12 Memory 8 Interrupt Enable */
        uint16_t ADC12IE9             : 1; /* ADC12 Memory 9 Interrupt Enable */
        uint16_t ADC12IE10            : 1; /* ADC12 Memory 10 Interrupt Enable */
        uint16_t ADC12IE11            : 1; /* ADC12 Memory 11 Interrupt Enable */
        uint16_t ADC12IE12            : 1; /* ADC12 Memory 12 Interrupt Enable */
        uint16_t ADC12IE13            : 1; /* ADC12 Memory 13 Interrupt Enable */
        uint16_t ADC12IE14            : 1; /* ADC12 Memory 14 Interrupt Enable */
        uint16_t ADC12IE15            : 1; /* ADC12 Memory 15 Interrupt Enable */
    } bits;
} ADC12IE_t;

#define p_ADC12IE                   ((ADC12IE_t        *) 0x070Cu)
#define ADC12IE                     p_ADC12IE->reg
#define ADC12IE_bits                p_ADC12IE->bits


/* ADC12+ Interrupt Vector Word */
typedef volatile uint16_t ADC12IV_t;
#define p_ADC12IV               ((ADC12IV_t     *) 0x070Eu)
#define ADC12IV                 *p_ADC12IV


/* ADC12 Conversion Memory */
typedef volatile uint16_t ADC12MEMx_t;

#define p_ADC12MEM0               ((ADC12MEMx_t     *) 0x0720u)
#define ADC12MEM0                 *p_ADC12MEM0

#define p_ADC12MEM1               ((ADC12MEMx_t     *) 0x0722u)
#define ADC12MEM1                 *p_ADC12MEM1

#define p_ADC12MEM2               ((ADC12MEMx_t     *) 0x0724u)
#define ADC12MEM2                 *p_ADC12MEM2

#define p_ADC12MEM3               ((ADC12MEMx_t     *) 0x0726u)
#define ADC12MEM3                 *p_ADC12MEM3

#define p_ADC12MEM4               ((ADC12MEMx_t     *) 0x0728u)
#define ADC12MEM4                 *p_ADC12MEM4

#define p_ADC12MEM5               ((ADC12MEMx_t     *) 0x072Au)
#define ADC12MEM5                 *p_ADC12MEM5

#define p_ADC12MEM6               ((ADC12MEMx_t     *) 0x072Cu)
#define ADC12MEM6                 *p_ADC12MEM6

#define p_ADC12MEM7               ((ADC12MEMx_t     *) 0x072Eu)
#define ADC12MEM7                 *p_ADC12MEM7

#define p_ADC12MEM8               ((ADC12MEMx_t     *) 0x0730u)
#define ADC12MEM8                 *p_ADC12MEM8

#define p_ADC12MEM9               ((ADC12MEMx_t     *) 0x0732u)
#define ADC12MEM9                 *p_ADC12MEM9

#define p_ADC12MEM10              ((ADC12MEMx_t     *) 0x0734u)
#define ADC12MEM10                *p_ADC12MEM10

#define p_ADC12MEM11              ((ADC12MEMx_t     *) 0x0736u)
#define ADC12MEM11                *p_ADC12MEM11

#define p_ADC12MEM12              ((ADC12MEMx_t     *) 0x0738u)
#define ADC12MEM12                *p_ADC12MEM12

#define p_ADC12MEM13              ((ADC12MEMx_t     *) 0x073Au)
#define ADC12MEM13                *p_ADC12MEM13

#define p_ADC12MEM14              ((ADC12MEMx_t     *) 0x073Cu)
#define ADC12MEM14                *p_ADC12MEM14

#define p_ADC12MEM15              ((ADC12MEMx_t     *) 0x073Eu)
#define ADC12MEM15                *p_ADC12MEM15


typedef volatile union
{
    uint8_t reg;   /* ADC12 Memory Control x */
    struct
    {
        uint8_t ADC12INCHx            : 4; /* ADC12 Input Channel Select Bits */
        uint8_t ADC12SREFx            : 3; /* ADC12 Select Reference Bits */
        uint8_t ADC12EOS              : 1; /* ADC12 End of Sequence */
    }bits;
} ADC12MCTLx_t;

#define p_ADC12MCTL0                ((ADC12MCTLx_t        *) 0x0710u)
#define ADC12MCTL0                  p_ADC12MCTL0->reg
#define ADC12MCTL0_bits             p_ADC12MCTL0->bits

#define p_ADC12MCTL1                ((ADC12MCTLx_t        *) 0x0711u)
#define ADC12MCTL1                  p_ADC12MCTL1->reg
#define ADC12MCTL1_bits             p_ADC12MCTL1->bits

#define p_ADC12MCTL2                ((ADC12MCTLx_t        *) 0x0712u)
#define ADC12MCTL2                  p_ADC12MCTL2->reg
#define ADC12MCTL2_bits             p_ADC12MCTL2->bits

#define p_ADC12MCTL3                ((ADC12MCTLx_t        *) 0x0713u)
#define ADC12MCTL3                  p_ADC12MCTL3->reg
#define ADC12MCTL3_bits             p_ADC12MCTL3->bits

#define p_ADC12MCTL4                ((ADC12MCTLx_t        *) 0x0714u)
#define ADC12MCTL4                  p_ADC12MCTL4->reg
#define ADC12MCTL4_bits             p_ADC12MCTL4->bits

#define p_ADC12MCTL5                ((ADC12MCTLx_t        *) 0x0715u)
#define ADC12MCTL5                  p_ADC12MCTL5->reg
#define ADC12MCTL5_bits             p_ADC12MCTL5->bits

#define p_ADC12MCTL6                ((ADC12MCTLx_t        *) 0x0716u)
#define ADC12MCTL6                  p_ADC12MCTL6->reg
#define ADC12MCTL6_bits             p_ADC12MCTL6->bits

#define p_ADC12MCTL7                ((ADC12MCTLx_t        *) 0x0717u)
#define ADC12MCTL7                  p_ADC12MCTL7->reg
#define ADC12MCTL7_bits             p_ADC12MCTL7->bits

#define p_ADC12MCTL8                ((ADC12MCTLx_t        *) 0x0718u)
#define ADC12MCTL8                  p_ADC12MCTL8->reg
#define ADC12MCTL8_bits             p_ADC12MCTL8->bits

#define p_ADC12MCTL9                ((ADC12MCTLx_t        *) 0x0719u)
#define ADC12MCTL9                  p_ADC12MCTL9->reg
#define ADC12MCTL9_bits             p_ADC12MCTL9->bits

#define p_ADC12MCTL10               ((ADC12MCTLx_t        *) 0x071Au)
#define ADC12MCTL10                 p_ADC12MCTL10->reg
#define ADC12MCTL10_bits            p_ADC12MCTL10->bits

#define p_ADC12MCTL11               ((ADC12MCTLx_t        *) 0x071Bu)
#define ADC12MCTL11                 p_ADC12MCTL11->reg
#define ADC12MCTL11_bits            p_ADC12MCTL11->bits

#define p_ADC12MCTL12               ((ADC12MCTLx_t        *) 0x071Cu)
#define ADC12MCTL12                 p_ADC12MCTL12->reg
#define ADC12MCTL12_bits            p_ADC12MCTL12->bits

#define p_ADC12MCTL13               ((ADC12MCTLx_t        *) 0x071Du)
#define ADC12MCTL13                 p_ADC12MCTL13->reg
#define ADC12MCTL13_bits            p_ADC12MCTL13->bits

#define p_ADC12MCTL14               ((ADC12MCTLx_t        *) 0x071Eu)
#define ADC12MCTL14                 p_ADC12MCTL14->reg
#define ADC12MCTL14_bits            p_ADC12MCTL14->bits

#define p_ADC12MCTL15               ((ADC12MCTLx_t        *) 0x071Fu)
#define ADC12MCTL15                 p_ADC12MCTL15->reg
#define ADC12MCTL15_bits            p_ADC12MCTL15->bits


/*   ADC12 Interrupt Vector Sources   */
#define ADC12IV_NONE                0x00u
#define ADC12IV_ADC12MEMx_OVFL      0x02u
#define ADC12IV_ADC12CONV_OVFL      0x04u
#define ADC12IV_ADC12MEM0_IFG       0x06u
#define ADC12IV_ADC12MEM1_IFG       0x08u
#define ADC12IV_ADC12MEM2_IFG       0x0Au
#define ADC12IV_ADC12MEM3_IFG       0x0Cu
#define ADC12IV_ADC12MEM4_IFG       0x0Eu
#define ADC12IV_ADC12MEM5_IFG       0x10u
#define ADC12IV_ADC12MEM6_IFG       0x12u
#define ADC12IV_ADC12MEM7_IFG       0x14u
#define ADC12IV_ADC12MEM8_IFG       0x16u
#define ADC12IV_ADC12MEM9_IFG       0x18u
#define ADC12IV_ADC12MEM10_IFG      0x1Au
#define ADC12IV_ADC12MEM11_IFG      0x1Cu
#define ADC12IV_ADC12MEM12_IFG      0x1Eu
#define ADC12IV_ADC12MEM13_IFG      0x20u
#define ADC12IV_ADC12MEM14_IFG      0x22u
#define ADC12IV_ADC12MEM15_IFG      0x24u





/*#########################################################################
 *   Comparator B
*##########################################################################*/

    // Not supported yet



/*#########################################################################
 *   CRC16
*##########################################################################*/

    // Not supported yet



/*#########################################################################
 *   DMA
*##########################################################################*/

// Not supported yet



/*#########################################################################
 *   Flash
*##########################################################################*/

// Not supported yet



/*#########################################################################
 *   MPY 16  Multiplier  16 Bit Mode
*##########################################################################*/

// Not supported yet



/*#########################################################################
 *   MPY 32  Multiplier  32 Bit Mode
*##########################################################################*/

// Not supported yet



/*#############################################################################
 *   Port A (16-bit access), Ports 1 & 2 (8-bit access)
*############################################################################*/


/*%%%%% INPUT %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 1 Input */
    struct
    {
        unsigned __READ char P1IN0           : 1; /*  */
        unsigned __READ char P1IN1           : 1; /*  */
        unsigned __READ char P1IN2           : 1; /*  */
        unsigned __READ char P1IN3           : 1; /*  */
        unsigned __READ char P1IN4           : 1; /*  */
        unsigned __READ char P1IN5           : 1; /*  */
        unsigned __READ char P1IN6           : 1; /*  */
        unsigned __READ char P1IN7           : 1; /*  */
    } bits;
} P1IN_t;

#define p_P1IN                  ((P1IN_t        *) 0x0200u)
#define P1IN                    p_P1IN->reg
#define P1IN_bits               p_P1IN->bits


typedef volatile union
{
    uint8_t reg;            /* Port 2 Input */
    struct
    {
        unsigned __READ char P2IN0           : 1; /*  */
        unsigned __READ char P2IN1           : 1; /*  */
        unsigned __READ char P2IN2           : 1; /*  */
        unsigned __READ char P2IN3           : 1; /*  */
        unsigned __READ char P2IN4           : 1; /*  */
        unsigned __READ char P2IN5           : 1; /*  */
        unsigned __READ char P2IN6           : 1; /*  */
        unsigned __READ char P2IN7           : 1; /*  */
    } bits;
} P2IN_t;

#define p_P2IN                  ((P2IN_t        *) 0x0201u)
#define P2IN                    p_P2IN->reg
#define P2IN_bits               p_P2IN->bits


typedef volatile union
{
    uint16_t reg;        /* Port A Input */
    struct
    {
        unsigned __READ short PAIN0           : 1; /*  */
        unsigned __READ short PAIN1           : 1; /*  */
        unsigned __READ short PAIN2           : 1; /*  */
        unsigned __READ short PAIN3           : 1; /*  */
        unsigned __READ short PAIN4           : 1; /*  */
        unsigned __READ short PAIN5           : 1; /*  */
        unsigned __READ short PAIN6           : 1; /*  */
        unsigned __READ short PAIN7           : 1; /*  */
        unsigned __READ short PAIN8           : 1; /*  */
        unsigned __READ short PAIN9           : 1; /*  */
        unsigned __READ short PAIN10          : 1; /*  */
        unsigned __READ short PAIN11          : 1; /*  */
        unsigned __READ short PAIN12          : 1; /*  */
        unsigned __READ short PAIN13          : 1; /*  */
        unsigned __READ short PAIN14          : 1; /*  */
        unsigned __READ short PAIN15          : 1; /*  */
    } bits;
} PAIN_t;

#define p_PAIN                  ((PAIN_t        *) 0x0200u)
#define PAIN                    p_PAIN->reg
#define PAIN_bits               p_PAIN->bits


/*%%%%% OUTPUT %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 1 Output */
    struct
    {
        uint8_t P1OUT0           : 1; /*  */
        uint8_t P1OUT1           : 1; /*  */
        uint8_t P1OUT2           : 1; /*  */
        uint8_t P1OUT3           : 1; /*  */
        uint8_t P1OUT4           : 1; /*  */
        uint8_t P1OUT5           : 1; /*  */
        uint8_t P1OUT6           : 1; /*  */
        uint8_t P1OUT7           : 1; /*  */
    } bits;
} P1OUT_t;

#define p_P1OUT                 ((P1OUT_t       *) 0x0202u)
#define P1OUT                   p_P1OUT->reg
#define P1OUT_bits              p_P1OUT->bits


typedef volatile union
{
    uint8_t reg;            /* Port 2 Output */
    struct
    {
        uint8_t P2OUT0           : 1; /*  */
        uint8_t P2OUT1           : 1; /*  */
        uint8_t P2OUT2           : 1; /*  */
        uint8_t P2OUT3           : 1; /*  */
        uint8_t P2OUT4           : 1; /*  */
        uint8_t P2OUT5           : 1; /*  */
        uint8_t P2OUT6           : 1; /*  */
        uint8_t P2OUT7           : 1; /*  */
    } bits;
} P2OUT_t;

#define p_P2OUT                 ((P2OUT_t       *) 0x0203u)
#define P2OUT                   p_P2OUT->reg
#define P2OUT_bits              p_P2OUT->bits


typedef volatile union
{
    uint16_t reg;        /* Port A Output */
    struct
    {
        uint16_t PAOUT0           : 1; /*  */
        uint16_t PAOUT1           : 1; /*  */
        uint16_t PAOUT2           : 1; /*  */
        uint16_t PAOUT3           : 1; /*  */
        uint16_t PAOUT4           : 1; /*  */
        uint16_t PAOUT5           : 1; /*  */
        uint16_t PAOUT6           : 1; /*  */
        uint16_t PAOUT7           : 1; /*  */
        uint16_t PAOUT8           : 1; /*  */
        uint16_t PAOUT9           : 1; /*  */
        uint16_t PAOUT10          : 1; /*  */
        uint16_t PAOUT11          : 1; /*  */
        uint16_t PAOUT12          : 1; /*  */
        uint16_t PAOUT13          : 1; /*  */
        uint16_t PAOUT14          : 1; /*  */
        uint16_t PAOUT15          : 1; /*  */
    } bits;
} PAOUT_t;

#define p_PAOUT                 ((PAOUT_t       *) 0x0202u)
#define PAOUT                   p_PAOUT->reg
#define PAOUT_bits              p_PAOUT->bits


/*%%%%% DIRECTION %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 1 Direction */
    struct
    {
        uint8_t P1DIR0          : 1; /*  */
        uint8_t P1DIR1          : 1; /*  */
        uint8_t P1DIR2          : 1; /*  */
        uint8_t P1DIR3          : 1; /*  */
        uint8_t P1DIR4          : 1; /*  */
        uint8_t P1DIR5          : 1; /*  */
        uint8_t P1DIR6          : 1; /*  */
        uint8_t P1DIR7          : 1; /*  */
    } bits;
} P1DIR_t;

#define p_P1DIR                 ((P1DIR_t       *) 0x0204u)
#define P1DIR                   p_P1DIR->reg
#define P1DIR_bits              p_P1DIR->bits


typedef volatile union
{
    uint8_t reg;            /* Port 2 Direction */
    struct
    {
        uint8_t P2DIR0          : 1; /*  */
        uint8_t P2DIR1          : 1; /*  */
        uint8_t P2DIR2          : 1; /*  */
        uint8_t P2DIR3          : 1; /*  */
        uint8_t P2DIR4          : 1; /*  */
        uint8_t P2DIR5          : 1; /*  */
        uint8_t P2DIR6          : 1; /*  */
        uint8_t P2DIR7          : 1; /*  */
    } bits;
} P2DIR_t;

#define p_P2DIR                 ((P2DIR_t       *) 0x0205u)
#define P2DIR                   p_P2DIR->reg
#define P2DIR_bits              p_P2DIR->bits


typedef volatile union
{
    uint16_t reg;        /* Port A Direction */
    struct
    {
        uint16_t PADIR0          : 1; /*  */
        uint16_t PADIR1          : 1; /*  */
        uint16_t PADIR2          : 1; /*  */
        uint16_t PADIR3          : 1; /*  */
        uint16_t PADIR4          : 1; /*  */
        uint16_t PADIR5          : 1; /*  */
        uint16_t PADIR6          : 1; /*  */
        uint16_t PADIR7          : 1; /*  */
        uint16_t PADIR8          : 1; /*  */
        uint16_t PADIR9          : 1; /*  */
        uint16_t PADIR10         : 1; /*  */
        uint16_t PADIR11         : 1; /*  */
        uint16_t PADIR12         : 1; /*  */
        uint16_t PADIR13         : 1; /*  */
        uint16_t PADIR14         : 1; /*  */
        uint16_t PADIR15         : 1; /*  */
    } bits;
} PADIR_t;

#define p_PADIR                 ((PADIR_t       *) 0x0204u)
#define PADIR                   p_PADIR->reg
#define PADIR_bits              p_PADIR->bits


/*%%%%% RESISTOR ENABLE %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 1 Resistor Enable */
    struct
    {
        uint8_t P1REN0          : 1; /*  */
        uint8_t P1REN1          : 1; /*  */
        uint8_t P1REN2          : 1; /*  */
        uint8_t P1REN3          : 1; /*  */
        uint8_t P1REN4          : 1; /*  */
        uint8_t P1REN5          : 1; /*  */
        uint8_t P1REN6          : 1; /*  */
        uint8_t P1REN7          : 1; /*  */
    } bits;
} P1REN_t;

#define p_P1REN                 ((P1REN_t       *) 0x0206u)
#define P1REN                   p_P1REN->reg
#define P1REN_bits              p_P1REN->bits


typedef volatile union
{
    uint8_t reg;            /* Port 2 Resistor Enable */
    struct
    {
        uint8_t P2REN0          : 1; /*  */
        uint8_t P2REN1          : 1; /*  */
        uint8_t P2REN2          : 1; /*  */
        uint8_t P2REN3          : 1; /*  */
        uint8_t P2REN4          : 1; /*  */
        uint8_t P2REN5          : 1; /*  */
        uint8_t P2REN6          : 1; /*  */
        uint8_t P2REN7          : 1; /*  */
    } bits;
} P2REN_t;

#define p_P2REN                 ((P2REN_t       *) 0x0207u)
#define P2REN                   p_P2REN->reg
#define P2REN_bits              p_P2REN->bits


typedef volatile union
{
    uint16_t reg;        /* Port A Resistor Enable */
    struct
    {
        uint16_t PAREN0          : 1; /*  */
        uint16_t PAREN1          : 1; /*  */
        uint16_t PAREN2          : 1; /*  */
        uint16_t PAREN3          : 1; /*  */
        uint16_t PAREN4          : 1; /*  */
        uint16_t PAREN5          : 1; /*  */
        uint16_t PAREN6          : 1; /*  */
        uint16_t PAREN7          : 1; /*  */
        uint16_t PAREN8          : 1; /*  */
        uint16_t PAREN9          : 1; /*  */
        uint16_t PAREN10         : 1; /*  */
        uint16_t PAREN11         : 1; /*  */
        uint16_t PAREN12         : 1; /*  */
        uint16_t PAREN13         : 1; /*  */
        uint16_t PAREN14         : 1; /*  */
        uint16_t PAREN15         : 1; /*  */
    } bits;
} PAREN_t;

#define p_PAREN                 ((PAREN_t       *) 0x0206u)
#define PAREN                   p_PAREN->reg
#define PAREN_bits              p_PAREN->bits


/*%%%%% DRIVE STRENGTH %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 1 Drive Strength */
    struct
    {
        uint8_t P1DS0          : 1; /*  */
        uint8_t P1DS1          : 1; /*  */
        uint8_t P1DS2          : 1; /*  */
        uint8_t P1DS3          : 1; /*  */
        uint8_t P1DS4          : 1; /*  */
        uint8_t P1DS5          : 1; /*  */
        uint8_t P1DS6          : 1; /*  */
        uint8_t P1DS7          : 1; /*  */
    } bits;
} P1DS_t;

#define p_P1DS                  ((P1DS_t        *) 0x0208u)
#define P1DS                    p_P1DS->reg
#define P1DS_bits               p_P1DS->bits


typedef volatile union
{
    uint8_t reg;            /* Port 2 Drive Strength */
    struct
    {
        uint8_t P2DS0          : 1; /*  */
        uint8_t P2DS1          : 1; /*  */
        uint8_t P2DS2          : 1; /*  */
        uint8_t P2DS3          : 1; /*  */
        uint8_t P2DS4          : 1; /*  */
        uint8_t P2DS5          : 1; /*  */
        uint8_t P2DS6          : 1; /*  */
        uint8_t P2DS7          : 1; /*  */
    } bits;
} P2DS_t;

#define p_P2DS                  ((P2DS_t        *) 0x0209u)
#define P2DS                    p_P2DS->reg
#define P2DS_bits               p_P2DS->bits


typedef volatile union
{
    uint16_t reg;        /* Port A Drive Strength */
    struct
    {
        uint16_t PADS0          : 1; /*  */
        uint16_t PADS1          : 1; /*  */
        uint16_t PADS2          : 1; /*  */
        uint16_t PADS3          : 1; /*  */
        uint16_t PADS4          : 1; /*  */
        uint16_t PADS5          : 1; /*  */
        uint16_t PADS6          : 1; /*  */
        uint16_t PADS7          : 1; /*  */
        uint16_t PADS8          : 1; /*  */
        uint16_t PADS9          : 1; /*  */
        uint16_t PADS10         : 1; /*  */
        uint16_t PADS11         : 1; /*  */
        uint16_t PADS12         : 1; /*  */
        uint16_t PADS13         : 1; /*  */
        uint16_t PADS14         : 1; /*  */
        uint16_t PADS15         : 1; /*  */
    } bits;
} PADS_t;

#define p_PADS                  ((PADS_t        *) 0x0208u)
#define PADS                    p_PADS->reg
#define PADS_bits               p_PADS->bits


/*%%%%% SELECT %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 1 Select */
    struct
    {
        uint8_t P1SEL0          : 1; /*  */
        uint8_t P1SEL1          : 1; /*  */
        uint8_t P1SEL2          : 1; /*  */
        uint8_t P1SEL3          : 1; /*  */
        uint8_t P1SEL4          : 1; /*  */
        uint8_t P1SEL5          : 1; /*  */
        uint8_t P1SEL6          : 1; /*  */
        uint8_t P1SEL7          : 1; /*  */
    } bits;
} P1SEL_t;

#define p_P1SEL                 ((P1SEL_t       *) 0x020Au)
#define P1SEL                   p_P1SEL->reg
#define P1SEL_bits              p_P1SEL->bits


typedef volatile union
{
    uint8_t reg;            /* Port 2 Select */
    struct
    {
        uint8_t P2SEL0          : 1; /*  */
        uint8_t P2SEL1          : 1; /*  */
        uint8_t P2SEL2          : 1; /*  */
        uint8_t P2SEL3          : 1; /*  */
        uint8_t P2SEL4          : 1; /*  */
        uint8_t P2SEL5          : 1; /*  */
        uint8_t P2SEL6          : 1; /*  */
        uint8_t P2SEL7          : 1; /*  */
    } bits;
} P2SEL_t;

#define p_P2SEL                 ((P2SEL_t       *) 0x020Bu)
#define P2SEL                   p_P2SEL->reg
#define P2SEL_bits              p_P2SEL->bits


typedef volatile union
{
    uint16_t reg;        /* Port A Select */
    struct
    {
        uint16_t PASEL0          : 1; /*  */
        uint16_t PASEL1          : 1; /*  */
        uint16_t PASEL2          : 1; /*  */
        uint16_t PASEL3          : 1; /*  */
        uint16_t PASEL4          : 1; /*  */
        uint16_t PASEL5          : 1; /*  */
        uint16_t PASEL6          : 1; /*  */
        uint16_t PASEL7          : 1; /*  */
        uint16_t PASEL8          : 1; /*  */
        uint16_t PASEL9          : 1; /*  */
        uint16_t PASEL10         : 1; /*  */
        uint16_t PASEL11         : 1; /*  */
        uint16_t PASEL12         : 1; /*  */
        uint16_t PASEL13         : 1; /*  */
        uint16_t PASEL14         : 1; /*  */
        uint16_t PASEL15         : 1; /*  */
    } bits;
} PASEL_t;

#define p_PASEL                 ((PASEL_t       *) 0x020Au)
#define PASEL                   p_PASEL->reg
#define PASEL_bits              p_PASEL->bits


/*%%%%% INTERRUPT VECTOR %%%%%*/

typedef volatile uint16_t P1IV_t;
#define p_P1IV                  ((P1IV_t       *) 0x020Eu)
#define P1IV                    * p_P1IV

typedef volatile uint16_t P2IV_t;
#define p_P2IV                  ((P2IV_t       *) 0x021Eu)
#define P2IV                    * p_P2IV


/*%%%%% INTERRUPT EDGE SELECT %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 1 Interrupt Edge Select */
    struct
    {
        uint8_t P1IES0          : 1; /*  */
        uint8_t P1IES1          : 1; /*  */
        uint8_t P1IES2          : 1; /*  */
        uint8_t P1IES3          : 1; /*  */
        uint8_t P1IES4          : 1; /*  */
        uint8_t P1IES5          : 1; /*  */
        uint8_t P1IES6          : 1; /*  */
        uint8_t P1IES7          : 1; /*  */
    } bits;
} P1IES_t;

#define p_P1IES                 ((P1IES_t       *) 0x0218u)
#define P1IES                   p_P1IES->reg
#define P1IES_bits              p_P1IES->bits


typedef volatile union
{
    uint8_t reg;            /* Port 2 Interrupt Edge Select */
    struct
    {
        uint8_t P2IES0          : 1; /*  */
        uint8_t P2IES1          : 1; /*  */
        uint8_t P2IES2          : 1; /*  */
        uint8_t P2IES3          : 1; /*  */
        uint8_t P2IES4          : 1; /*  */
        uint8_t P2IES5          : 1; /*  */
        uint8_t P2IES6          : 1; /*  */
        uint8_t P2IES7          : 1; /*  */
    } bits;
} P2IES_t;

#define p_P2IES                 ((P2IES_t       *) 0x0219u)
#define P2IES                   p_P2IES->reg
#define P2IES_bits              p_P2IES->bits


typedef volatile union
{
    uint16_t reg;        /* Port A Interrupt Edge Select */
    struct
    {
        uint16_t PAIES0          : 1; /*  */
        uint16_t PAIES1          : 1; /*  */
        uint16_t PAIES2          : 1; /*  */
        uint16_t PAIES3          : 1; /*  */
        uint16_t PAIES4          : 1; /*  */
        uint16_t PAIES5          : 1; /*  */
        uint16_t PAIES6          : 1; /*  */
        uint16_t PAIES7          : 1; /*  */
        uint16_t PAIES8          : 1; /*  */
        uint16_t PAIES9          : 1; /*  */
        uint16_t PAIES10         : 1; /*  */
        uint16_t PAIES11         : 1; /*  */
        uint16_t PAIES12         : 1; /*  */
        uint16_t PAIES13         : 1; /*  */
        uint16_t PAIES14         : 1; /*  */
        uint16_t PAIES15         : 1; /*  */
    } bits;
} PAIES_t;

#define p_PAIES                 ((PAIES_t       *) 0x0218u)
#define PAIES                   p_PAIES->reg
#define PAIES_bits              p_PAIES->bits


/*%%%%% INTERRUPT ENABLE %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 1 Interrupt Enable */
    struct
    {
        uint8_t P1IE0          : 1; /*  */
        uint8_t P1IE1          : 1; /*  */
        uint8_t P1IE2          : 1; /*  */
        uint8_t P1IE3          : 1; /*  */
        uint8_t P1IE4          : 1; /*  */
        uint8_t P1IE5          : 1; /*  */
        uint8_t P1IE6          : 1; /*  */
        uint8_t P1IE7          : 1; /*  */
    } bits;
} P1IE_t;

#define p_P1IE                  ((P1IE_t        *) 0x021Au)
#define P1IE                    p_P1IE->reg
#define P1IE_bits               p_P1IE->bits


typedef volatile union
{
    uint8_t reg;            /* Port 2 Interrupt Enable */
    struct
    {
        uint8_t P2IE0          : 1; /*  */
        uint8_t P2IE1          : 1; /*  */
        uint8_t P2IE2          : 1; /*  */
        uint8_t P2IE3          : 1; /*  */
        uint8_t P2IE4          : 1; /*  */
        uint8_t P2IE5          : 1; /*  */
        uint8_t P2IE6          : 1; /*  */
        uint8_t P2IE7          : 1; /*  */
    } bits;
} P2IE_t;

#define p_P2IE                  ((P2IE_t        *) 0x021Bu)
#define P2IE                    p_P2IE->reg
#define P2IE_bits               p_P2IE->bits


typedef volatile union
{
    uint16_t reg;        /* Port A Interrupt Enable */
    struct
    {
        uint16_t PAIE0          : 1; /*  */
        uint16_t PAIE1          : 1; /*  */
        uint16_t PAIE2          : 1; /*  */
        uint16_t PAIE3          : 1; /*  */
        uint16_t PAIE4          : 1; /*  */
        uint16_t PAIE5          : 1; /*  */
        uint16_t PAIE6          : 1; /*  */
        uint16_t PAIE7          : 1; /*  */
        uint16_t PAIE8          : 1; /*  */
        uint16_t PAIE9          : 1; /*  */
        uint16_t PAIE10         : 1; /*  */
        uint16_t PAIE11         : 1; /*  */
        uint16_t PAIE12         : 1; /*  */
        uint16_t PAIE13         : 1; /*  */
        uint16_t PAIE14         : 1; /*  */
        uint16_t PAIE15         : 1; /*  */
    } bits;
} PAIE_t;

#define p_PAIE                  ((PAIE_t        *) 0x021Au)
#define PAIE                    p_PAIE->reg
#define PAIE_bits               p_PAIE->bits


/*%%%%% INTERRUPT FLAG %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 1 Interrupt Flag */
    struct
    {
        uint8_t P1IFG0          : 1; /*  */
        uint8_t P1IFG1          : 1; /*  */
        uint8_t P1IFG2          : 1; /*  */
        uint8_t P1IFG3          : 1; /*  */
        uint8_t P1IFG4          : 1; /*  */
        uint8_t P1IFG5          : 1; /*  */
        uint8_t P1IFG6          : 1; /*  */
        uint8_t P1IFG7          : 1; /*  */
    } bits;
} P1IFG_t;

#define p_P1IFG                 ((P1IFG_t       *) 0x021Cu)
#define P1IFG                   p_P1IFG->reg
#define P1IFG_bits              p_P1IFG->bits


typedef volatile union
{
    uint8_t reg;            /* Port 2 Interrupt Flag */
    struct
    {
        uint8_t P2IFG0          : 1; /*  */
        uint8_t P2IFG1          : 1; /*  */
        uint8_t P2IFG2          : 1; /*  */
        uint8_t P2IFG3          : 1; /*  */
        uint8_t P2IFG4          : 1; /*  */
        uint8_t P2IFG5          : 1; /*  */
        uint8_t P2IFG6          : 1; /*  */
        uint8_t P2IFG7          : 1; /*  */
    } bits;
} P2IFG_t;

#define p_P2IFG                 ((P2IFG_t       *) 0x021Du)
#define P2IFG                   p_P2IFG->reg
#define P2IFG_bits              p_P2IFG->bits


typedef volatile union
{
    uint16_t reg;        /* Port A Interrupt Flag */
    struct
    {
        uint16_t PAIFG0          : 1; /*  */
        uint16_t PAIFG1          : 1; /*  */
        uint16_t PAIFG2          : 1; /*  */
        uint16_t PAIFG3          : 1; /*  */
        uint16_t PAIFG4          : 1; /*  */
        uint16_t PAIFG5          : 1; /*  */
        uint16_t PAIFG6          : 1; /*  */
        uint16_t PAIFG7          : 1; /*  */
        uint16_t PAIFG8          : 1; /*  */
        uint16_t PAIFG9          : 1; /*  */
        uint16_t PAIFG10         : 1; /*  */
        uint16_t PAIFG11         : 1; /*  */
        uint16_t PAIFG12         : 1; /*  */
        uint16_t PAIFG13         : 1; /*  */
        uint16_t PAIFG14         : 1; /*  */
        uint16_t PAIFG15         : 1; /*  */
    } bits;
} PAIFG_t;

#define p_PAIFG                 ((PAIFG_t       *) 0x021Cu)
#define PAIFG                   p_PAIFG->reg
#define PAIFG_bits              p_PAIFG->bits







/*#############################################################################
 *   Port B (16-bit access), Ports 3 & 4 (8-bit access)
*############################################################################*/


/*%%%%% INPUT %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 3 Input */
    struct
    {
        unsigned __READ char P3IN0           : 1; /*  */
        unsigned __READ char P3IN1           : 1; /*  */
        unsigned __READ char P3IN2           : 1; /*  */
        unsigned __READ char P3IN3           : 1; /*  */
        unsigned __READ char P3IN4           : 1; /*  */
        unsigned __READ char P3IN5           : 1; /*  */
        unsigned __READ char P3IN6           : 1; /*  */
        unsigned __READ char P3IN7           : 1; /*  */
    } bits;
} P3IN_t;

#define p_P3IN            ((P3IN_t        *) 0x0220u)
#define P3IN            p_P3IN->reg
#define P3IN_bits        p_P3IN->bits


typedef volatile union
{
    uint8_t reg;            /* Port 4 Input */
    struct
    {
        unsigned __READ char P4IN0           : 1; /*  */
        unsigned __READ char P4IN1           : 1; /*  */
        unsigned __READ char P4IN2           : 1; /*  */
        unsigned __READ char P4IN3           : 1; /*  */
        unsigned __READ char P4IN4           : 1; /*  */
        unsigned __READ char P4IN5           : 1; /*  */
        unsigned __READ char P4IN6           : 1; /*  */
        unsigned __READ char P4IN7           : 1; /*  */
    } bits;
} P4IN_t;

#define p_P4IN            ((P4IN_t        *) 0x0221u)
#define P4IN            p_P4IN->reg
#define P4IN_bits        p_P4IN->bits


typedef volatile union
{
    uint16_t reg;        /* Port B Input */
    struct
    {
        unsigned __READ short PBIN0           : 1; /*  */
        unsigned __READ short PBIN1           : 1; /*  */
        unsigned __READ short PBIN2           : 1; /*  */
        unsigned __READ short PBIN3           : 1; /*  */
        unsigned __READ short PBIN4           : 1; /*  */
        unsigned __READ short PBIN5           : 1; /*  */
        unsigned __READ short PBIN6           : 1; /*  */
        unsigned __READ short PBIN7           : 1; /*  */
        unsigned __READ short PBIN8           : 1; /*  */
        unsigned __READ short PBIN9           : 1; /*  */
        unsigned __READ short PBIN10          : 1; /*  */
        unsigned __READ short PBIN11          : 1; /*  */
        unsigned __READ short PBIN12          : 1; /*  */
        unsigned __READ short PBIN13          : 1; /*  */
        unsigned __READ short PBIN14          : 1; /*  */
        unsigned __READ short PBIN15          : 1; /*  */
    } bits;
} PBIN_t;

#define p_PBIN            ((PBIN_t        *) 0x0220u)
#define PBIN            p_PBIN->reg
#define PBIN_bits        p_PBIN->bits


/*%%%%% OUTPUT %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 3 Output */
    struct
    {
        uint8_t P3OUT0           : 1; /*  */
        uint8_t P3OUT1           : 1; /*  */
        uint8_t P3OUT2           : 1; /*  */
        uint8_t P3OUT3           : 1; /*  */
        uint8_t P3OUT4           : 1; /*  */
        uint8_t P3OUT5           : 1; /*  */
        uint8_t P3OUT6           : 1; /*  */
        uint8_t P3OUT7           : 1; /*  */
    } bits;
} P3OUT_t;

#define p_P3OUT            ((P3OUT_t        *) 0x0222u)
#define P3OUT            p_P3OUT->reg
#define P3OUT_bits        p_P3OUT->bits


typedef volatile union
{
    uint8_t reg;            /* Port 4 Output */
    struct
    {
        uint8_t P4OUT0           : 1; /*  */
        uint8_t P4OUT1           : 1; /*  */
        uint8_t P4OUT2           : 1; /*  */
        uint8_t P4OUT3           : 1; /*  */
        uint8_t P4OUT4           : 1; /*  */
        uint8_t P4OUT5           : 1; /*  */
        uint8_t P4OUT6           : 1; /*  */
        uint8_t P4OUT7           : 1; /*  */
    } bits;
} P4OUT_t;

#define p_P4OUT            ((P4OUT_t        *) 0x0223u)
#define P4OUT            p_P4OUT->reg
#define P4OUT_bits        p_P4OUT->bits


typedef volatile union
{
    uint16_t reg;        /* Port B Output */
    struct
    {
        uint16_t PBOUT0           : 1; /*  */
        uint16_t PBOUT1           : 1; /*  */
        uint16_t PBOUT2           : 1; /*  */
        uint16_t PBOUT3           : 1; /*  */
        uint16_t PBOUT4           : 1; /*  */
        uint16_t PBOUT5           : 1; /*  */
        uint16_t PBOUT6           : 1; /*  */
        uint16_t PBOUT7           : 1; /*  */
        uint16_t PBOUT8           : 1; /*  */
        uint16_t PBOUT9           : 1; /*  */
        uint16_t PBOUT10          : 1; /*  */
        uint16_t PBOUT11          : 1; /*  */
        uint16_t PBOUT12          : 1; /*  */
        uint16_t PBOUT13          : 1; /*  */
        uint16_t PBOUT14          : 1; /*  */
        uint16_t PBOUT15          : 1; /*  */
    } bits;
} PBOUT_t;

#define p_PBOUT            ((PBOUT_t        *) 0x0222u)
#define PBOUT            p_PBOUT->reg
#define PBOUT_bits        p_PBOUT->bits


/*%%%%% DIRECTION %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 3 Direction */
    struct
    {
        uint8_t P3DIR0          : 1; /*  */
        uint8_t P3DIR1          : 1; /*  */
        uint8_t P3DIR2          : 1; /*  */
        uint8_t P3DIR3          : 1; /*  */
        uint8_t P3DIR4          : 1; /*  */
        uint8_t P3DIR5          : 1; /*  */
        uint8_t P3DIR6          : 1; /*  */
        uint8_t P3DIR7          : 1; /*  */
    } bits;
} P3DIR_t;

#define p_P3DIR            ((P3DIR_t        *) 0x0224u)
#define P3DIR            p_P3DIR->reg
#define P3DIR_bits        p_P3DIR->bits


typedef volatile union
{
    uint8_t reg;            /* Port 4 Direction */
    struct
    {
        uint8_t P4DIR0          : 1; /*  */
        uint8_t P4DIR1          : 1; /*  */
        uint8_t P4DIR2          : 1; /*  */
        uint8_t P4DIR3          : 1; /*  */
        uint8_t P4DIR4          : 1; /*  */
        uint8_t P4DIR5          : 1; /*  */
        uint8_t P4DIR6          : 1; /*  */
        uint8_t P4DIR7          : 1; /*  */
    } bits;
} P4DIR_t;

#define p_P4DIR            ((P4DIR_t        *) 0x0225u)
#define P4DIR            p_P4DIR->reg
#define P4DIR_bits        p_P4DIR->bits


typedef volatile union
{
    uint16_t reg;        /* Port B Direction */
    struct
    {
        uint16_t PBDIR0          : 1; /*  */
        uint16_t PBDIR1          : 1; /*  */
        uint16_t PBDIR2          : 1; /*  */
        uint16_t PBDIR3          : 1; /*  */
        uint16_t PBDIR4          : 1; /*  */
        uint16_t PBDIR5          : 1; /*  */
        uint16_t PBDIR6          : 1; /*  */
        uint16_t PBDIR7          : 1; /*  */
        uint16_t PBDIR8          : 1; /*  */
        uint16_t PBDIR9          : 1; /*  */
        uint16_t PBDIR10         : 1; /*  */
        uint16_t PBDIR11         : 1; /*  */
        uint16_t PBDIR12         : 1; /*  */
        uint16_t PBDIR13         : 1; /*  */
        uint16_t PBDIR14         : 1; /*  */
        uint16_t PBDIR15         : 1; /*  */
    } bits;
} PBDIR_t;

#define p_PBDIR            ((PBDIR_t        *) 0x0224u)
#define PBDIR            p_PBDIR->reg
#define PBDIR_bits        p_PBDIR->bits


/*%%%%% RESISTOR ENABLE %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 3 Resistor Enable */
    struct
    {
        uint8_t P3REN0          : 1; /*  */
        uint8_t P3REN1          : 1; /*  */
        uint8_t P3REN2          : 1; /*  */
        uint8_t P3REN3          : 1; /*  */
        uint8_t P3REN4          : 1; /*  */
        uint8_t P3REN5          : 1; /*  */
        uint8_t P3REN6          : 1; /*  */
        uint8_t P3REN7          : 1; /*  */
    } bits;
} P3REN_t;

#define p_P3REN            ((P3REN_t        *) 0x0226u)
#define P3REN            p_P3REN->reg
#define P3REN_bits        p_P3REN->bits


typedef volatile union
{
    uint8_t reg;            /* Port 4 Resistor Enable */
    struct
    {
        uint8_t P4REN0          : 1; /*  */
        uint8_t P4REN1          : 1; /*  */
        uint8_t P4REN2          : 1; /*  */
        uint8_t P4REN3          : 1; /*  */
        uint8_t P4REN4          : 1; /*  */
        uint8_t P4REN5          : 1; /*  */
        uint8_t P4REN6          : 1; /*  */
        uint8_t P4REN7          : 1; /*  */
    } bits;
} P4REN_t;

#define p_P4REN            ((P4REN_t        *) 0x0227u)
#define P4REN            p_P4REN->reg
#define P4REN_bits        p_P4REN->bits


typedef volatile union
{
    uint16_t reg;        /* Port B Resistor Enable */
    struct
    {
        uint16_t PBREN0          : 1; /*  */
        uint16_t PBREN1          : 1; /*  */
        uint16_t PBREN2          : 1; /*  */
        uint16_t PBREN3          : 1; /*  */
        uint16_t PBREN4          : 1; /*  */
        uint16_t PBREN5          : 1; /*  */
        uint16_t PBREN6          : 1; /*  */
        uint16_t PBREN7          : 1; /*  */
        uint16_t PBREN8          : 1; /*  */
        uint16_t PBREN9          : 1; /*  */
        uint16_t PBREN10         : 1; /*  */
        uint16_t PBREN11         : 1; /*  */
        uint16_t PBREN12         : 1; /*  */
        uint16_t PBREN13         : 1; /*  */
        uint16_t PBREN14         : 1; /*  */
        uint16_t PBREN15         : 1; /*  */
    } bits;
} PBREN_t;

#define p_PBREN            ((PBREN_t        *) 0x0226u)
#define PBREN            p_PBREN->reg
#define PBREN_bits        p_PBREN->bits


/*%%%%% DRIVE STRENGTH %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 3 Drive Strength */
    struct
    {
        uint8_t P3DS0          : 1; /*  */
        uint8_t P3DS1          : 1; /*  */
        uint8_t P3DS2          : 1; /*  */
        uint8_t P3DS3          : 1; /*  */
        uint8_t P3DS4          : 1; /*  */
        uint8_t P3DS5          : 1; /*  */
        uint8_t P3DS6          : 1; /*  */
        uint8_t P3DS7          : 1; /*  */
    } bits;
} P3DS_t;

#define p_P3DS            ((P3DS_t        *) 0x0228u)
#define P3DS            p_P3DS->reg
#define P3DS_bits        p_P3DS->bits


typedef volatile union
{
    uint8_t reg;            /* Port 4 Drive Strength */
    struct
    {
        uint8_t P4DS0          : 1; /*  */
        uint8_t P4DS1          : 1; /*  */
        uint8_t P4DS2          : 1; /*  */
        uint8_t P4DS3          : 1; /*  */
        uint8_t P4DS4          : 1; /*  */
        uint8_t P4DS5          : 1; /*  */
        uint8_t P4DS6          : 1; /*  */
        uint8_t P4DS7          : 1; /*  */
    } bits;
} P4DS_t;

#define p_P4DS            ((P4DS_t        *) 0x0229u)
#define P4DS            p_P4DS->reg
#define P4DS_bits        p_P4DS->bits


typedef volatile union
{
    uint16_t reg;        /* Port B Drive Strength */
    struct
    {
        uint16_t PBDS0          : 1; /*  */
        uint16_t PBDS1          : 1; /*  */
        uint16_t PBDS2          : 1; /*  */
        uint16_t PBDS3          : 1; /*  */
        uint16_t PBDS4          : 1; /*  */
        uint16_t PBDS5          : 1; /*  */
        uint16_t PBDS6          : 1; /*  */
        uint16_t PBDS7          : 1; /*  */
        uint16_t PBDS8          : 1; /*  */
        uint16_t PBDS9          : 1; /*  */
        uint16_t PBDS10         : 1; /*  */
        uint16_t PBDS11         : 1; /*  */
        uint16_t PBDS12         : 1; /*  */
        uint16_t PBDS13         : 1; /*  */
        uint16_t PBDS14         : 1; /*  */
        uint16_t PBDS15         : 1; /*  */
    } bits;
} PBDS_t;

#define p_PBDS            ((PBDS_t        *) 0x0228u)
#define PBDS            p_PBDS->reg
#define PBDS_bits        p_PBDS->bits


/*%%%%% SELECT %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 3 Select */
    struct
    {
        uint8_t P3SEL0          : 1; /*  */
        uint8_t P3SEL1          : 1; /*  */
        uint8_t P3SEL2          : 1; /*  */
        uint8_t P3SEL3          : 1; /*  */
        uint8_t P3SEL4          : 1; /*  */
        uint8_t P3SEL5          : 1; /*  */
        uint8_t P3SEL6          : 1; /*  */
        uint8_t P3SEL7          : 1; /*  */
    } bits;
} P3SEL_t;

#define p_P3SEL            ((P3SEL_t        *) 0x022Au)
#define P3SEL            p_P3SEL->reg
#define P3SEL_bits        p_P3SEL->bits


typedef volatile union
{
    uint8_t reg;            /* Port 4 Select */
    struct
    {
        uint8_t P4SEL0          : 1; /*  */
        uint8_t P4SEL1          : 1; /*  */
        uint8_t P4SEL2          : 1; /*  */
        uint8_t P4SEL3          : 1; /*  */
        uint8_t P4SEL4          : 1; /*  */
        uint8_t P4SEL5          : 1; /*  */
        uint8_t P4SEL6          : 1; /*  */
        uint8_t P4SEL7          : 1; /*  */
    } bits;
} P4SEL_t;

#define p_P4SEL            ((P4SEL_t        *) 0x022Bu)
#define P4SEL            p_P4SEL->reg
#define P4SEL_bits        p_P4SEL->bits


typedef volatile union
{
    uint16_t reg;        /* Port B Select */
    struct
    {
        uint16_t PBSEL0          : 1; /*  */
        uint16_t PBSEL1          : 1; /*  */
        uint16_t PBSEL2          : 1; /*  */
        uint16_t PBSEL3          : 1; /*  */
        uint16_t PBSEL4          : 1; /*  */
        uint16_t PBSEL5          : 1; /*  */
        uint16_t PBSEL6          : 1; /*  */
        uint16_t PBSEL7          : 1; /*  */
        uint16_t PBSEL8          : 1; /*  */
        uint16_t PBSEL9          : 1; /*  */
        uint16_t PBSEL10         : 1; /*  */
        uint16_t PBSEL11         : 1; /*  */
        uint16_t PBSEL12         : 1; /*  */
        uint16_t PBSEL13         : 1; /*  */
        uint16_t PBSEL14         : 1; /*  */
        uint16_t PBSEL15         : 1; /*  */
    } bits;
} PBSEL_t;

#define p_PBSEL            ((PBSEL_t        *) 0x022Au)
#define PBSEL            p_PBSEL->reg
#define PBSEL_bits        p_PBSEL->bits







/*#############################################################################
 *   Port C (16-bit access), Ports 5 & 6 (8-bit access)
*############################################################################*/


/*%%%%% INPUT %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 5 Input */
    struct
    {
        unsigned __READ char P5IN0           : 1; /*  */
        unsigned __READ char P5IN1           : 1; /*  */
        unsigned __READ char P5IN2           : 1; /*  */
        unsigned __READ char P5IN3           : 1; /*  */
        unsigned __READ char P5IN4           : 1; /*  */
        unsigned __READ char P5IN5           : 1; /*  */
        unsigned __READ char P5IN6           : 1; /*  */
        unsigned __READ char P5IN7           : 1; /*  */
    } bits;
} P5IN_t;

#define p_P5IN            ((P5IN_t        *) 0x0240u)
#define P5IN            p_P5IN->reg
#define P5IN_bits        p_P5IN->bits


typedef volatile union
{
    uint8_t reg;            /* Port 6 Input */
    struct
    {
        unsigned __READ char P6IN0           : 1; /*  */
        unsigned __READ char P6IN1           : 1; /*  */
        unsigned __READ char P6IN2           : 1; /*  */
        unsigned __READ char P6IN3           : 1; /*  */
        unsigned __READ char P6IN4           : 1; /*  */
        unsigned __READ char P6IN5           : 1; /*  */
        unsigned __READ char P6IN6           : 1; /*  */
        unsigned __READ char P6IN7           : 1; /*  */
    } bits;
} P6IN_t;

#define p_P6IN            ((P6IN_t        *) 0x0241u)
#define P6IN            p_P6IN->reg
#define P6IN_bits        p_P6IN->bits


typedef volatile union
{
    uint16_t reg;        /* Port C Input */
    struct
    {
        unsigned __READ short PCIN0           : 1; /*  */
        unsigned __READ short PCIN1           : 1; /*  */
        unsigned __READ short PCIN2           : 1; /*  */
        unsigned __READ short PCIN3           : 1; /*  */
        unsigned __READ short PCIN4           : 1; /*  */
        unsigned __READ short PCIN5           : 1; /*  */
        unsigned __READ short PCIN6           : 1; /*  */
        unsigned __READ short PCIN7           : 1; /*  */
        unsigned __READ short PCIN8           : 1; /*  */
        unsigned __READ short PCIN9           : 1; /*  */
        unsigned __READ short PCIN10          : 1; /*  */
        unsigned __READ short PCIN11          : 1; /*  */
        unsigned __READ short PCIN12          : 1; /*  */
        unsigned __READ short PCIN13          : 1; /*  */
        unsigned __READ short PCIN14          : 1; /*  */
        unsigned __READ short PCIN15          : 1; /*  */
    } bits;
} PCIN_t;

#define p_PCIN            ((PCIN_t        *) 0x0240u)
#define PCIN            p_PCIN->reg
#define PCIN_bits        p_PCIN->bits


/*%%%%% OUTPUT %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 5 Output */
    struct
    {
        uint8_t P5OUT0           : 1; /*  */
        uint8_t P5OUT1           : 1; /*  */
        uint8_t P5OUT2           : 1; /*  */
        uint8_t P5OUT3           : 1; /*  */
        uint8_t P5OUT4           : 1; /*  */
        uint8_t P5OUT5           : 1; /*  */
        uint8_t P5OUT6           : 1; /*  */
        uint8_t P5OUT7           : 1; /*  */
    } bits;
} P5OUT_t;

#define p_P5OUT            ((P5OUT_t        *) 0x0242u)
#define P5OUT            p_P5OUT->reg
#define P5OUT_bits        p_P5OUT->bits


typedef volatile union
{
    uint8_t reg;            /* Port 6 Output */
    struct
    {
        uint8_t P6OUT0           : 1; /*  */
        uint8_t P6OUT1           : 1; /*  */
        uint8_t P6OUT2           : 1; /*  */
        uint8_t P6OUT3           : 1; /*  */
        uint8_t P6OUT4           : 1; /*  */
        uint8_t P6OUT5           : 1; /*  */
        uint8_t P6OUT6           : 1; /*  */
        uint8_t P6OUT7           : 1; /*  */
    } bits;
} P6OUT_t;

#define p_P6OUT            ((P6OUT_t        *) 0x0243u)
#define P6OUT            p_P6OUT->reg
#define P6OUT_bits        p_P6OUT->bits


typedef volatile union
{
    uint16_t reg;        /* Port C Output */
    struct
    {
        uint16_t PCOUT0           : 1; /*  */
        uint16_t PCOUT1           : 1; /*  */
        uint16_t PCOUT2           : 1; /*  */
        uint16_t PCOUT3           : 1; /*  */
        uint16_t PCOUT4           : 1; /*  */
        uint16_t PCOUT5           : 1; /*  */
        uint16_t PCOUT6           : 1; /*  */
        uint16_t PCOUT7           : 1; /*  */
        uint16_t PCOUT8           : 1; /*  */
        uint16_t PCOUT9           : 1; /*  */
        uint16_t PCOUT10          : 1; /*  */
        uint16_t PCOUT11          : 1; /*  */
        uint16_t PCOUT12          : 1; /*  */
        uint16_t PCOUT13          : 1; /*  */
        uint16_t PCOUT14          : 1; /*  */
        uint16_t PCOUT15          : 1; /*  */
    } bits;
} PCOUT_t;

#define p_PCOUT            ((PCOUT_t        *) 0x0242u)
#define PCOUT            p_PCOUT->reg
#define PCOUT_bits        p_PCOUT->bits


/*%%%%% DIRECTION %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 5 Direction */
    struct
    {
        uint8_t P5DIR0          : 1; /*  */
        uint8_t P5DIR1          : 1; /*  */
        uint8_t P5DIR2          : 1; /*  */
        uint8_t P5DIR3          : 1; /*  */
        uint8_t P5DIR4          : 1; /*  */
        uint8_t P5DIR5          : 1; /*  */
        uint8_t P5DIR6          : 1; /*  */
        uint8_t P5DIR7          : 1; /*  */
    } bits;
} P5DIR_t;

#define p_P5DIR            ((P5DIR_t        *) 0x0244u)
#define P5DIR            p_P5DIR->reg
#define P5DIR_bits        p_P5DIR->bits


typedef volatile union
{
    uint8_t reg;            /* Port 6 Direction */
    struct
    {
        uint8_t P6DIR0          : 1; /*  */
        uint8_t P6DIR1          : 1; /*  */
        uint8_t P6DIR2          : 1; /*  */
        uint8_t P6DIR3          : 1; /*  */
        uint8_t P6DIR4          : 1; /*  */
        uint8_t P6DIR5          : 1; /*  */
        uint8_t P6DIR6          : 1; /*  */
        uint8_t P6DIR7          : 1; /*  */
    } bits;
} P6DIR_t;

#define p_P6DIR            ((P6DIR_t        *) 0x0245u)
#define P6DIR            p_P6DIR->reg
#define P6DIR_bits        p_P6DIR->bits


typedef volatile union
{
    uint16_t reg;        /* Port C Direction */
    struct
    {
        uint16_t PCDIR0          : 1; /*  */
        uint16_t PCDIR1          : 1; /*  */
        uint16_t PCDIR2          : 1; /*  */
        uint16_t PCDIR3          : 1; /*  */
        uint16_t PCDIR4          : 1; /*  */
        uint16_t PCDIR5          : 1; /*  */
        uint16_t PCDIR6          : 1; /*  */
        uint16_t PCDIR7          : 1; /*  */
        uint16_t PCDIR8          : 1; /*  */
        uint16_t PCDIR9          : 1; /*  */
        uint16_t PCDIR10         : 1; /*  */
        uint16_t PCDIR11         : 1; /*  */
        uint16_t PCDIR12         : 1; /*  */
        uint16_t PCDIR13         : 1; /*  */
        uint16_t PCDIR14         : 1; /*  */
        uint16_t PCDIR15         : 1; /*  */
    } bits;
} PCDIR_t;

#define p_PCDIR            ((PCDIR_t        *) 0x0244u)
#define PCDIR            p_PCDIR->reg
#define PCDIR_bits        p_PCDIR->bits


/*%%%%% RESISTOR ENABLE %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 5 Resistor Enable */
    struct
    {
        uint8_t P5REN0          : 1; /*  */
        uint8_t P5REN1          : 1; /*  */
        uint8_t P5REN2          : 1; /*  */
        uint8_t P5REN3          : 1; /*  */
        uint8_t P5REN4          : 1; /*  */
        uint8_t P5REN5          : 1; /*  */
        uint8_t P5REN6          : 1; /*  */
        uint8_t P5REN7          : 1; /*  */
    } bits;
} P5REN_t;

#define p_P5REN            ((P5REN_t        *) 0x0246u)
#define P5REN            p_P5REN->reg
#define P5REN_bits        p_P5REN->bits


typedef volatile union
{
    uint8_t reg;            /* Port 6 Resistor Enable */
    struct
    {
        uint8_t P6REN0          : 1; /*  */
        uint8_t P6REN1          : 1; /*  */
        uint8_t P6REN2          : 1; /*  */
        uint8_t P6REN3          : 1; /*  */
        uint8_t P6REN4          : 1; /*  */
        uint8_t P6REN5          : 1; /*  */
        uint8_t P6REN6          : 1; /*  */
        uint8_t P6REN7          : 1; /*  */
    } bits;
} P6REN_t;

#define p_P6REN            ((P6REN_t        *) 0x0247u)
#define P6REN            p_P6REN->reg
#define P6REN_bits        p_P6REN->bits


typedef volatile union
{
    uint16_t reg;        /* Port C Resistor Enable */
    struct
    {
        uint16_t PCREN0          : 1; /*  */
        uint16_t PCREN1          : 1; /*  */
        uint16_t PCREN2          : 1; /*  */
        uint16_t PCREN3          : 1; /*  */
        uint16_t PCREN4          : 1; /*  */
        uint16_t PCREN5          : 1; /*  */
        uint16_t PCREN6          : 1; /*  */
        uint16_t PCREN7          : 1; /*  */
        uint16_t PCREN8          : 1; /*  */
        uint16_t PCREN9          : 1; /*  */
        uint16_t PCREN10         : 1; /*  */
        uint16_t PCREN11         : 1; /*  */
        uint16_t PCREN12         : 1; /*  */
        uint16_t PCREN13         : 1; /*  */
        uint16_t PCREN14         : 1; /*  */
        uint16_t PCREN15         : 1; /*  */
    } bits;
} PCREN_t;

#define p_PCREN            ((PCREN_t        *) 0x0246u)
#define PCREN            p_PCREN->reg
#define PCREN_bits        p_PCREN->bits


/*%%%%% DRIVE STRENGTH %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 5 Drive Strength */
    struct
    {
        uint8_t P5DS0          : 1; /*  */
        uint8_t P5DS1          : 1; /*  */
        uint8_t P5DS2          : 1; /*  */
        uint8_t P5DS3          : 1; /*  */
        uint8_t P5DS4          : 1; /*  */
        uint8_t P5DS5          : 1; /*  */
        uint8_t P5DS6          : 1; /*  */
        uint8_t P5DS7          : 1; /*  */
    } bits;
} P5DS_t;

#define p_P5DS            ((P5DS_t        *) 0x0248u)
#define P5DS            p_P5DS->reg
#define P5DS_bits        p_P5DS->bits


typedef volatile union
{
    uint8_t reg;            /* Port 6 Drive Strength */
    struct
    {
        uint8_t P6DS0          : 1; /*  */
        uint8_t P6DS1          : 1; /*  */
        uint8_t P6DS2          : 1; /*  */
        uint8_t P6DS3          : 1; /*  */
        uint8_t P6DS4          : 1; /*  */
        uint8_t P6DS5          : 1; /*  */
        uint8_t P6DS6          : 1; /*  */
        uint8_t P6DS7          : 1; /*  */
    } bits;
} P6DS_t;

#define p_P6DS            ((P6DS_t        *) 0x0249u)
#define P6DS            p_P6DS->reg
#define P6DS_bits        p_P6DS->bits


typedef volatile union
{
    uint16_t reg;        /* Port C Drive Strength */
    struct
    {
        uint16_t PCDS0          : 1; /*  */
        uint16_t PCDS1          : 1; /*  */
        uint16_t PCDS2          : 1; /*  */
        uint16_t PCDS3          : 1; /*  */
        uint16_t PCDS4          : 1; /*  */
        uint16_t PCDS5          : 1; /*  */
        uint16_t PCDS6          : 1; /*  */
        uint16_t PCDS7          : 1; /*  */
        uint16_t PCDS8          : 1; /*  */
        uint16_t PCDS9          : 1; /*  */
        uint16_t PCDS10         : 1; /*  */
        uint16_t PCDS11         : 1; /*  */
        uint16_t PCDS12         : 1; /*  */
        uint16_t PCDS13         : 1; /*  */
        uint16_t PCDS14         : 1; /*  */
        uint16_t PCDS15         : 1; /*  */
    } bits;
} PCDS_t;

#define p_PCDS            ((PCDS_t        *) 0x0248u)
#define PCDS            p_PCDS->reg
#define PCDS_bits        p_PCDS->bits


/*%%%%% SELECT %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 5 Select */
    struct
    {
        uint8_t P5SEL0          : 1; /*  */
        uint8_t P5SEL1          : 1; /*  */
        uint8_t P5SEL2          : 1; /*  */
        uint8_t P5SEL3          : 1; /*  */
        uint8_t P5SEL4          : 1; /*  */
        uint8_t P5SEL5          : 1; /*  */
        uint8_t P5SEL6          : 1; /*  */
        uint8_t P5SEL7          : 1; /*  */
    } bits;
} P5SEL_t;

#define p_P5SEL            ((P5SEL_t        *) 0x024Au)
#define P5SEL            p_P5SEL->reg
#define P5SEL_bits        p_P5SEL->bits


typedef volatile union
{
    uint8_t reg;            /* Port 6 Select */
    struct
    {
        uint8_t P6SEL0          : 1; /*  */
        uint8_t P6SEL1          : 1; /*  */
        uint8_t P6SEL2          : 1; /*  */
        uint8_t P6SEL3          : 1; /*  */
        uint8_t P6SEL4          : 1; /*  */
        uint8_t P6SEL5          : 1; /*  */
        uint8_t P6SEL6          : 1; /*  */
        uint8_t P6SEL7          : 1; /*  */
    } bits;
} P6SEL_t;

#define p_P6SEL            ((P6SEL_t        *) 0x024Bu)
#define P6SEL            p_P6SEL->reg
#define P6SEL_bits        p_P6SEL->bits


typedef volatile union
{
    uint16_t reg;        /* Port C Select */
    struct
    {
        uint16_t PCSEL0          : 1; /*  */
        uint16_t PCSEL1          : 1; /*  */
        uint16_t PCSEL2          : 1; /*  */
        uint16_t PCSEL3          : 1; /*  */
        uint16_t PCSEL4          : 1; /*  */
        uint16_t PCSEL5          : 1; /*  */
        uint16_t PCSEL6          : 1; /*  */
        uint16_t PCSEL7          : 1; /*  */
        uint16_t PCSEL8          : 1; /*  */
        uint16_t PCSEL9          : 1; /*  */
        uint16_t PCSEL10         : 1; /*  */
        uint16_t PCSEL11         : 1; /*  */
        uint16_t PCSEL12         : 1; /*  */
        uint16_t PCSEL13         : 1; /*  */
        uint16_t PCSEL14         : 1; /*  */
        uint16_t PCSEL15         : 1; /*  */
    } bits;
} PCSEL_t;

#define p_PCSEL            ((PCSEL_t        *) 0x024Au)
#define PCSEL            p_PCSEL->reg
#define PCSEL_bits        p_PCSEL->bits







/*#############################################################################
 *   Port D (16-bit access), Ports 7 & 8 (8-bit access)
*############################################################################*/


/*%%%%% INPUT %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 7 Input */
    struct
    {
        unsigned __READ char P7IN0           : 1; /*  */
        unsigned __READ char P7IN1           : 1; /*  */
        unsigned __READ char P7IN2           : 1; /*  */
        unsigned __READ char P7IN3           : 1; /*  */
        unsigned __READ char P7IN4           : 1; /*  */
        unsigned __READ char P7IN5           : 1; /*  */
        unsigned __READ char P7IN6           : 1; /*  */
        unsigned __READ char P7IN7           : 1; /*  */
    } bits;
} P7IN_t;

#define p_P7IN            ((P7IN_t        *) 0x0260u)
#define P7IN            p_P7IN->reg
#define P7IN_bits        p_P7IN->bits


typedef volatile union
{
    uint8_t reg;            /* Port 8 Input */
    struct
    {
        unsigned __READ char P8IN0           : 1; /*  */
        unsigned __READ char P8IN1           : 1; /*  */
        unsigned __READ char P8IN2           : 1; /*  */
        unsigned __READ char P8IN3           : 1; /*  */
        unsigned __READ char P8IN4           : 1; /*  */
        unsigned __READ char P8IN5           : 1; /*  */
        unsigned __READ char P8IN6           : 1; /*  */
        unsigned __READ char P8IN7           : 1; /*  */
    } bits;
} P8IN_t;

#define p_P8IN            ((P8IN_t        *) 0x0261u)
#define P8IN            p_P8IN->reg
#define P8IN_bits        p_P8IN->bits


typedef volatile union
{
    uint16_t reg;        /* Port D Input */
    struct
    {
        unsigned __READ short PDIN0           : 1; /*  */
        unsigned __READ short PDIN1           : 1; /*  */
        unsigned __READ short PDIN2           : 1; /*  */
        unsigned __READ short PDIN3           : 1; /*  */
        unsigned __READ short PDIN4           : 1; /*  */
        unsigned __READ short PDIN5           : 1; /*  */
        unsigned __READ short PDIN6           : 1; /*  */
        unsigned __READ short PDIN7           : 1; /*  */
        unsigned __READ short PDIN8           : 1; /*  */
        unsigned __READ short PDIN9           : 1; /*  */
        unsigned __READ short PDIN10          : 1; /*  */
        unsigned __READ short PDIN11          : 1; /*  */
        unsigned __READ short PDIN12          : 1; /*  */
        unsigned __READ short PDIN13          : 1; /*  */
        unsigned __READ short PDIN14          : 1; /*  */
        unsigned __READ short PDIN15          : 1; /*  */
    } bits;
} PDIN_t;

#define p_PDIN            ((PDIN_t        *) 0x0260u)
#define PDIN            p_PDIN->reg
#define PDIN_bits        p_PDIN->bits


/*%%%%% OUTPUT %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 7 Output */
    struct
    {
        uint8_t P7OUT0           : 1; /*  */
        uint8_t P7OUT1           : 1; /*  */
        uint8_t P7OUT2           : 1; /*  */
        uint8_t P7OUT3           : 1; /*  */
        uint8_t P7OUT4           : 1; /*  */
        uint8_t P7OUT5           : 1; /*  */
        uint8_t P7OUT6           : 1; /*  */
        uint8_t P7OUT7           : 1; /*  */
    } bits;
} P7OUT_t;

#define p_P7OUT            ((P7OUT_t        *) 0x0262u)
#define P7OUT            p_P7OUT->reg
#define P7OUT_bits        p_P7OUT->bits


typedef volatile union
{
    uint8_t reg;            /* Port 8 Output */
    struct
    {
        uint8_t P8OUT0           : 1; /*  */
        uint8_t P8OUT1           : 1; /*  */
        uint8_t P8OUT2           : 1; /*  */
        uint8_t P8OUT3           : 1; /*  */
        uint8_t P8OUT4           : 1; /*  */
        uint8_t P8OUT5           : 1; /*  */
        uint8_t P8OUT6           : 1; /*  */
        uint8_t P8OUT7           : 1; /*  */
    } bits;
} P8OUT_t;

#define p_P8OUT            ((P8OUT_t        *) 0x0263u)
#define P8OUT            p_P8OUT->reg
#define P8OUT_bits        p_P8OUT->bits


typedef volatile union
{
    uint16_t reg;        /* Port D Output */
    struct
    {
        uint16_t PDOUT0           : 1; /*  */
        uint16_t PDOUT1           : 1; /*  */
        uint16_t PDOUT2           : 1; /*  */
        uint16_t PDOUT3           : 1; /*  */
        uint16_t PDOUT4           : 1; /*  */
        uint16_t PDOUT5           : 1; /*  */
        uint16_t PDOUT6           : 1; /*  */
        uint16_t PDOUT7           : 1; /*  */
        uint16_t PDOUT8           : 1; /*  */
        uint16_t PDOUT9           : 1; /*  */
        uint16_t PDOUT10          : 1; /*  */
        uint16_t PDOUT11          : 1; /*  */
        uint16_t PDOUT12          : 1; /*  */
        uint16_t PDOUT13          : 1; /*  */
        uint16_t PDOUT14          : 1; /*  */
        uint16_t PDOUT15          : 1; /*  */
    } bits;
} PDOUT_t;

#define p_PDOUT            ((PDOUT_t        *) 0x0262u)
#define PDOUT            p_PDOUT->reg
#define PDOUT_bits        p_PDOUT->bits


/*%%%%% DIRECTION %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 7 Direction */
    struct
    {
        uint8_t P7DIR0          : 1; /*  */
        uint8_t P7DIR1          : 1; /*  */
        uint8_t P7DIR2          : 1; /*  */
        uint8_t P7DIR3          : 1; /*  */
        uint8_t P7DIR4          : 1; /*  */
        uint8_t P7DIR5          : 1; /*  */
        uint8_t P7DIR6          : 1; /*  */
        uint8_t P7DIR7          : 1; /*  */
    } bits;
} P7DIR_t;

#define p_P7DIR            ((P7DIR_t        *) 0x0264u)
#define P7DIR            p_P7DIR->reg
#define P7DIR_bits        p_P7DIR->bits


typedef volatile union
{
    uint8_t reg;            /* Port 8 Direction */
    struct
    {
        uint8_t P8DIR0          : 1; /*  */
        uint8_t P8DIR1          : 1; /*  */
        uint8_t P8DIR2          : 1; /*  */
        uint8_t P8DIR3          : 1; /*  */
        uint8_t P8DIR4          : 1; /*  */
        uint8_t P8DIR5          : 1; /*  */
        uint8_t P8DIR6          : 1; /*  */
        uint8_t P8DIR7          : 1; /*  */
    } bits;
} P8DIR_t;

#define p_P8DIR            ((P8DIR_t        *) 0x0265u)
#define P8DIR            p_P8DIR->reg
#define P8DIR_bits        p_P8DIR->bits


typedef volatile union
{
    uint16_t reg;        /* Port D Direction */
    struct
    {
        uint16_t PDDIR0          : 1; /*  */
        uint16_t PDDIR1          : 1; /*  */
        uint16_t PDDIR2          : 1; /*  */
        uint16_t PDDIR3          : 1; /*  */
        uint16_t PDDIR4          : 1; /*  */
        uint16_t PDDIR5          : 1; /*  */
        uint16_t PDDIR6          : 1; /*  */
        uint16_t PDDIR7          : 1; /*  */
        uint16_t PDDIR8          : 1; /*  */
        uint16_t PDDIR9          : 1; /*  */
        uint16_t PDDIR10         : 1; /*  */
        uint16_t PDDIR11         : 1; /*  */
        uint16_t PDDIR12         : 1; /*  */
        uint16_t PDDIR13         : 1; /*  */
        uint16_t PDDIR14         : 1; /*  */
        uint16_t PDDIR15         : 1; /*  */
    } bits;
} PDDIR_t;

#define p_PDDIR            ((PDDIR_t        *) 0x0264u)
#define PDDIR            p_PDDIR->reg
#define PDDIR_bits        p_PDDIR->bits


/*%%%%% RESISTOR ENABLE %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 7 Resistor Enable */
    struct
    {
        uint8_t P7REN0          : 1; /*  */
        uint8_t P7REN1          : 1; /*  */
        uint8_t P7REN2          : 1; /*  */
        uint8_t P7REN3          : 1; /*  */
        uint8_t P7REN4          : 1; /*  */
        uint8_t P7REN5          : 1; /*  */
        uint8_t P7REN6          : 1; /*  */
        uint8_t P7REN7          : 1; /*  */
    } bits;
} P7REN_t;

#define p_P7REN            ((P7REN_t        *) 0x0266u)
#define P7REN            p_P7REN->reg
#define P7REN_bits        p_P7REN->bits


typedef volatile union
{
    uint8_t reg;            /* Port 8 Resistor Enable */
    struct
    {
        uint8_t P8REN0          : 1; /*  */
        uint8_t P8REN1          : 1; /*  */
        uint8_t P8REN2          : 1; /*  */
        uint8_t P8REN3          : 1; /*  */
        uint8_t P8REN4          : 1; /*  */
        uint8_t P8REN5          : 1; /*  */
        uint8_t P8REN6          : 1; /*  */
        uint8_t P8REN7          : 1; /*  */
    } bits;
} P8REN_t;

#define p_P8REN            ((P8REN_t        *) 0x0267u)
#define P8REN            p_P8REN->reg
#define P8REN_bits        p_P8REN->bits


typedef volatile union
{
    uint16_t reg;        /* Port D Resistor Enable */
    struct
    {
        uint16_t PDREN0          : 1; /*  */
        uint16_t PDREN1          : 1; /*  */
        uint16_t PDREN2          : 1; /*  */
        uint16_t PDREN3          : 1; /*  */
        uint16_t PDREN4          : 1; /*  */
        uint16_t PDREN5          : 1; /*  */
        uint16_t PDREN6          : 1; /*  */
        uint16_t PDREN7          : 1; /*  */
        uint16_t PDREN8          : 1; /*  */
        uint16_t PDREN9          : 1; /*  */
        uint16_t PDREN10         : 1; /*  */
        uint16_t PDREN11         : 1; /*  */
        uint16_t PDREN12         : 1; /*  */
        uint16_t PDREN13         : 1; /*  */
        uint16_t PDREN14         : 1; /*  */
        uint16_t PDREN15         : 1; /*  */
    } bits;
} PDREN_t;

#define p_PDREN            ((PDREN_t        *) 0x0266u)
#define PDREN            p_PDREN->reg
#define PDREN_bits        p_PDREN->bits


/*%%%%% DRIVE STRENGTH %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 7 Drive Strength */
    struct
    {
        uint8_t P7DS0          : 1; /*  */
        uint8_t P7DS1          : 1; /*  */
        uint8_t P7DS2          : 1; /*  */
        uint8_t P7DS3          : 1; /*  */
        uint8_t P7DS4          : 1; /*  */
        uint8_t P7DS5          : 1; /*  */
        uint8_t P7DS6          : 1; /*  */
        uint8_t P7DS7          : 1; /*  */
    } bits;
} P7DS_t;

#define p_P7DS            ((P7DS_t        *) 0x0268u)
#define P7DS            p_P7DS->reg
#define P7DS_bits        p_P7DS->bits


typedef volatile union
{
    uint8_t reg;            /* Port 8 Drive Strength */
    struct
    {
        uint8_t P8DS0          : 1; /*  */
        uint8_t P8DS1          : 1; /*  */
        uint8_t P8DS2          : 1; /*  */
        uint8_t P8DS3          : 1; /*  */
        uint8_t P8DS4          : 1; /*  */
        uint8_t P8DS5          : 1; /*  */
        uint8_t P8DS6          : 1; /*  */
        uint8_t P8DS7          : 1; /*  */
    } bits;
} P8DS_t;

#define p_P8DS            ((P8DS_t        *) 0x0269u)
#define P8DS            p_P8DS->reg
#define P8DS_bits        p_P8DS->bits


typedef volatile union
{
    uint16_t reg;        /* Port D Drive Strength */
    struct
    {
        uint16_t PDDS0          : 1; /*  */
        uint16_t PDDS1          : 1; /*  */
        uint16_t PDDS2          : 1; /*  */
        uint16_t PDDS3          : 1; /*  */
        uint16_t PDDS4          : 1; /*  */
        uint16_t PDDS5          : 1; /*  */
        uint16_t PDDS6          : 1; /*  */
        uint16_t PDDS7          : 1; /*  */
        uint16_t PDDS8          : 1; /*  */
        uint16_t PDDS9          : 1; /*  */
        uint16_t PDDS10         : 1; /*  */
        uint16_t PDDS11         : 1; /*  */
        uint16_t PDDS12         : 1; /*  */
        uint16_t PDDS13         : 1; /*  */
        uint16_t PDDS14         : 1; /*  */
        uint16_t PDDS15         : 1; /*  */
    } bits;
} PDDS_t;

#define p_PDDS            ((PDDS_t        *) 0x0268u)
#define PDDS            p_PDDS->reg
#define PDDS_bits        p_PDDS->bits


/*%%%%% SELECT %%%%%*/

typedef volatile union
{
    uint8_t reg;            /* Port 7 Select */
    struct
    {
        uint8_t P7SEL0          : 1; /*  */
        uint8_t P7SEL1          : 1; /*  */
        uint8_t P7SEL2          : 1; /*  */
        uint8_t P7SEL3          : 1; /*  */
        uint8_t P7SEL4          : 1; /*  */
        uint8_t P7SEL5          : 1; /*  */
        uint8_t P7SEL6          : 1; /*  */
        uint8_t P7SEL7          : 1; /*  */
    } bits;
} P7SEL_t;

#define p_P7SEL            ((P7SEL_t        *) 0x026Au)
#define P7SEL            p_P7SEL->reg
#define P7SEL_bits        p_P7SEL->bits


typedef volatile union
{
    uint8_t reg;            /* Port 8 Select */
    struct
    {
        uint8_t P8SEL0          : 1; /*  */
        uint8_t P8SEL1          : 1; /*  */
        uint8_t P8SEL2          : 1; /*  */
        uint8_t P8SEL3          : 1; /*  */
        uint8_t P8SEL4          : 1; /*  */
        uint8_t P8SEL5          : 1; /*  */
        uint8_t P8SEL6          : 1; /*  */
        uint8_t P8SEL7          : 1; /*  */
    } bits;
} P8SEL_t;

#define p_P8SEL            ((P8SEL_t        *) 0x026Bu)
#define P8SEL            p_P8SEL->reg
#define P8SEL_bits        p_P8SEL->bits


typedef volatile union
{
    uint16_t reg;        /* Port D Select */
    struct
    {
        uint16_t PDSEL0          : 1; /*  */
        uint16_t PDSEL1          : 1; /*  */
        uint16_t PDSEL2          : 1; /*  */
        uint16_t PDSEL3          : 1; /*  */
        uint16_t PDSEL4          : 1; /*  */
        uint16_t PDSEL5          : 1; /*  */
        uint16_t PDSEL6          : 1; /*  */
        uint16_t PDSEL7          : 1; /*  */
        uint16_t PDSEL8          : 1; /*  */
        uint16_t PDSEL9          : 1; /*  */
        uint16_t PDSEL10         : 1; /*  */
        uint16_t PDSEL11         : 1; /*  */
        uint16_t PDSEL12         : 1; /*  */
        uint16_t PDSEL13         : 1; /*  */
        uint16_t PDSEL14         : 1; /*  */
        uint16_t PDSEL15         : 1; /*  */
    } bits;
} PDSEL_t;

#define p_PDSEL            ((PDSEL_t        *) 0x026Au)
#define PDSEL            p_PDSEL->reg
#define PDSEL_bits        p_PDSEL->bits







/*#############################################################################
 *   Port J (8-bit access only)
*############################################################################*/


/*%%%%% INPUT %%%%%*/

typedef volatile union
{
    uint8_t reg;      /* Port J Input */
    struct
    {
        unsigned __READ char PJIN0           : 1; /*  */
        unsigned __READ char PJIN1           : 1; /*  */
        unsigned __READ char PJIN2           : 1; /*  */
        unsigned __READ char PJIN3           : 1; /*  */
        unsigned __READ char PJIN4           : 1; /*  */
        unsigned __READ char PJIN5           : 1; /*  */
        unsigned __READ char PJIN6           : 1; /*  */
        unsigned __READ char PJIN7           : 1; /*  */
    } bits;
} PJIN_t;

#define p_PJIN                  ((PJIN_t            *) 0x0320u)
#define PJIN                    p_PJIN->reg
#define PJIN_bits               p_PJIN->bits


/*%%%%% OUTPUT %%%%%*/

typedef volatile union
{
    uint8_t reg;      /* Port J Output */
    struct
    {
        uint8_t PJOUT0           : 1; /*  */
        uint8_t PJOUT1           : 1; /*  */
        uint8_t PJOUT2           : 1; /*  */
        uint8_t PJOUT3           : 1; /*  */
        uint8_t PJOUT4           : 1; /*  */
        uint8_t PJOUT5           : 1; /*  */
        uint8_t PJOUT6           : 1; /*  */
        uint8_t PJOUT7           : 1; /*  */
    } bits;
} PJOUT_t;

#define p_PJOUT                 ((PJOUT_t           *) 0x0322u)
#define PJOUT                   p_PJOUT->reg
#define PJOUT_bits              p_PJOUT->bits


/*%%%%% DIRECTION %%%%%*/

typedef volatile union
{
    uint8_t reg;      /* Port J Direction */
    struct
    {
        uint8_t PJDIR0          : 1; /*  */
        uint8_t PJDIR1          : 1; /*  */
        uint8_t PJDIR2          : 1; /*  */
        uint8_t PJDIR3          : 1; /*  */
        uint8_t PJDIR4          : 1; /*  */
        uint8_t PJDIR5          : 1; /*  */
        uint8_t PJDIR6          : 1; /*  */
        uint8_t PJDIR7          : 1; /*  */
    } bits;
} PJDIR_t;

#define p_PJDIR                 ((PJDIR_t           *) 0x0324u)
#define PJDIR                   p_PJDIR->reg
#define PJDIR_bits              p_PJDIR->bits


/*%%%%% RESISTOR ENABLE %%%%%*/

typedef volatile union
{
    uint8_t reg;      /* Port J Resistor Enable */
    struct
    {
        uint8_t PJREN0          : 1; /*  */
        uint8_t PJREN1          : 1; /*  */
        uint8_t PJREN2          : 1; /*  */
        uint8_t PJREN3          : 1; /*  */
        uint8_t PJREN4          : 1; /*  */
        uint8_t PJREN5          : 1; /*  */
        uint8_t PJREN6          : 1; /*  */
        uint8_t PJREN7          : 1; /*  */
    } bits;
} PJREN_t;

#define p_PJREN                 ((PJREN_t           *) 0x0326u)
#define PJREN                   p_PJREN->reg
#define PJREN_bits              p_PJREN->bits


/*%%%%% DRIVE STRENGTH %%%%%*/

typedef volatile union
{
    uint8_t reg;      /* Port J Drive Strength */
    struct
    {
        uint8_t PJDS0          : 1; /*  */
        uint8_t PJDS1          : 1; /*  */
        uint8_t PJDS2          : 1; /*  */
        uint8_t PJDS3          : 1; /*  */
        uint8_t PJDS4          : 1; /*  */
        uint8_t PJDS5          : 1; /*  */
        uint8_t PJDS6          : 1; /*  */
        uint8_t PJDS7          : 1; /*  */
    } bits;
} PJDS_t;

#define p_PJDS                  ((PJDS_t            *) 0x0328u)
#define PJDS                    p_PJDS->reg
#define PJDS_bits               p_PJDS->bits







/*#########################################################################
 *   Port Mapping Control
*##########################################################################*/


/* Port Mapping Key register */
typedef volatile uint16_t PMAPKEYID_t;
#define p_PMAPKEYID                 ((PMAPKEYID_t     *) 0x01C0u)
#define PMAPKEYID                   *p_PMAPKEYID


typedef volatile union
{
    uint16_t reg;   /* Port Mapping control register */
    struct
    {
        uint16_t PMAPLOCKED           : 1; /* Port Mapping Lock bit. Read only */
        uint16_t PMAPRECFG            : 1; /* Port Mapping re-configuration control bit */
    } bits;
} PMAPCTL_t;

#define p_PMAPCTL                   ((PMAPCTL_t            *) 0x01C2u)
#define PMAPCTL                     p_PMAPCTL->reg
#define PMAPCTL_bits                p_PMAPCTL->bits



#define PM_NONE         0       /* INPUT: None, OUTPUT: DVSS */
#define PM_CBOUT0       1       /* INPUT: n/a, OUTPUT: Comparator_B output */
#define PM_TB0CLK       1       /* INPUT: TB0 clock input, OUTPUT: n/a */
#define PM_ADC12CLK     2       /* INPUT: n/a, OUTPUT: ADC12CLK */
#define PM_DMAE0        2       /* INPUT: DMAE0 input, OUTPUT: n/a */
#define PM_SVMOUT       3       /* INPUT: n/a, OUTPUT: SVM output */
#define PM_TB0OUTH      3       /* INPUT: TB0 high impedance input TB0OUTH, OUTPUT: n/a */
#define PM_TB0CCR0A     4       /* INPUT: TB0 CCR0 capture input CCI0A, OUTPUT: TB0 CCR0 compare output Out0 */
#define PM_TB0CCR1A     5       /* INPUT: TB0 CCR1 capture input CCI1A, OUTPUT: TB0 CCR1 compare output Out1 */
#define PM_TB0CCR2A     6       /* INPUT: TB0 CCR2 capture input CCI2A, OUTPUT: TB0 CCR2 compare output Out2 */
#define PM_TB0CCR3A     7       /* INPUT: TB0 CCR3 capture input CCI3A, OUTPUT: TB0 CCR3 compare output Out3 */
#define PM_TB0CCR4A     8       /* INPUT: TB0 CCR4 capture input CCI4A, OUTPUT: TB0 CCR4 compare output Out4 */
#define PM_TB0CCR5A     9       /* INPUT: TB0 CCR5 capture input CCI5A, OUTPUT: TB0 CCR5 compare output Out5 */
#define PM_TB0CCR6A     10      /* INPUT: TB0 CCR6 capture input CCI6A, OUTPUT: TB0 CCR6 compare output Out6 */
#define PM_UCA1RXD      11      /* USCI_A1 UART RXD (Direction controlled by USCI - input) */
#define PM_UCA1SOMI     11      /* USCI_A1 SPI slave out master in (direction controlled by USCI) */
#define PM_UCA1TXD      12      /* USCI_A1 UART TXD (Direction controlled by USCI - output) */
#define PM_UCA1SIMO     12      /* USCI_A1 SPI slave in master out (direction controlled by USCI) */
#define PM_UCA1CLK      13      /* USCI_A1 clock input/output (direction controlled by USCI) */
#define PM_UCB1STE      13      /* USCI_B1 SPI slave transmit enable (direction controlled by USCI) */
#define PM_UCB1SOMI     14      /* USCI_B1 SPI slave out master in (direction controlled by USCI) */
#define PM_UCB1SCL      14      /* USCI_B1 I2C clock (open drain and direction controlled by USCI) */
#define PM_UCB1SIMO     15      /* USCI_B1 SPI slave in master out (direction controlled by USCI) */
#define PM_UCB1SDA      15      /* USCI_B1 I2C data (open drain and direction controlled by USCI) */
#define PM_UCB1CLK      16      /* USCI_B1 clock input/output (direction controlled by USCI) */
#define PM_UCA1STE      16      /* USCI_A1 SPI slave transmit enable (direction controlled by USCI) */
#define PM_CBOUT1       17      /* INPUT: None, OUTPUT: Comparator_B output */
#define PM_MCLK         18      /* INPUT: None, OUTPUT: MCLK */

/* The value of the PM_ANALOG mnemonic is set to 0FFh. The port mapping registers
 * are only 5 bits wide and the upper bits are ignored resulting in a read out
 * value of 31. Using this mnemonic disables the output driver as well as the
 * input Schmitt-trigger to prevent parasitic cross currents when applying
 * analog signals.*/
#define PM_ANALOG       0xFF







/*#########################################################################
 *   Port Mapping Port 4
*##########################################################################*/

// Not supported yet




/*#########################################################################
 *   PMM  Power Management System
*##########################################################################*/


typedef volatile uint16_t PMMCTL0_t;
#define p_PMMCTL0                ((PMMCTL0_t              *) 0x0120u)
#define PMMCTL0                  *p_PMMCTL0

#define PMMPW               (0xA500u)  /* PMM Register Write Password */

#define PMMCOREV_0          (0x0000u)  /* PMM Core Voltage 0 (1.35V) */
#define PMMCOREV_1          (0x0001u)  /* PMM Core Voltage 1 (1.55V) */
#define PMMCOREV_2          (0x0002u)  /* PMM Core Voltage 2 (1.75V) */
#define PMMCOREV_3          (0x0003u)  /* PMM Core Voltage 3 (1.85V) */


typedef volatile uint16_t PMMCTL1_t;
#define p_PMMCTL1                ((PMMCTL1_t              *) 0x0122u)
#define PMMCTL1                  *p_PMMCTL1


typedef volatile union
{
    uint16_t reg;   /* SVS and SVM high side control register */
    struct
    {
        uint16_t SVSMHRRLx        : 3; /* SVS and SVM high side Reset Release Voltage Level Bits */
        uint16_t SVSMHDLYST       : 1; /* SVS and SVM high side delay status */
        uint16_t SVSHMD           : 1; /* SVS high side mode */
        uint16_t                  : 1;
        uint16_t SVSMHEVM         : 1; /* SVS and SVM high side event mask */
        uint16_t SVSMHACE         : 1; /* SVS and SVM high side auto control enable */
        uint16_t SVSHRVLx         : 2; /* SVS high side reset voltage level Bits */
        uint16_t SVSHE            : 1; /* SVS high side enable */
        uint16_t SVSHFP           : 1; /* SVS high side full performace mode */
        uint16_t SVMHOVPE         : 1; /* SVM high side over-voltage enable */
        uint16_t                  : 1;
        uint16_t SVMHE            : 1; /* SVM high side enable */
        uint16_t SVMHFP           : 1; /* SVM high side full performace mode */
    } bits;
} SVSMHCTL_t;

#define p_SVSMHCTL              ((SVSMHCTL_t            *) 0x0124u)
#define SVSMHCTL                p_SVSMHCTL->reg
#define SVSMHCTL_bits           p_SVSMHCTL->bits


typedef volatile union
{
    uint16_t reg;   /* SVS and SVM low side control register */
    struct
    {
        uint16_t SVSMLRRLx        : 3; /* SVS and SVM low side Reset Release Voltage Level Bits */
        uint16_t SVSMLDLYST       : 1; /* SVS and SVM low side delay status */
        uint16_t SVSLMD           : 1; /* SVS low side mode */
        uint16_t                  : 1;
        uint16_t SVSMLEVM         : 1; /* SVS and SVM low side event mask */
        uint16_t SVSMLACE         : 1; /* SVS and SVM low side auto control enable */
        uint16_t SVSLRVLx         : 2; /* SVS low side reset voltage level Bits */
        uint16_t SVSLE            : 1; /* SVS low side enable */
        uint16_t SVSLFP           : 1; /* SVS low side full performace mode */
        uint16_t SVMLOVPE         : 1; /* SVM low side over-voltage enable */
        uint16_t                  : 1;
        uint16_t SVMLE            : 1; /* SVM low side enable */
        uint16_t SVMLFP           : 1; /* SVM low side full performace mode */
    } bits;
} SVSMLCTL_t;

#define p_SVSMLCTL              ((SVSMLCTL_t            *) 0x0126u)
#define SVSMLCTL                p_SVSMLCTL->reg
#define SVSMLCTL_bits           p_SVSMLCTL->bits


typedef volatile union
{
    uint16_t reg;   /* SVSIN and SVSOUT control register */
    struct
    {
        uint16_t                  : 3;
        uint16_t SVMLOE           : 1; /* SVM low side output enable */
        uint16_t SVMLVLROE        : 1; /* SVM low side voltage level reached output enable */
        uint16_t SVMOUTPOL        : 1; /* SVMOUT pin polarity */
        uint16_t                  : 5;
        uint16_t SVMHOE           : 1; /* SVM high side output enable */
        uint16_t SVMHVLROE        : 1; /* SVM high side voltage level reached output enable */
    } bits;
} SVSMIO_t;

#define p_SVSMIO                ((SVSMIO_t              *) 0x0128u)
#define SVSMIO                  p_SVSMIO->reg
#define SVSMIO_bits             p_SVSMIO->bits


typedef volatile union
{
    uint16_t reg;   /* PMM Interrupt Flag */
    struct
    {
        uint16_t SVSMLDLYIFG      : 1; /* SVS and SVM low side Delay expired interrupt flag */
        uint16_t SVMLIFG          : 1; /* SVM low side interrupt flag */
        uint16_t SVMLVLRIFG       : 1; /* SVM low side Voltage Level Reached interrupt flag */
        uint16_t                  : 1;
        uint16_t SVSMHDLYIFG      : 1; /* SVS and SVM high side Delay expired interrupt flag */
        uint16_t SVMHIFG          : 1; /* SVM high side interrupt flag */
        uint16_t SVMHVLRIFG       : 1; /* SVM high side Voltage Level Reached interrupt flag */
        uint16_t                  : 1;
        uint16_t PMMBORIFG        : 1; /* PMM Software BOR interrupt flag */
        uint16_t PMMRSTIFG        : 1; /* PMM RESET pin interrupt flag */
        uint16_t PMMPORIFG        : 1; /* PMM Software POR interrupt flag */
        uint16_t                  : 1;
        uint16_t SVSHIFG          : 1; /* SVS low side interrupt flag */
        uint16_t SVSLIFG          : 1; /* SVS high side interrupt flag */
        uint16_t                  : 1;
        uint16_t PMMLPM5IFG       : 1; /* LPM5 indication Flag */
    } bits;
} PMMIFG_t;

#define p_PMMIFG                ((PMMIFG_t              *) 0x012Cu)
#define PMMIFG                  p_PMMIFG->reg
#define PMMIFG_bits             p_PMMIFG->bits


typedef volatile union
{
    uint16_t reg;   /* PMM and RESET Interrupt Enable */
    struct
    {
        uint16_t SVSMLDLYIE       : 1; /* SVS and SVM low side Delay expired interrupt enable */
        uint16_t SVMLIE           : 1; /* SVM low side interrupt enable */
        uint16_t SVMLVLRIE        : 1; /* SVM low side Voltage Level Reached interrupt enable */
        uint16_t                  : 1;
        uint16_t SVSMHDLYIE       : 1; /* SVS and SVM high side Delay expired interrupt enable */
        uint16_t SVMHIE           : 1; /* SVM high side interrupt enable */
        uint16_t SVMHVLRIE        : 1; /* SVM high side Voltage Level Reached interrupt enable */
        uint16_t                  : 1;
        uint16_t SVSLPE           : 1; /* SVS low side POR enable */
        uint16_t SVMLVLRPE        : 1; /* SVM low side Voltage Level reached POR enable */
        uint16_t                  : 2;
        uint16_t SVSHPE           : 1; /* SVS high side POR enable */
        uint16_t SVMHVLRPE        : 1; /* SVM high side Voltage Level reached POR enable */
    } bits;
} PMMRIE_t;

#define p_PMMRIE                ((PMMRIE_t              *) 0x012Eu)
#define PMMRIE                  p_PMMRIE->reg
#define PMMRIE_bits             p_PMMRIE->bits


typedef volatile union
{
    uint16_t reg;   /* PMM Power Mode 5 Control Register 0 */
    struct
    {
        uint16_t LOCKLPM5        : 1; /* Lock I/O pin configuration upon entry/exit to/from LPM5 */
    } bits;
} PM5CTL0_t;

#define p_PM5CTL0               ((PM5CTL0_t             *) 0x0130u)
#define PM5CTL0                 p_PM5CTL0->reg
#define PM5CTL0_bits            p_PM5CTL0->bits







/*#########################################################################
 *   RC  RAM Control Module
*##########################################################################*/

// Not supported yet



/*#########################################################################
 *   Shared Reference
*##########################################################################*/

// Not supported yet



/*#########################################################################
 *   RTC  Real Time Clock
*##########################################################################*/

// Not supported yet



/*#########################################################################
 *   SFR  Special Function Registers
 *#########################################################################*/


typedef volatile union
{
    uint16_t reg;   /* Interrupt Enable 1 */
    struct
    {
        uint16_t WDTIE            : 1; /* WDT Interrupt Enable */
        uint16_t OFIE             : 1; /* Osc Fault Enable */
        uint16_t                  : 1;
        uint16_t VMAIE            : 1; /* Vacant Memory Interrupt Enable */
        uint16_t NMIIE            : 1; /* NMI Interrupt Enable */
        uint16_t ACCVIE           : 1; /* Flash Access Violation Interrupt Enable */
        uint16_t JMBINIE          : 1; /* JTAG Mail Box input Interrupt Enable */
        uint16_t JMBOUTIE         : 1; /* JTAG Mail Box output Interrupt Enable */
    } bits;
} SFRIE1_t;

#define p_SFRIE1            ((SFRIE1_t       *) 0x0100u)
#define SFRIE1              p_SFRIE1->reg
#define SFRIE1_bits         p_SFRIE1->bits


typedef volatile union
{
    uint16_t reg;   /* Interrupt Flag 1 */
    struct
    {
        uint16_t WDTIFG           : 1; /* WDT Interrupt Flag */
        uint16_t OFIFG            : 1; /* Osc Fault Flag */
        uint16_t                  : 1;
        uint16_t VMAIFG           : 1; /* Vacant Memory Interrupt Flag */
        uint16_t NMIIFG           : 1; /* NMI Interrupt Flag */
        uint16_t                  : 1;
        uint16_t JMBINIFG         : 1; /* JTAG Mail Box input Interrupt Flag */
        uint16_t JMBOUTIFG        : 1; /* JTAG Mail Box output Interrupt Flag */
    } bits;
} SFRIFG1_t;

#define p_SFRIFG1           ((SFRIFG1_t       *) 0x0102u)
#define SFRIFG1             p_SFRIFG1->reg
#define SFRIFG1_bits        p_SFRIFG1->bits


typedef volatile union
{
    uint16_t reg;   /* RESET Pin Control Register */
    struct
    {
        uint16_t SYSNMI           : 1; /* NMI select */
        uint16_t SYSNMIIES        : 1; /* NMI edge select */
        uint16_t SYSRSTUP         : 1; /* RESET Pin pull down/up select */
        uint16_t SYSRSTRE         : 1; /* RESET Pin Resistor enable */
    } bits;
} SFRRPCR_t;

#define p_SFRRPCR           ((SFRRPCR_t       *) 0x0104u)
#define SFRRPCR             p_SFRRPCR->reg
#define SFRRPCR_bits        p_SFRRPCR->bits







/*#########################################################################
 *   SYS  System Module
 *#########################################################################*/

// Not supported yet



/*#########################################################################
 *   Timer0_A5
 *#########################################################################*/


typedef volatile union
{
    uint16_t reg;     /* Timer0_A5 Control */
    struct
    {
        uint16_t TAIFG            : 1; /* Timer A counter interrupt flag */
        uint16_t TAIE             : 1; /* Timer A counter interrupt enable */
        uint16_t TACLR            : 1; /* Timer A counter clear */
        uint16_t                  : 1;
        uint16_t MCx              : 2; /* Timer A mode control bits */
        uint16_t IDx              : 2; /* Timer A clock input divider bits */
        uint16_t TASSELx          : 2; /* Timer A clock source select bits */
    } bits;
} TA0CTL_t;

#define p_TA0CTL                ((TA0CTL_t              *) 0x0340u)
#define TA0CTL                  p_TA0CTL->reg
#define TA0CTL_bits             p_TA0CTL->bits


typedef volatile union
{
    uint16_t reg;   /* Timer0_A5 Capture/Compare Control 0 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t                  : 1;
        uint16_t SCCI             : 1; /* Latched capture signal (read) */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TA0CCTL0_t;

#define p_TA0CCTL0              ((TA0CCTL0_t            *) 0x0342u)
#define TA0CCTL0                p_TA0CCTL0->reg
#define TA0CCTL0_bits           p_TA0CCTL0->bits


typedef volatile union
{
    uint16_t reg;   /* Timer0_A5 Capture/Compare Control 1 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t                  : 1;
        uint16_t SCCI             : 1; /* Latched capture signal (read) */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TA0CCTL1_t;

#define p_TA0CCTL1              ((TA0CCTL1_t        *) 0x0344u)
#define TA0CCTL1                p_TA0CCTL1->reg
#define TA0CCTL1_bits           p_TA0CCTL1->bits


typedef volatile union
{
    uint16_t reg;   /* Timer0_A5 Capture/Compare Control 2 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t                  : 1;
        uint16_t SCCI             : 1; /* Latched capture signal (read) */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TA0CCTL2_t;

#define p_TA0CCTL2              ((TA0CCTL2_t        *) 0x0346u)
#define TA0CCTL2                p_TA0CCTL2->reg
#define TA0CCTL2_bits           p_TA0CCTL2->bits


typedef volatile union
{
    uint16_t reg;   /* Timer0_A5 Capture/Compare Control 3 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t                  : 1;
        uint16_t SCCI             : 1; /* Latched capture signal (read) */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TA0CCTL3_t;

#define p_TA0CCTL3              ((TA0CCTL3_t        *) 0x0348u)
#define TA0CCTL3                p_TA0CCTL3->reg
#define TA0CCTL3_bits           p_TA0CCTL3->bits


typedef volatile union
{
    uint16_t reg;   /* Timer0_A5 Capture/Compare Control 4 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t                  : 1;
        uint16_t SCCI             : 1; /* Latched capture signal (read) */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TA0CCTL4_t;

#define p_TA0CCTL4              ((TA0CCTL4_t        *) 0x034Au)
#define TA0CCTL4                p_TA0CCTL4->reg
#define TA0CCTL4_bits           p_TA0CCTL4->bits


  /* Timer0_A5 */
typedef volatile uint16_t TA0R_t;
#define p_TA0R                  ((TA0R_t        *) 0x0350u)
#define TA0R                    *p_TA0R

  /* Timer0_A5 Capture/Compare 0 */
typedef volatile uint16_t TA0CCR0_t;
#define p_TA0CCR0               ((TA0CCR0_t     *) 0x0352u)
#define TA0CCR0                 *p_TA0CCR0

  /* Timer0_A5 Capture/Compare 1 */
typedef volatile uint16_t TA0CCR1_t;
#define p_TA0CCR1               ((TA0CCR1_t     *) 0x0354u)
#define TA0CCR1                 *p_TA0CCR1

  /* Timer0_A5 Capture/Compare 2 */
typedef volatile uint16_t TA0CCR2_t;
#define p_TA0CCR2               ((TA0CCR2_t     *) 0x0356u)
#define TA0CCR2                 *p_TA0CCR2

  /* Timer0_A5 Capture/Compare 3 */
typedef volatile uint16_t TA0CCR3_t;
#define p_TA0CCR3               ((TA0CCR3_t     *) 0x0358u)
#define TA0CCR3                 *p_TA0CCR3

  /* Timer0_A5 Capture/Compare 4 */
typedef volatile uint16_t TA0CCR4_t;
#define p_TA0CCR4               ((TA0CCR4_t     *) 0x035Au)
#define TA0CCR4                 *p_TA0CCR4

  /* Timer0_A5 Interrupt Vector Word */
typedef volatile uint16_t TA0IV_t;
#define p_TA0IV                 ((TA0IV_t       *) 0x036Eu)
#define TA0IV                   *p_TA0IV


typedef volatile union
{
    uint16_t reg;   /* Timer0_A5 Expansion Register 0 */
    struct
    {
        uint16_t TAIDEXx          : 3; /* Timer A Input divider expansion Bits */
    } bits;
} TA0EX0_t;

#define p_TA0EX0              ((TA0EX0_t        *) 0x0360u)
#define TA0EX0                p_TA0EX0->reg
#define TA0EX0_bits           p_TA0EX0->bits







/*#########################################################################
 *   Timer1_A3
 *#########################################################################*/


typedef volatile union
{
    uint16_t reg;   /* Timer1_A3 Control */
    struct
    {
        uint16_t TAIFG            : 1; /* Timer A counter interrupt flag */
        uint16_t TAIE             : 1; /* Timer A counter interrupt enable */
        uint16_t TACLR            : 1; /* Timer A counter clear */
        uint16_t                  : 1;
        uint16_t MCx              : 2; /* Timer A mode control bits */
        uint16_t IDx              : 2; /* Timer A clock input divider bits */
        uint16_t TASSELx          : 2; /* Timer A clock source select bits */
   } bits;
} TA1CTL_t;

#define p_TA1CTL                ((TA1CTL_t          *) 0x0380u)
#define TA1CTL                  p_TA1CTL->reg
#define TA1CTL_bits             p_TA1CTL->bits


typedef volatile union
{
    uint16_t reg;   /* Timer1_A3 Capture/Compare Control 0 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t                  : 1;
        uint16_t SCCI             : 1; /* Latched capture signal (read) */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TA1CCTL0_t;

#define p_TA1CCTL0              ((TA1CCTL0_t        *) 0x0382u)
#define TA1CCTL0                p_TA1CCTL0->reg
#define TA1CCTL0_bits           p_TA1CCTL0->bits


typedef volatile union
{
    uint16_t reg;   /* Timer1_A3 Capture/Compare Control 1 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t                  : 1;
        uint16_t SCCI             : 1; /* Latched capture signal (read) */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TA1CCTL1_t;

#define p_TA1CCTL1              ((TA1CCTL1_t        *) 0x0384u)
#define TA1CCTL1                p_TA1CCTL1->reg
#define TA1CCTL1_bits           p_TA1CCTL1->bits


typedef volatile union
{
    uint16_t reg;   /* Timer1_A3 Capture/Compare Control 2 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t                  : 1;
        uint16_t SCCI             : 1; /* Latched capture signal (read) */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TA1CCTL2_t;

#define p_TA1CCTL2              ((TA1CCTL2_t        *) 0x0386u)
#define TA1CCTL2                p_TA1CCTL2->reg
#define TA1CCTL2_bits           p_TA1CCTL2->bits


  /* Timer1_A3 */
typedef volatile uint16_t TA1R_t;
#define p_TA1R                  ((TA1R_t        *) 0x0390u)
#define TA1R                    *p_TA1R

  /* Timer1_A3 Capture/Compare 0 */
typedef volatile uint16_t TA1CCR0_t;
#define p_TA1CCR0               ((TA1CCR0_t     *) 0x0392u)
#define TA1CCR0                 *p_TA1CCR0

  /* Timer1_A3 Capture/Compare 1 */
typedef volatile uint16_t TA1CCR1_t;
#define p_TA1CCR1               ((TA1CCR1_t     *) 0x0394u)
#define TA1CCR1                 *p_TA1CCR1

  /* Timer1_A3 Capture/Compare 2 */
typedef volatile uint16_t TA1CCR2_t;
#define p_TA1CCR2               ((TA1CCR2_t     *) 0x0396u)
#define TA1CCR2                 *p_TA1CCR2

  /* Timer1_A3 Interrupt Vector Word */
typedef volatile uint16_t TA1IV_t;
#define p_TA1IV                 ((TA1IV_t       *) 0x03AEu)
#define TA1IV                   *p_TA1IV

typedef volatile union
{
    uint16_t reg;   /* Timer1_A3 Expansion Register 0 */
    struct
    {
        uint16_t TAIDEXx          : 3; /* Timer A Input divider expansion Bits */
    } bits;
} TA1EX0_t;

#define p_TA1EX0                ((TA1EX0_t      *) 0x03A0u)
#define TA1EX0                  p_TA1EX0->reg
#define TA1EX0_bits             p_TA1EX0->bits







/*#########################################################################
 *   Timer2_A3
 *#########################################################################*/

typedef volatile union
{
    uint16_t reg;   /* Timer2_A3 Control */
    struct
    {
        uint16_t TAIFG            : 1; /* Timer A counter interrupt flag */
        uint16_t TAIE             : 1; /* Timer A counter interrupt enable */
        uint16_t TACLR            : 1; /* Timer A counter clear */
        uint16_t                  : 1;
        uint16_t MCx              : 2; /* Timer A mode control bits */
        uint16_t IDx              : 2; /* Timer A clock input divider bits */
        uint16_t TASSELx          : 2; /* Timer A clock source select bits */
    } bits;
} TA2CTL_t;

#define p_TA2CTL                ((TA2CTL_t          *) 0x0400u)
#define TA2CTL                  p_TA2CTL->reg
#define TA2CTL_bits             p_TA2CTL->bits


typedef volatile union
{
    uint16_t reg;   /* Timer2_A3 Capture/Compare Control 0 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t                  : 1;
        uint16_t SCCI             : 1; /* Latched capture signal (read) */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TA2CCTL0_t;

#define p_TA2CCTL0              ((TA2CCTL0_t        *) 0x0402u)
#define TA2CCTL0                p_TA2CCTL0->reg
#define TA2CCTL0_bits           p_TA2CCTL0->bits


typedef volatile union
{
    uint16_t reg;   /* Timer2_A3 Capture/Compare Control 1 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t                  : 1;
        uint16_t SCCI             : 1; /* Latched capture signal (read) */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TA2CCTL1_t;

#define p_TA2CCTL1              ((TA2CCTL1_t        *) 0x0404u)
#define TA2CCTL1                p_TA2CCTL1->reg
#define TA2CCTL1_bits           p_TA2CCTL1->bits


typedef volatile union
{
    uint16_t reg;   /* Timer2_A3 Capture/Compare Control 2 */
    struct
    {
        uint16_t CCIFG           : 1; /* Capture/compare interrupt flag */
        uint16_t COV             : 1; /* Capture/compare overflow flag */
        uint16_t OUT             : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI             : 1; /* Capture input signal (read) */
        uint16_t CCIE            : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx         : 3; /* Output mode bits */
        uint16_t CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t                : 1;
        uint16_t SCCI            : 1; /* Latched capture signal (read) */
        uint16_t SCS             : 1; /* Capture sychronize */
        uint16_t CCISx           : 2; /* Capture input select bits */
        uint16_t CMx             : 2; /* Capture mode bits */
    } bits;
} TA2CCTL2_t;

#define p_TA2CCTL2              ((TA2CCTL2_t        *) 0x0406u)
#define TA2CCTL2                p_TA2CCTL2->reg
#define TA2CCTL2_bits           p_TA2CCTL2->bits


  /* Timer2_A3 */
typedef volatile uint16_t TA2R_t;
#define p_TA2R                  ((TA2R_t        *) 0x0410u)
#define TA2R                    *p_TA2R

  /* Timer2_A3 Capture/Compare 0 */
typedef volatile uint16_t TA2CCR0_t;
#define p_TA2CCR0               ((TA2CCR0_t     *) 0x0412u)
#define TA2CCR0                 *p_TA2CCR0

  /* Timer2_A3 Capture/Compare 1 */
typedef volatile uint16_t TA2CCR1_t;
#define p_TA2CCR1               ((TA2CCR1_t     *) 0x0414u)
#define TA2CCR1                 *p_TA2CCR1

  /* Timer2_A3 Capture/Compare 2 */
typedef volatile uint16_t TA2CCR2_t;
#define p_TA2CCR2               ((TA2CCR2_t     *) 0x0416u)
#define TA2CCR2                 *p_TA2CCR2

  /* Timer2_A3 Interrupt Vector Word */
typedef volatile uint16_t TA2IV_t;
#define p_TA2IV                 ((TA2IV_t       *) 0x042Eu)
#define TA2IV                   *p_TA2IV


typedef volatile union
{
    uint16_t reg;   /* Timer2_A3 Expansion Register 0 */
    struct
    {
        uint16_t TAIDEXx         : 3; /* Timer A Input divider expansion Bits */
    } bits;
} TA2EX0_t;

#define p_TA2EX0                ((TA2EX0_t      *) 0x0420u)
#define TA2EX0                  p_TA2EX0->reg
#define TA2EX0_bits             p_TA2EX0->bits









/*#########################################################################
 *   Timer0_B7
*#########################################################################*/


typedef volatile union
{
    uint16_t reg;   /* Timer0_B7 Control */
    struct
    {
        uint16_t TBIFG            : 1; /* Timer0_B7 interrupt flag */
        uint16_t TBIE             : 1; /* Timer0_B7 interrupt enable */
        uint16_t TBCLR            : 1; /* Timer0_B7 counter clear */
        uint16_t                  : 1;
        uint16_t MCx              : 2; /* Timer A mode control bits */
        uint16_t IDx              : 2; /* Timer A clock input divider bits */
        uint16_t TBSSELx          : 2; /* Clock source bits */
        uint16_t                  : 1;
        uint16_t CNTLx            : 2; /* Counter lenght bits */
        uint16_t TBCLGRP0         : 1; /* Timer0_B7 Compare latch load group 0 */
        uint16_t TBCLGRP1         : 1; /* Timer0_B7 Compare latch load group 1 */
    } bits;
} TB0CTL_t;

#define p_TB0CTL                ((TB0CTL_t          *) 0x03C0u)
#define TB0CTL                  p_TB0CTL->reg
#define TB0CTL_bits             p_TB0CTL->bits


typedef volatile union
{
    uint16_t reg;   /* Timer0_B7 Capture/Compare Control 0 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t CLLDx            : 2; /* Compare latch load source bits */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TB0CCTL0_t;

#define p_TB0CCTL0              ((TB0CCTL0_t        *) 0x03C2u)
#define TB0CCTL0                p_TB0CCTL0->reg
#define TB0CCTL0_bits           p_TB0CCTL0->bits


typedef volatile union
{
    uint16_t reg;   /* Timer0_B7 Capture/Compare Control 1 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t CLLDx            : 2; /* Compare latch load source bits */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TB0CCTL1_t;

#define p_TB0CCTL1              ((TB0CCTL1_t        *) 0x03C4u)
#define TB0CCTL1                p_TB0CCTL1->reg
#define TB0CCTL1_bits           p_TB0CCTL1->bits


typedef volatile union
{
    uint16_t reg;   /* Timer0_B7 Capture/Compare Control 2 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t CLLDx            : 2; /* Compare latch load source bits */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TB0CCTL2_t;

#define p_TB0CCTL2              ((TB0CCTL2_t        *) 0x03C6u)
#define TB0CCTL2                p_TB0CCTL2->reg
#define TB0CCTL2_bits           p_TB0CCTL2->bits


typedef volatile union
{
    uint16_t reg;   /* Timer0_B7 Capture/Compare Control 3 */
    struct
    {
        uint16_t CCIFG           : 1; /* Capture/compare interrupt flag */
        uint16_t COV             : 1; /* Capture/compare overflow flag */
        uint16_t OUT             : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI             : 1; /* Capture input signal (read) */
        uint16_t CCIE            : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx         : 3; /* Output mode bits */
        uint16_t CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t CLLDx           : 1; /* Compare latch load source bits */
        uint16_t SCS             : 1; /* Capture sychronize */
        uint16_t CCISx           : 2; /* Capture input select bits */
        uint16_t CMx             : 2; /* Capture mode bits */
    } bits;
} TB0CCTL3_t;

#define p_TB0CCTL3              ((TB0CCTL3_t        *) 0x03C8u)
#define TB0CCTL3                p_TB0CCTL3->reg
#define TB0CCTL3_bits           p_TB0CCTL3->bits


typedef volatile union
{
    uint16_t reg;   /* Timer0_B7 Capture/Compare Control 4 */
    struct
    {
        uint16_t CCIFG           : 1; /* Capture/compare interrupt flag */
        uint16_t COV             : 1; /* Capture/compare overflow flag */
        uint16_t OUT             : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI             : 1; /* Capture input signal (read) */
        uint16_t CCIE            : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx         : 3; /* Output mode bits */
        uint16_t CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t CLLDx           : 2; /* Compare latch load source bits */
        uint16_t SCS             : 1; /* Capture sychronize */
        uint16_t CCISx           : 2; /* Capture input select bits */
        uint16_t CMx             : 2; /* Capture mode bits */
    } bits;
} TB0CCTL4_t;

#define p_TB0CCTL4              ((TB0CCTL4_t        *) 0x03CAu)
#define TB0CCTL4                p_TB0CCTL4->reg
#define TB0CCTL4_bits           p_TB0CCTL4->bits


typedef volatile union
{
    uint16_t reg;   /* Timer0_B7 Capture/Compare Control 5 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t CLLDx            : 2; /* Compare latch load source bits */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TB0CCTL5_t;

#define p_TB0CCTL5              ((TB0CCTL5_t        *) 0x03CCu)
#define TB0CCTL5                p_TB0CCTL5->reg
#define TB0CCTL5_bits           p_TB0CCTL5->bits


typedef volatile union
{
    uint16_t reg;   /* Timer0_B7 Capture/Compare Control 6 */
    struct
    {
        uint16_t CCIFG            : 1; /* Capture/compare interrupt flag */
        uint16_t COV              : 1; /* Capture/compare overflow flag */
        uint16_t OUT              : 1; /* PWM Output signal if output mode 0 */
        uint16_t CCI              : 1; /* Capture input signal (read) */
        uint16_t CCIE             : 1; /* Capture/compare interrupt enable */
        uint16_t OUTMODx          : 3; /* Output mode bits */
        uint16_t CAP              : 1; /* Capture mode: 1 /Compare mode : 0 */
        uint16_t CLLDx            : 2; /* Compare latch load source bits */
        uint16_t SCS              : 1; /* Capture sychronize */
        uint16_t CCISx            : 2; /* Capture input select bits */
        uint16_t CMx              : 2; /* Capture mode bits */
    } bits;
} TB0CCTL6_t;

#define p_TB0CCTL6              ((TB0CCTL6_t        *) 0x03CEu)
#define TB0CCTL6                p_TB0CCTL6->reg
#define TB0CCTL6_bits           p_TB0CCTL6->bits


  /* Timer0_B7 */
typedef volatile uint16_t TB0R_t;
#define p_TB0R                  ((TB0R_t        *) 0x03D0u)
#define TB0R                    *p_TB0R

  /* Timer0_B7 Capture/Compare 0 */
typedef volatile uint16_t TB0CCR0_t;
#define p_TB0CCR0               ((TB0CCR0_t     *) 0x03D2u)
#define TB0CCR0                 *p_TB0CCR0

  /* Timer0_B7 Capture/Compare 1 */
typedef volatile uint16_t TB0CCR1_t;
#define p_TB0CCR1               ((TB0CCR1_t     *) 0x03D4u)
#define TB0CCR1                 *p_TB0CCR1

  /* Timer0_B7 Capture/Compare 2 */
typedef volatile uint16_t TB0CCR2_t;
#define p_TB0CCR2               ((TB0CCR2_t     *) 0x03D6u)
#define TB0CCR2                 *p_TB0CCR2

  /* Timer0_B7 Capture/Compare 3 */
typedef volatile uint16_t TB0CCR3_t;
#define p_TB0CCR3               ((TB0CCR3_t     *) 0x03D8u)
#define TB0CCR3                 *p_TB0CCR3

  /* Timer0_B7 Capture/Compare 4 */
typedef volatile uint16_t TB0CCR4_t;
#define p_TB0CCR4               ((TB0CCR4_t     *) 0x03DAu)
#define TB0CCR4                 *p_TB0CCR4

  /* Timer0_B7 Capture/Compare 5 */
typedef volatile uint16_t TB0CCR5_t;
#define p_TB0CCR5               ((TB0CCR5_t     *) 0x03DCu)
#define TB0CCR5                 *p_TB0CCR5

  /* Timer0_B7 Capture/Compare 6 */
typedef volatile uint16_t TB0CCR6_t;
#define p_TB0CCR6               ((TB0CCR6_t     *) 0x03DEu)
#define TB0CCR6                 *p_TB0CCR6

/* Timer0_B7 Interrupt Vector Word */
typedef volatile uint16_t TB0IV_t;
#define p_TB0IV                 ((TB0IV_t       *) 0x03EEu)
#define TB0IV                   *p_TB0IV


typedef volatile union
{
    uint16_t reg;   /* Timer0_B7 Expansion Register 0 */
    struct
    {
        uint16_t TBIDEXx         : 3; /* Timer0_B7 Input divider expansion Bits */
    } bits;
} TB0EX0_t;

#define p_TB0EX0                ((TB0EX0_t      *) 0x03E0u)
#define TB0EX0                  p_TB0EX0->reg
#define TB0EX0_bits             p_TB0EX0->bits







/*#########################################################################
 *   USB Configuration Registers
 *#########################################################################*/

// Not supported yet



/*#########################################################################
 *   USB Control Registers
 *#########################################################################*/

// Not supported yet



/*#########################################################################
 *   UCS  Unified System Clock
 *#########################################################################*/


typedef volatile union
{
    uint16_t reg;     /* UCS Control Register 0 */
    struct
    {
        uint16_t              : 3;
        uint16_t MODx         : 5; /* Modulation Bit Counter Bits */
        uint16_t DCOx         : 5; /* DCO TAP Bits */
    } bits;
} UCSCTL0_t;

#define p_UCSCTL0           ((UCSCTL0_t         *) 0x0160u)
#define UCSCTL0             p_UCSCTL0->reg
#define UCSCTL0_bits        p_UCSCTL0->bits

enum {
    MOD0            = 0x0008,
    MOD1            = 0x0010,
    MOD2            = 0x0020,
    MOD3            = 0x0040,
    MOD4            = 0x0080,
    DCO0            = 0x0100,
    DCO1            = 0x0200,
    DCO2            = 0x0400,
    DCO3            = 0x0800,
    DCO4            = 0x1000
};


typedef volatile union
{
    uint16_t reg;     /* UCS Control Register 1 */
    struct
    {
        uint16_t DISMOD       : 1; /* Disable Modulation */
        uint16_t              : 3;
        uint16_t DCORSELx     : 3; /* DCO Freq. Range Select Bits */
    } bits;
} UCSCTL1_t;

#define p_UCSCTL1           ((UCSCTL1_t         *) 0x0162u)
#define UCSCTL1             p_UCSCTL1->reg
#define UCSCTL1_bits        p_UCSCTL1->bits

enum {
    DISMOD          = 0x0001,
    DCORSEL0        = 0x0010,
    DCORSEL1        = 0x0020,
    DCORSEL2        = 0x0040
};


typedef volatile union
{
    uint16_t reg;     /* UCS Control Register 2 */
    struct
    {
        uint16_t FLLNx        : 10; /* FLL Multipier Bits */
        uint16_t              : 2;
        uint16_t FLLDx        : 3; /* Loop Divider Bits */
    } bits;
} UCSCTL2_t;

#define p_UCSCTL2           ((UCSCTL2_t         *) 0x0164u)
#define UCSCTL2             p_UCSCTL2->reg
#define UCSCTL2_bits        p_UCSCTL2->bits

enum {
    FLLN0           = 0x0001,
    FLLN1           = 0x0002,
    FLLN2           = 0x0004,
    FLLN3           = 0x0008,
    FLLN4           = 0x0010,
    FLLN5           = 0x0020,
    FLLN6           = 0x0040,
    FLLN7           = 0x0080,
    FLLN8           = 0x0100,
    FLLN9           = 0x0200,
    FLLD0           = 0x1000,
    FLLD1           = 0x2000,
    FLLD2           = 0x4000
};


typedef volatile union
{
    uint16_t reg;     /* UCS Control Register 3 */
    struct
    {
        uint16_t FLLREFDIVx   : 3; /* Reference Divider Bits */
        uint16_t              : 1;
        uint16_t SELREFx      : 3; /* FLL Reference Clock Select Bits */
    } bits;
} UCSCTL3_t;

#define p_UCSCTL3           ((UCSCTL3_t         *) 0x0166u)
#define UCSCTL3             p_UCSCTL3->reg
#define UCSCTL3_bits        p_UCSCTL3->bits

enum {
    FLLREFDIV0      = 0x0001,
    FLLREFDIV1      = 0x0002,
    FLLREFDIV2      = 0x0004,
    SELREF0         = 0x0010,
    SELREF1         = 0x0020,
    SELREF2         = 0x0040
};


typedef volatile union
{
    uint16_t reg;     /* UCS Control Register 4 */
    struct
    {
        uint16_t SELMx        : 3; /* MCLK Source Select Bits */
        uint16_t              : 1;
        uint16_t SELSx        : 3; /* SMCLK Source Select Bits */
        uint16_t              : 1;
        uint16_t SELAx        : 3; /* ACLK Source Select Bits */
    } bits;
} UCSCTL4_t;

#define p_UCSCTL4           ((UCSCTL4_t         *) 0x0168u)
#define UCSCTL4             p_UCSCTL4->reg
#define UCSCTL4_bits        p_UCSCTL4->bits

enum {
    SELM0           = 0x0001,
    SELM1           = 0x0002,
    SELM2           = 0x0004,
    SELS0           = 0x0010,
    SELS1           = 0x0020,
    SELS2           = 0x0040,
    SELA0           = 0x0100,
    SELA1           = 0x0200,
    SELA2           = 0x0400
};


typedef volatile union
{
    uint16_t reg;     /* UCS Control Register 5 */
    struct
    {
        uint16_t DIVMx        : 3; /* MCLK Divider Bits */
        uint16_t              : 1;
        uint16_t DIVSx        : 3; /* SMCLK Divider Bits */
        uint16_t              : 1;
        uint16_t DIVAx        : 3; /* ACLK Divider Bits */
        uint16_t              : 1;
        uint16_t DIVPAx       : 3; /* ACLK from Pin Divider Bits */
    } bits;
} UCSCTL5_t;

#define p_UCSCTL5           ((UCSCTL5_t         *) 0x016Au)
#define UCSCTL5             p_UCSCTL5->reg
#define UCSCTL5_bits        p_UCSCTL5->bits

enum {
    DIVM0           = 0x0001,
    DIVM1           = 0x0002,
    DIVM2           = 0x0004,
    DIVS0           = 0x0010,
    DIVS1           = 0x0020,
    DIVS2           = 0x0040,
    DIVA0           = 0x0100,
    DIVA1           = 0x0200,
    DIVA2           = 0x0400,
    DIVPA0          = 0x1000,
    DIVPA1          = 0x2000,
    DIVPA2          = 0x4000
};


typedef volatile union
{
    uint16_t reg;     /* UCS Control Register 6 */
    struct
    {
        uint16_t XT1OFF       : 1; /* High Frequency Oscillator 1 (XT1) disable */
        uint16_t SMCLKOFF     : 1; /* SMCLK Off */
        uint16_t XCAPx        : 2; /* XIN/XOUT Cap Bits */
        uint16_t XT1BYPASS    : 1; /* XT1 bypass mode : 0: internal 1:sourced from external pin */
        uint16_t XTS          : 1; /* 1: Selects high-freq. oscillator */
        uint16_t XT1DRIVEx    : 2; /* XT1 Drive Level mode Bits */
        uint16_t XT2OFF       : 1; /* High Frequency Oscillator 2 (XT2) disable */
        uint16_t              : 3;
        uint16_t XT2BYPASS    : 1; /* XT2 bypass mode : 0: internal 1:sourced from external pin */
        uint16_t              : 1;
        uint16_t XT2DRIVEx    : 2; /* XT2 Drive Level mode Bits */
    } bits;
} UCSCTL6_t;

#define p_UCSCTL6           ((UCSCTL6_t         *) 0x016Cu)
#define UCSCTL6             p_UCSCTL6->reg
#define UCSCTL6_bits        p_UCSCTL6->bits

enum {
    XT1OFF          = 0x0001,
    SMCLKOFF        = 0x0002,
    XCAP0           = 0x0004,
    XCAP1           = 0x0008,
    XT1BYPASS       = 0x0010,
    XTS             = 0x0020,
    XT1DRIVE0       = 0x0040,
    XT1DRIVE1       = 0x0080,
    XT2OFF          = 0x0100,
    XT2BYPASS       = 0x1000,
    XT2DRIVE0       = 0x4000,
    XT2DRIVE1       = 0x8000
};


typedef volatile union
{
    uint16_t reg;     /* UCS Control Register 7 */
    struct
    {
        uint16_t DCOFFG       : 1; /* DCO Fault Flag */
        uint16_t XT1LFOFFG    : 1; /* XT1 Low Frequency Oscillator Fault Flag */
        uint16_t XT1HFOFFG    : 1; /* XT1 High Frequency Oscillator Fault Flag */
        uint16_t XT2OFFG      : 1; /* High Frequency Oscillator 2 Fault Flag */
    } bits;
} UCSCTL7_t;

#define p_UCSCTL7           ((UCSCTL7_t         *) 0x016Eu)
#define UCSCTL7             p_UCSCTL7->reg
#define UCSCTL7_bits        p_UCSCTL7->bits

enum {
    DCOFFG          = 0x0001,
    XT1LFOFFG       = 0x0002,
    XT1HFOFFG       = 0x0004,
    XT2OFFG         = 0x0008
};


typedef volatile union
{
    uint16_t reg;     /* UCS Control Register 8 */
    struct
    {
        uint16_t ACLKREQEN    : 1; /* ACLK Clock Request Enable */
        uint16_t MCLKREQEN    : 1; /* MCLK Clock Request Enable */
        uint16_t SMCLKREQEN   : 1; /* SMCLK Clock Request Enable */
        uint16_t MODOSCREQEN  : 1; /* MODOSC Clock Request Enable */
    } bits;
} UCSCTL8_t;

#define p_UCSCTL8           ((UCSCTL8_t         *) 0x0170u)
#define UCSCTL8             p_UCSCTL8->reg
#define UCSCTL8_bits        p_UCSCTL8->bits

enum {
    ACLKREQEN       = 0x0001,
    MCLKREQEN       = 0x0002,
    SMCLKREQEN      = 0x0004,
    MODOSCREQEN     = 0x0008
};







/*#########################################################################
 *   USCI_A0 & USCI_A1  UART and SPI Modes
 *#########################################################################*/


typedef volatile union
{
    uint8_t reg;     /* USCI control 1 */
    union
    {
        struct
        {
            uint8_t UCSWRST       : 1; /* USCI Software Reset */
            uint8_t UCTXBRK       : 1; /* Send next Data as Break */
            uint8_t UCTXADDR      : 1; /* Send next Data as Address */
            uint8_t UCDORM        : 1; /* Dormant (Sleep) Mode */
            uint8_t UCBRKIE       : 1; /* Break interrupt enable */
            uint8_t UCRXEIE       : 1; /* RX Error interrupt enable */
            uint8_t UCSSELx       : 2; /* USCI 0 Clock Source Select bits */
        };
        struct
        {
            uint8_t               : 1; /* UCSYNC */
            uint8_t               : 2; /* UCMODEx */
            uint8_t UCMST         : 1; /* Master mode select: 0:slave, 1:master */
            uint8_t               : 1; /* UC7BIT */
            uint8_t               : 1; /* UCMSB */
            uint8_t UCCKPL        : 1; /* Clock polarity select: 0:inactive low, 1:inactive high */
            uint8_t UCCKPH        : 1; /* Clock phase select: 0:data changed on UCLK edge
                                                                    1:data captured on UCLK edge. */
        };
    } bits;
} UCAxCTL1_t;

#define p_UCA0CTL1          ((UCAxCTL1_t         *) 0x05C0u)
#define UCA0CTL1            p_UCA0CTL1->reg
#define UCA0CTL1_bits       p_UCA0CTL1->bits

#define p_UCA1CTL1          ((UCAxCTL1_t         *) 0x0600u)
#define UCA1CTL1            p_UCA1CTL1->reg
#define UCA1CTL1_bits       p_UCA1CTL1->bits


typedef volatile union
{
    uint8_t reg;     /* USCI control 0 */
    union
    {
        struct
        {
            uint8_t UCSYNC        : 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
            uint8_t UCMODEx       : 2; /* Async. Mode: USCI Mode Bits */
            uint8_t UCSPB         : 1; /* Async. Mode: Stop Bits  0:one / 1: two */
            uint8_t UC7BIT        : 1; /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
            uint8_t UCMSB         : 1; /* Async. Mode: MSB first  0:LSB / 1:MSB */
            uint8_t UCPAR         : 1; /* Async. Mode: Parity     0:odd / 1:even */
            uint8_t UCPEN         : 1; /* Async. Mode: Parity enable */
        };
        struct
        {
            uint8_t               : 1; /* UCSYNC */
            uint8_t               : 2; /* UCMODEx */
            uint8_t UCMST         : 1; /* Master mode select: 0:slave, 1:master */
            uint8_t               : 1; /* UC7BIT */
            uint8_t               : 1; /* UCMSB */
            uint8_t UCCKPL        : 1; /* Clock polarity select: 0:inactive low, 1:inactive high */
            uint8_t UCCKPH        : 1; /* Clock phase select: 0:data changed on UCLK edge
                                                                    1:data captured on UCLK edge. */
        };
    } bits;
} UCAxCTL0_t;

#define p_UCA0CTL0          ((UCAxCTL0_t         *) 0x05C1u)
#define UCA0CTL0            p_UCA0CTL0->reg
#define UCA0CTL0_bits       p_UCA0CTL0->bits

#define p_UCA1CTL0          ((UCAxCTL0_t         *) 0x0601u)
#define UCA1CTL0            p_UCA1CTL0->reg
#define UCA1CTL0_bits       p_UCA1CTL0->bits


/* USCI baud rate control word */
typedef volatile uint16_t UCAxBRW_t;
#define p_UCA0BRW               ((UCAxBRW_t     *) 0x05C6u)
#define UCA0BRW                 *p_UCA0BRW
#define p_UCA1BRW               ((UCAxBRW_t     *) 0x0606u)
#define UCA1BRW                 *p_UCA1BRW

/* USCI baud rate 0 */
typedef volatile uint8_t UCAxBR0_t;
#define p_UCA0BR0               ((UCAxBR0_t     *) 0x05C6u)
#define UCA0BR0                 *p_UCA0BR0
#define p_UCA1BR0               ((UCAxBR0_t     *) 0x0606u)
#define UCA1BR0                 *p_UCA1BR0

/* USCI baud rate 1 */
typedef volatile uint8_t UCAxBR1_t;
#define p_UCA0BR1               ((UCAxBR1_t     *) 0x05C7u)
#define UCA0BR1                 *p_UCA0BR1
#define p_UCA1BR1               ((UCAxBR1_t     *) 0x0607u)
#define UCA1BR1                 *p_UCA1BR1


typedef volatile union
{
    uint8_t reg;     /* USCI modulation control */
    struct
    {
        uint8_t UCOS16        : 1; /* USCI 16-times Oversampling enable */
        uint8_t UCBRSx        : 3; /* USCI Second Stage Modulation Select Bits */
        uint8_t UCBRFx        : 4; /* USCI First Stage Modulation Select Bits */
    } bits;
} UCAxMCTL_t;

#define p_UCA0MCTL          ((UCAxMCTL_t         *) 0x05C8u)
#define UCA0MCTL            p_UCA0MCTL->reg
#define UCA0MCTL_bits       p_UCA0MCTL->bits

#define p_UCA1MCTL          ((UCAxMCTL_t         *) 0x0608u)
#define UCA1MCTL            p_UCA1MCTL->reg
#define UCA1MCTL_bits       p_UCA1MCTL->bits


typedef volatile union
{
    uint8_t reg;     /* USCI status */
    struct
    {
        uint8_t UCBUSY        : 1; /* USCI Busy Flag */
        uint8_t UCADDR        : 1; /* USCI Address received Flag */
        uint8_t UCRXERR       : 1; /* USCI RX Error Flag */
        uint8_t UCBRK         : 1; /* USCI Break received */
        uint8_t UCPE          : 1; /* USCI Parity Error Flag */
        uint8_t UCOE          : 1; /* USCI Overrun Error Flag */
        uint8_t UCFE          : 1; /* USCI Frame Error Flag */
        uint8_t UCLISTEN      : 1; /* USCI Listen mode */
    } bits;
} UCAxSTAT_t;

#define p_UCA0STAT          ((UCAxSTAT_t         *) 0x05CAu)
#define UCA0STAT            p_UCA0STAT->reg
#define UCA0STAT_bits       p_UCA0STAT->bits

#define p_UCA1STAT          ((UCAxSTAT_t         *) 0x060Au)
#define UCA1STAT            p_UCA1STAT->reg
#define UCA1STAT_bits       p_UCA1STAT->bits


/* USCI receive buffer */
typedef volatile uint8_t UCAxRXBUF_t;
#define p_UCA0RXBUF             ((UCAxRXBUF_t     *) 0x05CCu)
#define UCA0RXBUF               *p_UCA0RXBUF
#define p_UCA1RXBUF             ((UCAxRXBUF_t     *) 0x060Cu)
#define UCA1RXBUF               *p_UCA1RXBUF


/* USCI transmit buffer */
typedef volatile uint8_t UCAxTXBUF_t;
#define p_UCA0TXBUF             ((UCAxTXBUF_t     *) 0x05CEu)
#define UCA0TXBUF               *p_UCA0TXBUF
#define p_UCA1TXBUF             ((UCAxTXBUF_t     *) 0x060Eu)
#define UCA1TXBUF               *p_UCA1TXBUF


typedef volatile union
{
    uint8_t reg;     /* USCI auto baud rate control */
    struct
    {
        uint8_t UCABDEN       : 1; /* Auto Baud Rate detect enable */
        uint8_t               : 1;
        uint8_t UCBTOE        : 1; /* Break Timeout error */
        uint8_t UCSTOE        : 1; /* Sync-Field Timeout error */
        uint8_t UCDELIMx      : 2; /* Break Sync Delimiter Bits */
    } bits;
} UCAxABCTL_t;

#define p_UCA0ABCTL         ((UCAxABCTL_t         *) 0x05D0u)
#define UCA0ABCTL           p_UCA0ABCTL->reg
#define UCA0ABCTL_bits      p_UCA0ABCTL->bits

#define p_UCA1ABCTL         ((UCAxABCTL_t         *) 0x0610u)
#define UCA1ABCTL           p_UCA1ABCTL->reg
#define UCA1ABCTL_bits      p_UCA1ABCTL->bits


typedef volatile union
{
    uint8_t reg;     /* USCI IrDA transmit control */
    struct
    {
        uint8_t UCIREN        : 1; /* IRDA Encoder/Decoder enable */
        uint8_t UCIRTXCLK     : 1; /* IRDA Transmit Pulse Clock Select */
        uint8_t UCIRTXPLx     : 6; /* IRDA Transmit Pulse Length Bits */
    } bits;
} UCAxIRTCTL_t;

#define p_UCA0IRTCTL        ((UCAxIRTCTL_t         *) 0x05D2u)
#define UCA0IRTCTL          p_UCA0IRTCTL->reg
#define UCA0IRTCTL_bits     p_UCA0IRTCTL->bits

#define p_UCA1IRTCTL        ((UCAxIRTCTL_t         *) 0x0612u)
#define UCA1IRTCTL          p_UCA1IRTCTL->reg
#define UCA1IRTCTL_bits     p_UCA1IRTCTL->bits


typedef volatile union
{
    uint8_t reg;     /* USCI IrDA receive control */
    struct
    {
        uint8_t UCIRRXFE      : 1; /* IRDA Receive Filter enable */
        uint8_t UCIRRXPL      : 1; /* IRDA Receive Input Polarity */
        uint8_t UCIRRXFLx     : 6; /* IRDA Receive Filter Length Bits */
    } bits;
} UCAxIRRCTL_t;

#define p_UCA0IRRCTL        ((UCAxIRRCTL_t         *) 0x05D3u)
#define UCA0IRRCTL          p_UCA0IRRCTL->reg
#define UCA0IRRCTL_bits     p_UCA0IRRCTL->bits

#define p_UCA1IRRCTL        ((UCAxIRRCTL_t         *) 0x0613u)
#define UCA1IRRCTL          p_UCA1IRRCTL->reg
#define UCA1IRRCTL_bits     p_UCA1IRRCTL->bits


typedef volatile union
{
    uint8_t reg;     /* USCI interrupt enable */
    struct
    {
        uint8_t UCRXIE        : 1; /* USCI Receive Interrupt Enable */
        uint8_t UCTXIE        : 1; /* USCI Transmit Interrupt Enable */
    } bits;
} UCAxIE_t;

#define p_UCA0IE            ((UCAxIE_t         *) 0x05DCu)
#define UCA0IE              p_UCA0IE->reg
#define UCA0IE_bits         p_UCA0IE->bits

#define p_UCA1IE            ((UCAxIE_t         *) 0x061Cu)
#define UCA1IE              p_UCA1IE->reg
#define UCA1IE_bits         p_UCA1IE->bits


typedef volatile union
{
    uint8_t reg;     /* USCI interrupt flags */
    struct
    {
        uint8_t UCRXIFG       : 1; /* USCI Receive Interrupt Flag */
        uint8_t UCTXIFG       : 1; /* USCI Transmit Interrupt Flag */
    } bits;
} UCAxIFG_t;

#define p_UCA0IFG           ((UCAxIFG_t         *) 0x05DDu)
#define UCA0IFG             p_UCA0IFG->reg
#define UCA0IFG_bits        p_UCA0IFG->bits

#define p_UCA1IFG           ((UCAxIFG_t         *) 0x061Du)
#define UCA1IFG             p_UCA1IFG->reg
#define UCA1IFG_bits        p_UCA1IFG->bits


/* USCI interrupt vector word */
typedef volatile uint16_t UCAxIV_t;
#define p_UCA0IV                ((UCAxIV_t     *) 0x05DEu)
#define UCA0IV                  *p_UCA0IV
#define p_UCA1IV                ((UCAxIV_t     *) 0x061Eu)
#define UCA1IV                  *p_UCA1IV







/*#########################################################################
 *   USCI_B0 & USCI_B1  I2C and SPI Modes
 *#########################################################################*/


typedef volatile union
{
    uint8_t reg;     /* USCI synchronous control 1 */
    struct
    {
        uint8_t UCSWRST       : 1; /* USCI Software Reset */
        uint8_t UCTXSTT       : 1; /* Transmit START */
        uint8_t UCTXSTP       : 1; /* Transmit STOP */
        uint8_t UCTXNACK      : 1; /* Transmit NACK */
        uint8_t UCTR          : 1; /* Transmit/Receive Select/Flag */
        uint8_t               : 1;
        uint8_t UCSSELx       : 2; /* USCI Clock Source Select Bits */
    } bits;
} UCBxCTL1_t;

#define p_UCB0CTL1          ((UCBxCTL1_t         *) 0x05E0u)
#define UCB0CTL1            p_UCB0CTL1->reg
#define UCB0CTL1_bits       p_UCB0CTL1->bits

#define p_UCB1CTL1          ((UCBxCTL1_t         *) 0x0620u)
#define UCB1CTL1            p_UCB1CTL1->reg
#define UCB1CTL1_bits       p_UCB1CTL1->bits


typedef volatile union
{
    uint8_t reg;     /* USCI synchronous control 0  */
    union
    {
        struct
        {
            uint8_t UCSYNC        : 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
            uint8_t UCMODEx       : 2; /* Async. Mode: USCI Mode Bits */
            uint8_t UCMST         : 1; /* Sync. Mode: Master Select */
            uint8_t               : 1;
            uint8_t UCMM          : 1; /* Multi-Master Environment */
            uint8_t UCSLA10       : 1; /* 10-bit Slave Address Mode */
            uint8_t UCA10         : 1; /* 10-bit Address Mode */
        };
        struct
        {
            uint8_t               : 1; /* UCSYNC */
            uint8_t               : 2; /* UCMODEx */
            uint8_t               : 1; /* UCMST */
            uint8_t               : 1; /* UC7BIT */
            uint8_t               : 1; /* UCMSB */
            uint8_t UCCKPL        : 1; /* Clock polarity select: 0:inactive low, 1:inactive high */
            uint8_t UCCKPH        : 1; /* Clock phase select: 0:data changed on UCLK edge
                                                                    1:data captured on UCLK edge. */
        };
    } bits;
} UCBxCTL0_t;

#define p_UCB0CTL0          ((UCBxCTL0_t         *) 0x05E1u)
#define UCB0CTL0            p_UCB0CTL0->reg
#define UCB0CTL0_bits       p_UCB0CTL0->bits

#define p_UCB1CTL0          ((UCBxCTL0_t         *) 0x0621u)
#define UCB1CTL0            p_UCB1CTL0->reg
#define UCB1CTL0_bits       p_UCB1CTL0->bits


/* USCI synchronous bit rate control word */
typedef volatile uint16_t UCBxBRW_t;
#define p_UCB0BRW               ((UCBxBRW_t     *) 0x05E6u)
#define UCB0BRW                 *p_UCB0BRW
#define p_UCB1BRW               ((UCBxBRW_t     *) 0x05E6u)
#define UCB1BRW                 *p_UCB1BRW

/* USCI synchronous bit rate 0  */
typedef volatile uint8_t UCBxBR0_t;
#define p_UCB0BR0               ((UCBxBR0_t     *) 0x05E6u)
#define UCB0BR0                 *p_UCB0BR0
#define p_UCB1BR0               ((UCBxBR0_t     *) 0x0626u)
#define UCB1BR0                 *p_UCB1BR0

/* USCI synchronous bit rate 1  */
typedef volatile uint8_t UCBxBR1_t;
#define p_UCB0BR1               ((UCBxBR1_t     *) 0x05E7u)
#define UCB0BR1                 *p_UCB0BR1
#define p_UCB1BR1               ((UCBxBR1_t     *) 0x0627u)
#define UCB1BR1                 *p_UCB1BR1


typedef volatile union
{
    uint8_t reg;     /* USCI synchronous status  */
    union
    {
        struct
        {
            uint8_t               : 4;
            uint8_t UCBBUSY       : 1; /* Bus Busy Flag */
            uint8_t UCGC          : 1; /* General Call address received Flag */
            uint8_t UCSCLLOW      : 1; /* SCL low */
        };
        struct
        {
            uint8_t UCBUSY        : 1; /* USCI Busy Flag */
            uint8_t               : 4;
            uint8_t UCOE          : 1; /* USCI Overrun Error Flag */
            uint8_t UCFE          : 1; /* USCI Frame Error Flag */
            uint8_t UCLISTEN      : 1; /* USCI Listen mode */
        };
    } bits;
} UCBxSTAT_t;

#define p_UCB0STAT          ((UCBxSTAT_t         *) 0x05EAu)
#define UCB0STAT            p_UCB0STAT->reg
#define UCB0STAT_bits       p_UCB0STAT->bits

#define p_UCB1STAT          ((UCBxSTAT_t         *) 0x062Au)
#define UCB1STAT            p_UCB1STAT->reg
#define UCB1STAT_bits       p_UCB1STAT->bits


/* USCI synchronous receive buffer */
typedef volatile uint8_t UCBxRXBUF_t;
#define p_UCB0RXBUF             ((UCBxRXBUF_t     *) 0x05ECu)
#define UCB0RXBUF               *p_UCB0RXBUF
#define p_UCB1RXBUF             ((UCBxRXBUF_t     *) 0x062Cu)
#define UCB1RXBUF               *p_UCB1RXBUF


/* USCI synchronous transmit buffer */
typedef volatile uint8_t UCBxTXBUF_t;
#define p_UCB0TXBUF             ((UCBxTXBUF_t     *) 0x05EEu)
#define UCB0TXBUF               *p_UCB0TXBUF
#define p_UCB1TXBUF             ((UCBxTXBUF_t     *) 0x062Eu)
#define UCB1TXBUF               *p_UCB1TXBUF


typedef volatile union
{
    uint16_t reg;     /* USCI I2C own address */
    struct
    {
        uint16_t I2COAx       : 10; /* I2C Own Address Bits */
        uint16_t              : 5;
        uint16_t UCGCEN       : 1;  /* I2C General Call enable */
    } bits;
} UCBxI2COA_t;

#define p_UCB0I2COA         ((UCBxI2COA_t         *) 0x05F0u)
#define UCB0I2COA           p_UCB0I2COA->reg
#define UCB0I2COA_bits      p_UCB0I2COA->bits

#define p_UCB1I2COA         ((UCBxI2COA_t         *) 0x0630u)
#define UCB1I2COA           p_UCB1I2COA->reg
#define UCB1I2COA_bits      p_UCB1I2COA->bits


typedef volatile union
{
    uint16_t reg;     /* USCI I2C slave address */
    struct
    {
        uint16_t I2CSAx       : 10; /* I2C Own Address Bits */
    } bits;
} UCBxI2CSA_t;

#define p_UCB0I2CSA         ((UCBxI2CSA_t         *) 0x05F2u)
#define UCB0I2CSA           p_UCB0I2CSA->reg
#define UCB0I2CSA_bits      p_UCB0I2CSA->bits

#define p_UCB1I2CSA         ((UCBxI2CSA_t         *) 0x0632u)
#define UCB1I2CSA           p_UCB1I2CSA->reg
#define UCB1I2CSA_bits      p_UCB1I2CSA->bits


typedef volatile union
{
    uint8_t reg;     /* USCI interrupt enable */
    struct
    {
        uint8_t UCRXIE        : 1; /* I2C/SPI Receive Interrupt Enable */
        uint8_t UCTXIE        : 1; /* I2C/SPI Transmit Interrupt Enable */
        uint8_t UCSTTIE       : 1; /* START Condition interrupt enable */
        uint8_t UCSTPIE       : 1; /* STOP Condition interrupt enable */
        uint8_t UCALIE        : 1; /* Arbitration Lost interrupt enable */
        uint8_t UCNACKIE      : 1; /* NACK Condition interrupt enable */
    } bits;
} UCBxIE_t;

#define p_UCB0IE            ((UCBxIE_t         *) 0x05FCu)
#define UCB0IE              p_UCB0IE->reg
#define UCB0IE_bits         p_UCB0IE->bits

#define p_UCB1IE            ((UCBxIE_t         *) 0x063Cu)
#define UCB1IE              p_UCB1IE->reg
#define UCB1IE_bits         p_UCB1IE->bits


typedef volatile union
{
    uint8_t reg;     /* USCI interrupt flags */
    struct
    {
        uint8_t UCRXIFG       : 1; /* I2C/SPI Receive Interrupt Flag */
        uint8_t UCTXIFG       : 1; /* I2C/SPI Transmit Interrupt Flag */
        uint8_t UCSTTIFG      : 1; /* START Condition interrupt Flag */
        uint8_t UCSTPIFG      : 1; /* STOP Condition interrupt Flag */
        uint8_t UCALIFG       : 1; /* Arbitration Lost interrupt Flag */
        uint8_t UCNACKIFG     : 1; /* NACK Condition interrupt Flag */
    } bits;
} UCBxIFG_t;

#define p_UCB0IFG           ((UCBxIFG_t         *) 0x05FDu)
#define UCB0IFG             p_UCB0IFG->reg
#define UCB0IFG_bits        p_UCB0IFG->bits

#define p_UCB1IFG           ((UCBxIFG_t         *) 0x063Du)
#define UCB1IFG             p_UCB1IFG->reg
#define UCB1IFG_bits        p_UCB1IFG->bits


/* USCI interrupt vector word */
typedef volatile uint16_t UCBxIV_t;
#define p_UCB0IV                ((UCBxIV_t     *) 0x05FEu)
#define UCB0IV                  *p_UCB0IV
#define p_UCB1IV                ((UCBxIV_t     *) 0x063Eu)
#define UCB1IV                  *p_UCB1IV

#define UCBxIV_NO_INTERRUPT      0x00  /* No interrupt pending */
#define UCBxIV_SPI_UCRXIFG       0x02  /* SPI data received */
#define UCBxIV_SPI_UCTXIFG       0x04  /* SPI transmit buffer empty */
#define UCBxIV_I2C_ARBLOSS       0x02  /* I2C Arbitration Lost */
#define UCBxIV_I2C_NACK          0x04  /* I2C not acknowledge */
#define UCBxIV_I2C_START         0x06  /* I2C start condition received */
#define UCBxIV_I2C_STOP          0x08  /* I2C stop condition received */
#define UCBxIV_I2C_UCRXIFG       0x0A  /* I2C data received */
#define UCBxIV_I2C_UCTXIFG       0x0C  /* I2C transmit buffer empty */







/*#########################################################################
 *   Watchdog Timer
*##########################################################################*/


typedef volatile uint16_t WDTCTL_t;   /* Watchdog Timer Control */
#define p_WDTCTL                ((WDTCTL_t              *) 0x015Cu)
#define WDTCTL                  *p_WDTCTL

#define WDTPW               (0x5A00u)

/* The bit names have been prefixed with "WDT" */
/* WDTCTL Control Bits */
#define WDTIS0              (0x0001u)  /* WDT - Timer Interval Select 0 */
#define WDTIS1              (0x0002u)  /* WDT - Timer Interval Select 1 */
#define WDTIS2              (0x0004u)  /* WDT - Timer Interval Select 2 */
#define WDTCNTCL            (0x0008u)  /* WDT - Timer Clear */
#define WDTTMSEL            (0x0010u)  /* WDT - Timer Mode Select */
#define WDTSSEL0            (0x0020u)  /* WDT - Timer Clock Source Select 0 */
#define WDTSSEL1            (0x0040u)  /* WDT - Timer Clock Source Select 1 */
#define WDTHOLD             (0x0080u)  /* WDT - Timer hold */









/************************************************************
* TLV Descriptors
************************************************************/

#define __MSP430_HAS_TLV__              /* Definition to show that Module is available */
#define TLV_BASE __MSP430_BASEADDRESS_TLV__

#define TLV_CRC_LENGTH        (0x1A01)    /* CRC length of the TLV structure */
#define TLV_CRC_VALUE         (0x1A02)    /* CRC value of the TLV structure */
#define TLV_START             (0x1A08)    /* Start Address of the TLV structure */
#define TLV_END               (0x1AFF)    /* End Address of the TLV structure */

#define TLV_LDTAG             (0x01)      /*  Legacy descriptor (1xx, 2xx, 4xx families) */
#define TLV_PDTAG             (0x02)      /*  Peripheral discovery descriptor */
#define TLV_Reserved3         (0x03)      /*  Future usage */
#define TLV_Reserved4         (0x04)      /*  Future usage */
#define TLV_BLANK             (0x05)      /*  Blank descriptor */
#define TLV_Reserved6         (0x06)      /*  Future usage */
#define TLV_Reserved7         (0x07)      /*  Serial Number */
#define TLV_DIERECORD         (0x08)      /*  Die Record  */
#define TLV_ADCCAL            (0x11)      /*  ADC12 calibration */
#define TLV_ADC12CAL          (0x11)      /*  ADC12 calibration */
#define TLV_ADC10CAL          (0x13)      /*  ADC10 calibration */
#define TLV_REFCAL            (0x12)      /*  REF calibration */
#define TLV_TAGEXT            (0xFE)      /*  Tag extender */
#define TLV_TAGEND            (0xFF)      //  Tag End of Table


/************************************************************
* Timer A interrupt vector value
************************************************************/

/* Compability definitions */

#define TAIV_CCIFG1         TAIV_TACCR1       /* Capture/compare 1 */
#define TAIV_CCIFG2         TAIV_TACCR2       /* Capture/compare 2 */
#define TAIV_CCIFG3         TAIV_6            /* Capture/compare 3 */
#define TAIV_CCIFG4         TAIV_8            /* Capture/compare 4 */


/************************************************************
* Interrupt Vectors (offset from 0xFF80)
************************************************************/


#define RTC_VECTOR              (42)                     /* 0xFFD2 RTC */
#define PORT2_VECTOR            (43)                     /* 0xFFD4 Port 2 */
#define TIMER2_A1_VECTOR        (44)                     /* 0xFFD6 Timer2_A5 CC1-4, TA */
#define TIMER2_A0_VECTOR        (45)                     /* 0xFFD8 Timer2_A5 CC0 */
#define USCI_B1_VECTOR          (46)                     /* 0xFFDA USCI B1 Receive/Transmit */
#define USCI_A1_VECTOR          (47)                     /* 0xFFDC USCI A1 Receive/Transmit */
#define PORT1_VECTOR            (48)                     /* 0xFFDE Port 1 */
#define TIMER1_A1_VECTOR        (49)                     /* 0xFFE0 Timer1_A3 CC1-2, TA1 */
#define TIMER1_A0_VECTOR        (50)                     /* 0xFFE2 Timer1_A3 CC0 */
#define DMA_VECTOR              (51)                     /* 0xFFE4 DMA */
#define USB_UBM_VECTOR          (52)                     /* 0xFFE6 USB Timer / cable event / USB reset */
#define TIMER0_A1_VECTOR        (53)                     /* 0xFFE8 Timer0_A5 CC1-4, TA */
#define TIMER0_A0_VECTOR        (54)                     /* 0xFFEA Timer0_A5 CC0 */
#define ADC12_VECTOR            (55)                     /* 0xFFEC ADC */
#define USCI_B0_VECTOR          (56)                     /* 0xFFEE USCI B0 Receive/Transmit */
#define USCI_A0_VECTOR          (57)                     /* 0xFFF0 USCI A0 Receive/Transmit */
#define WDT_VECTOR              (58)                     /* 0xFFF2 Watchdog Timer */
#define TIMER0_B1_VECTOR        (59)                     /* 0xFFF4 Timer0_B7 CC1-6, TB */
#define TIMER0_B0_VECTOR        (60)                     /* 0xFFF6 Timer0_B7 CC0 */
#define COMP_B_VECTOR           (61)                     /* 0xFFF8 Comparator B */
#define UNMI_VECTOR             (62)                     /* 0xFFFA User Non-maskable */
#define SYSNMI_VECTOR           (63)                     /* 0xFFFC System Non-maskable */
#define RESET_VECTOR            ("reset")                /* 0xFFFE Reset [Highest Priority] */

/************************************************************
* End of Modules
************************************************************/
#ifdef __cplusplus
}
#endif /* extern "C" */


#endif /* #ifndef __MSP430F5529LP */

