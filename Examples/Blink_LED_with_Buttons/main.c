
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
 * This program toggles the LEDs on the Texas Instruments MSP430F5529 Launchpad
 * development board using the Button hardware library. This is a very basic
 * demonstration for registering a button with the button service, and toggling
 * the LED when the callback indicates that a button event has occurred.
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
#include "MSP430F5529LP_BUTTONS.h"


/******************************************************************************
   PUBLIC DEFINITIONS
******************************************************************************/


/******************************************************************************
   PUBLIC VARIABLES
******************************************************************************/


/******************************************************************************
   PRIVATE DEFINITIONS (static const)
******************************************************************************/

    // These are logical descriptions of the button service index values.
    #define BUTTON1     0
    #define BUTTON2     1


/******************************************************************************
   PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/

    static void initialize(void);

    static void Button_Callback(void);


/******************************************************************************
   PRIVATE VARIABLES (static)
******************************************************************************/


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
        // Do nothing
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
static void initialize(void)
{
    // ###################################################################
    // Add operating environment initialization here

    MSP430F5529LP_CLOCK_Initialize();
    MSP430F5529LP_TIMERA2_Initialize();
    MSP430F5529LP_BUTTONS_Initialize(8, 3, 100, 500);


    // ###################################################################
    // Add program specific initialization here

    // Enable the Debug LEDs
    P1DIR_bits.P1DIR0 = 1;         // Set P1.0 (LED1) to an Output
    P4DIR_bits.P4DIR7 = 1;         // Set P4.7 (LED2) to an Output
    P1OUT_bits.P1OUT0 = 0;         // Set P1.0 initial value
    P4OUT_bits.P4OUT7 = 1;         // Set P4.7 initial value

    // Register the buttons
    Set_Button_Callback(BUTTON1, MSP430F5529LP_BUTTON1, 0, Button_Callback);
    Set_Button_Callback(BUTTON2, MSP430F5529LP_BUTTON2, 0, Button_Callback);


    // ###################################################################
    // Last step before exiting, enable global interrupts

    __enable_interrupt();
}


/******************************************************************************
    Subroutine:     Button_Callback
    Description:    This is the callBack function that will be called when
                    either button generates an event.
    Inputs:         None
    Outputs:        None

******************************************************************************/
static void Button_Callback(void)
{
    static ButtonEvents_t button_status;


    button_status = Get_Button_Status(BUTTON1);

    if (button_status.reg)
    {
        P1OUT_bits.P1OUT0 ^= 1;     // toggle P1.0 (LED1)
    }

    Clear_Button_Status(BUTTON1);


    button_status = Get_Button_Status(BUTTON2);

    if (button_status.reg)
    {
        P4OUT_bits.P4OUT7 ^= 1;     // toggle P4.7 (LED2)
    }

    Clear_Button_Status(BUTTON2);

    return;
}


/******************************************************************************
   End of File: main.c
******************************************************************************/
