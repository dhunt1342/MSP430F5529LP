
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
 * FileName:      MSP430F5529LP_I2C.c
 *
 * This file provides functions for the Universal Serial Communications
 * Interface (UCB1) in the I2C Master mode for the Texas Instruments
 * MSP430F5529 Launchpad development board.
 *
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
 *
 *                                                                            */
/* ===========================================================================*/

#include "MSP430F5529LP.h"
#include "MSP430F5529LP_CLOCK.h"
#include "MSP430F5529LP_I2C.h"
#include "MSP430F5529LP_TIMER_A2.h"


/******************************************************************************
   PUBLIC DEFINITIONS
******************************************************************************/

   
/******************************************************************************
   PUBLIC VARIABLES
******************************************************************************/
  
 
/******************************************************************************
   PRIVATE DEFINITIONS (static const)
******************************************************************************/
   
    #define I2C_DELAY_10us      __delay_cycles((10e-6)/(1.0/CLOCK_FREQ))

   
/******************************************************************************
   PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/

    static void I2C_Recovery(void);

    static void I2cIsr1Rx(void);
   
    static void I2cIsr1Tx(void);

    static void I2cIsr1Stat(void);

    static void I2cIsr1Unhandled(void);
   
   
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


    STATIC  uint8_t     *pRxData;
    STATIC  uint8_t     *pTxData;

    STATIC  I2C_CmplCode_t  done;

    STATIC  uint16_t    I2cStart;

    STATIC  uint16_t    s_I2cErrorCnt;
    STATIC  uint16_t    s_I2cErrNackCnt;
    STATIC  uint16_t    s_I2cErrArbLossCnt;
    STATIC  uint16_t    s_I2cErrUnhandledCnt;
  
   
/******************************************************************************
   Subroutine:    function_name
   Description:   
   Inputs:
   Outputs:

******************************************************************************/
void MSP430F5529LP_I2C_Initialize(void)
{
    __disable_interrupt();

    s_I2cErrorCnt = 0;
    s_I2cErrNackCnt = 0;
    s_I2cErrArbLossCnt = 0;
    s_I2cErrUnhandledCnt = 0;

    // Reset both control registers to default values (just in case)
    UCB1CTL0 = 1u;
    UCB1CTL1 = 1u;

    UCB1CTL1_bits.UCSWRST  = 1u;      // Disable I2C (in reset)

    // Configure I2C mode
    UCB1CTL0_bits.UCMODEx = 3u;      // Select I2C mode
    UCB1CTL0_bits.UCSYNC = 1u;       // Synchronous mode
    UCB1CTL0_bits.UCMST = 1u;        // Select Master Mode
    UCB1CTL1_bits.UCSSELx = 3u;      // Select SMCLK Source
    UCB1CTL0_bits.UCSLA10 = 0u;      // 7-bit slave addressing mode

    // Set I2C clock speed to 50KHz = 24MHz/480
    // Prescaler is determined by (UCxxBR0 + (UCxxBR1 × 256))
    UCB1BR1 = 1u;
    UCB1BR0 = 224u;

    // Select the special function mapping for UCB1 I2C Mode
    P4DIR_bits.P4DIR1 = 0;      // set P4.1 as Input
    P4SEL_bits.P4SEL1 = 1;      // select P4.1 as (I2C) SDA
    P4DIR_bits.P4DIR2 = 1;      // set P4.2 as Input
    P4SEL_bits.P4SEL2 = 1;      // select P4.2 as (I2C) SCL

    // Many I2C boards do not come with pullup resistors, and the launchpad
    // board also has no resistors. This typcally makes most I2C projects
    // frustratingly non-functional. To ensure at least basic functionality
    // enable the internal MSP430 pullup resistors. These resistors have very
    // high values of 20K to 50K, so speed must be limited until either
    // resistors are added to the design, or are confimed to exist elsewhere.
    // Assuming 50K and 20pF, Tau = 1us. At 10us, where rising edge will take
    // 10% of the pulse width to be stable, max speed is limited to no more
    // than 100KHz. Max speed for the MSP430 is 400 KHz.

    P4REN_bits.P4REN1 = 1;      // enable the P4.1 resistor
    P4OUT_bits.P4OUT1 = 1;      // set P4.1 resistor as pullup.
    P4REN_bits.P4REN2 = 1;      // enable P4.2 resistor
    P4OUT_bits.P4OUT2 = 1;      // set P4.2 resistor as pullup

    // Just in case, start with a bus recovery. The I2C bus can frequently
    // become locked up. This is particularly true while using the debugger.
    // If I2C is interrupted while a device is driving a 0 on the bus, that
    // device can continue to hold SDA low, which will create a permanent
    // arbitration loss condition. Note that the MSP430 can sometimes be the
    // device holding the bus, and can deadlock itself.
    I2C_Recovery();

    // The bus may have been released above because the slave transitioned to
    // sending a 1, but may not have completed the transaction. Set the STOP
    // bit to send a STOP condition. This will force the slave to abort.
    UCB1CTL1_bits.UCTXSTP = 1u;

    UCB1CTL1_bits.UCSWRST  = 0u;      // Enable I2C (not reset)

   __enable_interrupt();
}


/******************************************************************************
   Subroutine:    function_name
   Description:   
   Inputs:
   Outputs:

******************************************************************************/
void I2C_Read(uint8_t address, uint8_t *p_reg)
{
    while( (UCB1STAT_bits.UCBBUSY) &&
           (UCB1CTL1_bits.UCTXSTP) ) {};

    if (1u == UCB1STAT_bits.UCBBUSY)
    {
        I2C_Recovery();
    }
  
   UCB1I2CSA_bits.I2CSAx = address;
   pRxData = p_reg;
   
   UCB1CTL1_bits.UCTR = 0u;         // set as receiver
   UCB1CTL1_bits.UCTXSTT = 1u;      // set start bit
   UCB1IE_bits.UCRXIE = 1u;         // enable Rx interrupt

   done = I2C_IN_PROGRESS;
   I2cStart = GetTick();
   
   while ( (done == I2C_IN_PROGRESS) &&
           (35 > Elapse(I2cStart, GetTick())) ) {}

   if (I2C_COMPLETED_SUCCESS != done)
   {
       I2C_Recovery();
   }

   return;
}


/******************************************************************************
   Subroutine:    function_name
   Description:   
   Inputs:
   Outputs:

******************************************************************************/
void I2C_Write(uint8_t address, uint8_t * p_reg)
{
    // It is possible to complete the final ISR transaction, and queue up a new
    // i2c transaction while the last one is being completed. This is typically
    // due to the i2c module writing out the stop condition to the bus.
    while( (UCB1STAT_bits.UCBBUSY) &&
           (UCB1CTL1_bits.UCTXSTP) ) {};
   
    // If our last transaction is complete, but the bus is still busy,
    // something is very wrong. Attempt to recover the bus before continuing.
    if (1u == UCB1STAT_bits.UCBBUSY)
    {
        I2C_Recovery();
    }
     
    UCB1I2CSA_bits.I2CSAx = address;
    pTxData = p_reg;

    UCB1CTL1_bits.UCTR = 1u;        // set as transmitter
    UCB1CTL1_bits.UCTXSTT = 1u;     // set start bit
    UCB1IE_bits.UCTXIE = 1u;        // enable Tx interrupt
   
    done = I2C_IN_PROGRESS;
    I2cStart = GetTick();

    while ( (done == I2C_IN_PROGRESS) &&
            (35 > Elapse(I2cStart, GetTick())) ) {}

    return;
}


/******************************************************************************
   Subroutine:    function_name
   Description:
   Inputs:
   Outputs:

******************************************************************************/
static void I2C_Recovery(void)
{
    uint8_t  RstCnt;

    __disable_interrupt();

    UCB1CTL1_bits.UCSWRST  = 1u;      // Disable I2C (in reset)

    P4SEL_bits.P4SEL1 = 0;      // set I2C SDA to GPIO control
    P4DIR_bits.P4DIR1 = 0;      // set I2C SDA GPIO as Input
    P4REN_bits.P4REN1 = 1;      // enable I2C SDA Resistor
    P4DIR_bits.P4DIR1 = 1;      // set resistor as pullup

    P4SEL_bits.P4SEL2 = 0;      // set I2C CLK to GPIO control
    P4DIR_bits.P4DIR2 = 1;      // set I2C CLK GPIO as Output

    // for up to 9 bits, toggle the I2C clock to force any peripherals
    // to complete any transactions and release the bus.
    for(RstCnt = 0u; RstCnt < 9u; RstCnt++)
    {
        P4OUT_bits.P4OUT2 = 0;      // set I2C CLK = 0
        I2C_DELAY_10us;             // pw = 10us, f = 50KHz
        P4OUT_bits.P4OUT2 = 1;      // set I2C CLK = 0
        I2C_DELAY_10us;             // pw = 10us, f = 50KHz

        // If the I2C SDA line is released, quit sending clock pulses
        if (1u == P4IN_bits.P4IN1)
        {
            break;
        }
    }

    P4DIR_bits.P4DIR2 = 0;      // set I2C SCL GPIO as Input
    P4REN_bits.P4REN2 = 1;      // enable I2C SCL Resistor
    P4DIR_bits.P4DIR2 = 1;      // set resistor as pullup

    P4SEL_bits.P4SEL1 = 1;      // set SDA under I2C control
    P4SEL_bits.P4SEL2 = 1;      // set CLK under I2C control

    UCB1CTL1_bits.UCSWRST  = 0u;      // Enable I2C (not reset)

    __enable_interrupt();
}


/******************************************************************************
   Subroutine:    USCIB0_I2C_TxRx_ISR
   Description:   
   Inputs:
   Outputs:

******************************************************************************/
void __attribute__((__interrupt__(USCI_B1_VECTOR))) USCIB1_I2C_ISR(void)
{ 
    static uint16_t UCB1IVector;

    UCB1IVector = UCB1IV;

    switch (UCB1IVector)
    {
        case (UCBxIV_I2C_UCRXIFG):
        {
            I2cIsr1Rx();
            break;
        }
        case (UCBxIV_I2C_UCTXIFG):
        {
            I2cIsr1Tx();
            break;
        }
        case (UCBxIV_I2C_ARBLOSS):
        case (UCBxIV_I2C_NACK):
        {
            I2cIsr1Stat();
            break;
        }
        default:
        {
            I2cIsr1Unhandled();
        }
    }
}


/******************************************************************************
   Subroutine:    I2cIsr0Rx
   Description:   This ISR configures the MSP430 I2C USCI module to RX & TX
   SMBus commands & data in both Master and Slave configurations. 

******************************************************************************/
static void I2cIsr1Rx(void)
{  
    static uint8_t rxData;

    UCB1CTL1_bits.UCTXSTP = 1u;      // set stop bit

    // Always pull the RX data and clear the interrupt flag
    UCB1IFG_bits.UCRXIFG = 0u;
    rxData = UCB1RXBUF;

    *pRxData = rxData;
    done = I2C_COMPLETED_SUCCESS;
}


/******************************************************************************
   Subroutine:    I2cIsr0Rx
   Description:   This ISR configures the MSP430 I2C USCI module to RX & TX
   SMBus commands & data in both Master and Slave configurations. 

******************************************************************************/
static void I2cIsr1Tx(void)
{  
    // if the start bit is set, the slave has not yet acknowledged the
    // address, and the I2C is waiting for data to be written to UCB1TXBUF.
    if (1u == UCB1CTL1_bits.UCTXSTT)
    {
        UCB1TXBUF = *pTxData;
    }
    // else, we have transmitted the data from the Tx buffer and the I2CB0 Tx
    // buffer is now empty (hence the Isr call). Disable the Tx interrupt, and
    // set the request to send a STOP bit.
    else
    {
        UCB1CTL1_bits.UCTXSTP = 1u;
        UCB1IE_bits.UCTXIE = 0u;
        done = I2C_COMPLETED_SUCCESS;
    }
}


/******************************************************************************
   Subroutine:    I2cIsr1Stat
   Description:

******************************************************************************/
static void I2cIsr1Stat(void)
{
    // If the Arbitration Lost flag is set...
    if ( 1u == UCB1IFG_bits.UCALIFG )
    {
        // Then another master has control of the bus, or more likely, noise
        // on the I2C bus has been interpreted as another master on the bus.
        // As a result the MSP430 will have automatically switched the I2C
        // mode to receiver.

        UCB1IFG_bits.UCALIFG = 0u;      /* Clear the arb lost flag */

        /* Clear Start and stop bits in case they are still set. */
        UCB1CTL1_bits.UCTXSTT = 0u;
        UCB1CTL1_bits.UCTXSTP = 0u;

        UCB1CTL0_bits.UCMST = 1u;        // Select Master Mode again

        s_I2cErrArbLossCnt++;
        s_I2cErrorCnt++;

        done = I2C_ARBITRATION_LOST;
    }

    // If the NACK Flag is set...
    if ( 1u == UCB1IFG_bits.UCNACKIFG )
    {
        // Then the I2C device did not respond to the communication attempt,
        // setup the conditions to send a STOP bit in response to the NACK.

        UCB1IFG_bits.UCNACKIFG = 0u;    /* Clear the NACK flag */

        UCB1CTL1_bits.UCTXSTP = 0u;     /* Set STOP bit request */

        s_I2cErrNackCnt++;
        s_I2cErrorCnt++;

        done = I2C_NACK_RESPONSE;
  }
}


/******************************************************************************
   Subroutine:    I2cIsr1Unhandled
   Description:

******************************************************************************/
static void I2cIsr1Unhandled(void)
{
    // If we get an ISR vector that is unhandled, let's trap it, so we know
    // to look for the root cause.
    s_I2cErrUnhandledCnt++;
    s_I2cErrorCnt++;

}

/******************************************************************************
	End of File: MSP430F5529LP_I2C.c
******************************************************************************/
