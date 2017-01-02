
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
 * This program writes to a 20x4 LCD display based on the HD44780 display
 * controller using the 4-bit parallel addressing mode. The example uses an
 * interval timer to display an up-counter in decimal, hexadecimal and binary
 * formats. This example can also be used to explore the refresh rates of the
 * LCD. To fast, and the display becomes unreadable. A note of caution, the
 * refresh rate of the LCD is highly dependent on temperature.
 *
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
 *
 *                                                                            */
/* ===========================================================================*/

#include "MSP430F5529LP.h"
#include "MSP430F5529LP_CLOCK.h"
#include "MSP430F5529LP_TIMERA2.h"
#include "MSP430F5529LP_GPIO.h"

#include "LCD_HD44780_4BIT.h"


/******************************************************************************
   PUBLIC DEFINITIONS
******************************************************************************/


/******************************************************************************
   PUBLIC VARIABLES
******************************************************************************/


/******************************************************************************
   PRIVATE DEFINITIONS (static const)
******************************************************************************/

    #define BYTETOBINARYPATTERN    "%d%d%d%d%d%d%d%d"

    #define BYTETOBINARY(byte) \
      (byte & 0x80 ? 1 : 0), \
      (byte & 0x40 ? 1 : 0), \
      (byte & 0x20 ? 1 : 0), \
      (byte & 0x10 ? 1 : 0), \
      (byte & 0x08 ? 1 : 0), \
      (byte & 0x04 ? 1 : 0), \
      (byte & 0x02 ? 1 : 0), \
      (byte & 0x01 ? 1 : 0)


/******************************************************************************
   PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/

    static void initialize(void);

    static void Update_LCD_Display(void);


/******************************************************************************
   PRIVATE VARIABLES (static)
******************************************************************************/

    static uint8_t         s_count_u8;


/******************************************************************************
    Subroutine:     main
    Description:    program entry point at startup.
    Inputs:         None
    Outputs:        0

******************************************************************************/
int main( void )
{
    // perform initialization
    initialize();

    for (;;)    // Loop forever...
    {
        delay(250);             // perform a blocking delay of 250 ms
        s_count_u8++;           // increment the counter
        Update_LCD_Display();   // Update the LCD display
    }

    return 0;
}


/******************************************************************************
    Subroutine:     initialize
    Description:    Performs the initalization of the main program. This also
                    initializes the MSP430F5529LP operating environment.
    Inputs:         None
    Outputs:        None

******************************************************************************/
void initialize(void)
{
    // ###################################################################
        // Add operating environment initialization here

        MSP430F5529LP_CLOCK_Initialize();
        MSP430F5529LP_TIMERA2_Initialize();

        /* Initialize the 20x4 LCD display
         * LcdPin_RS =  57;  // P7.4
         * LcdPin_RW =  35;  // P2.6
         * LcdPin_EN =  16;  // P8.1
         * LcdPin_D4 =  44;  // P3.7
         * LcdPin_D5 =  17;  // P8.2
         * LcdPin_D6 =  27;  // P1.6
         * LcdPin_D7 =  36;  // P2.7
         */
        LCD_Initialize(57, 35, 16, 44, 17, 27, 36);


        // ###################################################################
        // Add program specific initialization here

        // Enable the Debug LEDs
        P1DIR_bits.P1DIR0 = 1;         // Set P1.0 (LED1) to an Output
        P4DIR_bits.P4DIR7 = 1;         // Set P4.7 (LED2) to an Output
        P1OUT_bits.P1OUT0 = 1;         // Set P1.0 initial value
        P4OUT_bits.P4OUT7 = 1;         // Set P4.7 initial value

        s_count_u8 = 0u;

        Update_LCD_Display();


        // ###################################################################
        // Last step before exiting, enable global interrupts

        __enable_interrupt();
}


/******************************************************************************
    Subroutine:     Update_LCD_Display
    Description:    This function updates the LCD display values.
    Inputs:         None
    Outputs:        None

******************************************************************************/
static void Update_LCD_Display(void)
{
    /* In addition to updating the LCD, set and clear the P1.0 LED during LCD
     * processing. This gives an indication of how long it takes to update
     * the LCD display. It is important to keep in mind that the LCD will
     * "block" during update, and this can affect application performance.
     * Interrupts are not disabled during LCD updates, but the application's
     * ability to keep up with processing between interrupts could be. Note
     * that the P1.0 LED signal is also available at jumper JP8.
     */

    P1OUT_bits.P1OUT0 = 1;

    LCD_SetPosition(LCD_ROW1);
    LCD_Print("LCD (4bit) Example  ");
    LCD_SetPosition(LCD_ROW2);
    LCD_Print("Decimal:         %3d", s_count_u8);
    LCD_SetPosition(LCD_ROW3);
    LCD_Print("Hexadecimal:     %3X", s_count_u8);
    LCD_SetPosition(LCD_ROW4);
    LCD_Print("Binary:     "BYTETOBINARYPATTERN, BYTETOBINARY(s_count_u8));

    P1OUT_bits.P1OUT0 = 0;
}



/******************************************************************************
   End of File: main.c
******************************************************************************/
