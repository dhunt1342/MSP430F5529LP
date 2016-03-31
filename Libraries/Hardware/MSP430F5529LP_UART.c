
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
 * FileName:      MSP430F5529LP_UART.c
 *
 * This file provides functions for the Universal Serial Communications
 * Interface (USCI) in the UART mode for the Texas Instruments MSP430F5529
 * Launchpad development board.
 *
 * Version 1.1
 *
 * Rev. 1.0, Initial Release
 * Rev. 1.1, Updated static variable debugging info
 *
 *                                                                            */
/* ===========================================================================*/

#include "MSP430F5529LP.h"
#include "MSP430F5529LP_UART.h"
#include "string.h"


/******************************************************************************
    PUBLIC DEFINITIONS
******************************************************************************/

   
/******************************************************************************
    PUBLIC VARIABLES
******************************************************************************/
  
 
/******************************************************************************
    PRIVATE DEFINITIONS (static const)
******************************************************************************/

    #define  MAX_UART_BUFFER_LEN   80


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

    static volatile uint8_t    s_UartRxMsgBuffer_u8[MAX_UART_BUFFER_LEN];
    static volatile uint16_t   s_UartRxWriteIndex_u16;
    static volatile uint16_t   s_UartRxReadIndex_u16;

    static volatile uint8_t    s_UartTxMsgBuffer_u8[MAX_UART_BUFFER_LEN];
    static volatile uint16_t   s_UartTxWriteIndex_u16;
    static volatile uint16_t   s_UartTxReadIndex_u16;


/******************************************************************************
   Subroutine:    MSP430F5529LP_UART_Initialize
   Description:
   Inputs:
   Outputs:

******************************************************************************/
void MSP430F5529LP_UART_Initialize(void)
{
    int x;

    UCA0CTL1_bits.UCSWRST = 1u;     // disable the UART

   //disable all UART interrupts, and clear the interrupt flags
   UCA0IE_bits.UCRXIE = 0u;
   UCA0IE_bits.UCTXIE = 0u;
   UCA0IFG_bits.UCRXIFG = 0u;
   UCA0IFG_bits.UCTXIFG = 0u;

   // clear the UART status flags
   UCA0STAT = 0u;

   // Configure the UART.
   UCA0CTL0_bits.UCSYNC = 0u;       // asynchronous serial mode
   UCA0CTL0_bits.UCMODEx = 0u;      // standard UART mode
   UCA0CTL0_bits.UCSPB = 0u;        // one stop bit
   UCA0CTL0_bits.UC7BIT = 0u;       // 8-bits of data
   UCA0CTL0_bits.UCMSB = 0u;        // LSB first
   UCA0CTL0_bits.UCPEN = 0u;        // parity disabled
   UCA0CTL1_bits.UCSSELx = 3u;      // UART clock = SMCLK
   UCA0CTL1_bits.UCRXEIE = 0u;      // ignore erroneous chars
   UCA0CTL1_bits.UCBRKIE = 0u;      // ignore break chars
   UCA0CTL1_bits.UCDORM = 0u;       // disable dormant mode
   UCA0CTL1_bits.UCTXADDR = 0u;     // next frame is not address
   UCA0CTL1_bits.UCTXBRK = 0u;      // next frame is not break

   UCA0MCTL_bits.UCOS16 = 1u;       // 16-bit oversampling enabled
   UCA0MCTL_bits.UCBRFx = 1u;       // first stage modulator value
   UCA0MCTL_bits.UCBRSx = 0u;       // second stage modulator value

   // Set the uart baud rate prescaler to 26 = 0x001A.
   UCA0BR1 = 0x00u;
   UCA0BR0 = 0x1Au;

   for (x=0; x<MAX_UART_BUFFER_LEN; x++)
   {
       s_UartRxMsgBuffer_u8[x] = 0u;
       s_UartTxMsgBuffer_u8[x] = 0u;
   }

   s_UartRxWriteIndex_u16 = 0u;
   s_UartRxReadIndex_u16 = 0u;

   s_UartTxWriteIndex_u16 = 0u;
   s_UartTxReadIndex_u16 = 0u;

   // Select the special function mapping for UCA0 UART Mode
   P3DIR_bits.P3DIR3 = 1u;          // set P3.3 (Tx) as Output
   P3OUT_bits.P3OUT3 = 1u;          // set P3.3 output high
   P3DIR_bits.P3DIR4 = 0u;          // set P3.4 (Rx) as Input
   P3SEL_bits.P3SEL3 = 1u;          // set P3.3 as UCA0TXD
   P3SEL_bits.P3SEL4 = 1u;          // set P3.4 as UCA0RXD


   UCA0CTL1_bits.UCSWRST = 0u;      // enable the UART

   // enable recieve interrupt - this must be done after UART enable!
   UCA0IE_bits.UCRXIE = 1u;
}


/******************************************************************************
   Subroutine:    BytesReady
   Description:
   Inputs:
   Outputs:

******************************************************************************/
uint8_t BytesReady(void)
{
   return (s_UartRxWriteIndex_u16 != s_UartRxReadIndex_u16);
}


/******************************************************************************
   Subroutine:    GetRxByte
   Description:
   Inputs:
   Outputs:

******************************************************************************/
uint8_t GetRxByte(void)
{
    static uint8_t retVal;

    // get the revieved byte from the RxBuffer, and increment read index
    retVal = s_UartRxMsgBuffer_u8[s_UartRxReadIndex_u16++];

    // rollover index if we have reached end of buffer
    if (MAX_UART_BUFFER_LEN <= s_UartRxReadIndex_u16)
    {
        s_UartRxReadIndex_u16 = 0u;
    }

    return retVal;
}


/******************************************************************************
   Subroutine:    PutTxByte
   Description:
   Inputs:
   Outputs:

******************************************************************************/
void PutTxByte(uint8_t byte)
{
    // put the byte to transmit into the TxBuffer, and increment write index
    s_UartTxMsgBuffer_u8[s_UartTxWriteIndex_u16++] = byte;

    // rollover index if we have reached end of buffer
    if (MAX_UART_BUFFER_LEN <= s_UartTxWriteIndex_u16)
    {
        s_UartTxWriteIndex_u16 = 0u;
    }

    // enable the UART transmit interrupt
    UCA0IE_bits.UCTXIE = 1u;
}


/******************************************************************************
   Subroutine:    SendSerialMsg
   Description:
   Inputs:
   Outputs:

******************************************************************************/
void SendSerialMsg(char* pMsg, int size)
{
    int x;

    // if there is currently a message in the UART Tx Message Buffer that is
    // being processed, wait for that to complete first.
    while (s_UartTxWriteIndex_u16 != s_UartTxReadIndex_u16) {}

    for (x=0; x<size; x++)
    {
        PutTxByte(pMsg[x]);
    }
}


/******************************************************************************
   Subroutine:    function_name
   Description:
   Inputs:
   Outputs:

******************************************************************************/
void __attribute__((__interrupt__(USCI_A0_VECTOR))) USCI_A0_ISR(void)
{
    static uint8_t UCA0IV_value;

    UCA0IV_value = UCA0IV;

    // if a UART byte has been received...
    if (2u == UCA0IV_value)
    {
        // put the received byte into the Rx buffer
        s_UartRxMsgBuffer_u8[s_UartRxWriteIndex_u16++] = UCA0RXBUF;

        // rollover index if we have reached end of buffer
        if (MAX_UART_BUFFER_LEN <= s_UartRxWriteIndex_u16)
        {
            s_UartRxWriteIndex_u16 = 0u;
        }
    }

    // if a UART byte is ready to be transmitted
    if (4u == UCA0IV_value)
    {
        // put the next byte to send into the Tx buffer
        UCA0TXBUF = s_UartTxMsgBuffer_u8[s_UartTxReadIndex_u16++];

        // rollover index if we have reached end of buffer
        if (MAX_UART_BUFFER_LEN <= s_UartTxReadIndex_u16)
        {
            s_UartTxReadIndex_u16 = 0u;
        }

        // If there are no more bytes to process
        if (s_UartTxWriteIndex_u16 == s_UartTxReadIndex_u16)
        {
            // disable the UART transmit interrupt
            UCA0IE_bits.UCTXIE = 0u;
        }
    }
}

/******************************************************************************
     End of File: MSP430F5529LP_UART.c
******************************************************************************/
