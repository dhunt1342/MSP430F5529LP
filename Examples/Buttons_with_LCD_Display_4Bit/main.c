
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

    // These are logical descriptions of the button service index values.
    #define BUTTON1     0
    #define BUTTON2     1


/******************************************************************************
   PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/

    static void initialize(void);

    static void Button1_Callback(void);

    static void Button2_Callback(void);

    static void Update_LCD_Display(void);


/******************************************************************************
   PRIVATE VARIABLES (static)
******************************************************************************/

    static uint16_t s_single_press;
    static uint16_t s_double_click;
    static uint16_t s_long_press;

    static uint16_t s_LcdUpdateFlag;


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
        if (s_LcdUpdateFlag)
        {
            Update_LCD_Display();
            s_LcdUpdateFlag = 0u;
        }
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
        MSP430F5529LP_BUTTONS_Initialize(8, 3, 100, 500);

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

        s_single_press = 0u;
        s_double_click = 0u;
        s_long_press = 0u;
        s_LcdUpdateFlag = 0u;

        // Register the buttons
        Set_Button_Callback(BUTTON1, MSP430F5529LP_BUTTON1, 0, Button1_Callback);
        Set_Button_Callback(BUTTON2, MSP430F5529LP_BUTTON2, 0, Button2_Callback);

        Update_LCD_Display();


        // ###################################################################
        // Last step before exiting, enable global interrupts

        __enable_interrupt();
}


/******************************************************************************
    Subroutine:     Button1_Callback
    Description:    This is the callBack function that will be called when
                    button1 generates an event.
    Inputs:         None
    Outputs:        None

******************************************************************************/
static void Button1_Callback(void)
{
    static ButtonEvents_t b1_status;

    b1_status = Get_Button_Status(BUTTON1);

    if (b1_status.single_press)
    {
        s_single_press++;
    }

    if (b1_status.double_click)
    {
        s_double_click++;
    }

    if (b1_status.long_press)
    {
        s_long_press++;
    }

    Clear_Button_Status(BUTTON1);
    s_LcdUpdateFlag = 1u;
}


/******************************************************************************
    Subroutine:     Button2_Callback
    Description:    This is the callBack function that will be called when
                    button2 generates an event.
    Inputs:         None
    Outputs:        None

******************************************************************************/
static void Button2_Callback(void)
{
    static ButtonEvents_t b2_status;

    b2_status = Get_Button_Status(BUTTON2);

    if (b2_status.single_press)
    {
        s_single_press++;
    }

    if (b2_status.double_click)
    {
        s_double_click++;
    }

    if (b2_status.long_press)
    {
        s_long_press++;
    }

    Clear_Button_Status(BUTTON2);
    s_LcdUpdateFlag = 1u;
}


/******************************************************************************
    Subroutine:     Update_LCD_Display
    Description:    This function is called by the main loop whenever
                    s_LcdUpdateFlag is set.
    Inputs:         None
    Outputs:        None

******************************************************************************/
static void Update_LCD_Display(void)
{
    LCD_SetPosition(LCD_ROW1);
    LCD_Print("Button LCD Example");
    LCD_SetPosition(LCD_ROW2);
    LCD_Print("single_press:  %5u", s_single_press);
    LCD_SetPosition(LCD_ROW3);
    LCD_Print("double_click:  %5u", s_double_click);
    LCD_SetPosition(LCD_ROW4);
    LCD_Print("long_press:    %5u", s_long_press);
}



/******************************************************************************
   End of File: main.c
******************************************************************************/
