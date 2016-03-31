
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
 * FileName:      MSP430F5529LP_BUTTONS.c
 *
 * Description
 *
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
 *
 *                                                                            */
/* ===========================================================================*/

#include "MSP430F5529LP.h"
#include "MSP430F5529LP_BUTTONS.h"
#include "MSP430F5529LP_TIMERA2.h"


/******************************************************************************
    PUBLIC DEFINITIONS
******************************************************************************/


/******************************************************************************
    PUBLIC VARIABLES
******************************************************************************/
  
    volatile ButtonEvents_t   Button1Events;
 

/******************************************************************************
    PRIVATE DEFINITIONS (static const)
******************************************************************************/

    typedef enum
    {
        UP1_ENTRY,
        UP1_MAIN,
        DN1_ENTRY,
        DN1_MAIN,
        UP2_ENTRY,
        UP2_MAIN,
        DN2_ENTRY,
        DN2_MAIN
    } Button_State_t;

    #define BUTTON1     P2IN_bits.P2IN1
    #define BUTTON2     P1IN_bits.P1IN1

    #define BUTTON_DBNC_THRESHOLD       4       // 64 ms
    #define BUTTON_DBL_CLICK_TIMEOUT    250     // 250 ms
    #define BUTTON_LNG_PRESS_TIMEOUT    1000    // 1000 ms


/******************************************************************************
    PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/

    static void Button_Service(void);

    static void Button1_Service(void);



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

    static Button_State_t   s_Button1State;
    static uint16_t         s_Button1Start;
    static uint16_t         s_Button1Dbnc;
    static uint16_t         s_Button1LongPressed;

    static BUTTON_Callback_t    Button_Callback;


/******************************************************************************
    Subroutine:     function_name
    Description:   
    Inputs:
    Outputs:

******************************************************************************/
void MSP430F5529LP_BUTTONS_Initialize(void)
{
    P2DIR_bits.P2DIR1 = 0u;
    P2REN_bits.P2REN1 = 1u;
    P2OUT_bits.P2OUT1 = 1u;

    P1DIR_bits.P1DIR1 = 0u;
    P1REN_bits.P1REN1 = 1u;
    P1OUT_bits.P1OUT1 = 1u;

    extern void Set_Button_Service(void *callback);
    Set_Button_Service(Button_Service);

    MSP430F5529LP_TIMERA2_Initialize();
}


/******************************************************************************
    Subroutine:     Set_Button_Service
    Description:    Use this function to create a watchdog timer, and register
                    the callback function to be executed when it expires.
    Inputs:         Index: The index of the WDT_timers[] array to place the
                    new WDT timer being registered. Valid values are from
                    zero to MAX_WDT_TIMERS-1.
                    timeout: The timeout value of the new timer in seconds.
                    For example, a value of 10, will expire after 10 seconds.
                    callback: The name of the function that will be called
                    when the registered timer expires.
    Outputs:        None

******************************************************************************/
void Set_BUTTON_Callback(void *callback)
{
    Button_Callback = (BUTTON_Callback_t) callback;
}


/******************************************************************************
    Subroutine:     function_name
    Description:
    Inputs:
    Outputs:

******************************************************************************/
static void Button_Service(void)
{
    Button1_Service();
}

/******************************************************************************
    Subroutine:     function_name
    Description:
    Inputs:
    Outputs:

******************************************************************************/
static void Button1_Service(void)
{
    switch(s_Button1State)
    {
        case(UP1_ENTRY):
        {
            s_Button1Dbnc = 0;
            s_Button1State = UP1_MAIN;
        }
        break;

        case(UP1_MAIN):
        {
            // If the button is pressed...
            if (0 == BUTTON1)
            {
                s_Button1Dbnc += 1u;    // accumulate debounce samples
            }
            // If the button is unpressed...
            else
            {
                s_Button1Dbnc = 0u;     // reset the debounce value
            }

            // if there are N consecutive measurements...
            if (BUTTON_DBNC_THRESHOLD <= s_Button1Dbnc)
            {
                s_Button1State = DN1_ENTRY;
            }
        }
        break;

        case(DN1_ENTRY):
        {
            s_Button1Start = GetTick();
            s_Button1Dbnc = 0u;
            s_Button1LongPressed = 0u;
            s_Button1State = DN1_MAIN;
        }
        break;

        case(DN1_MAIN):
        {
            if (!s_Button1LongPressed)
            {
                if (BUTTON_LNG_PRESS_TIMEOUT <= Elapse(s_Button1Start, GetTick()))
                {
                    s_Button1LongPressed = 1u;
                    Button1Events.long_press = 1u;
                    if (NULL != Button_Callback) {Button_Callback();}
                }
            }

            // If the button is unpressed...
            if (1 == BUTTON1)
            {
                s_Button1Dbnc += 1u;    // accumulate debounce samples
            }
            // If the button is pressed...
            else
            {
                s_Button1Dbnc = 0u;     // reset the debounce value
            }

            // if there are N consecutive measurements...
            if (BUTTON_DBNC_THRESHOLD <= s_Button1Dbnc)
            {
                if (!s_Button1LongPressed)
                {
                    if (BUTTON_DBL_CLICK_TIMEOUT <= Elapse(s_Button1Start, GetTick()))
                    {
                        Button1Events.single_press = 1u;
                        if (NULL != Button_Callback) {Button_Callback();}
                        s_Button1State = UP1_ENTRY;
                    }
                    else
                    {
                        s_Button1State = UP2_ENTRY;
                    }
                }
                else
                {
                    s_Button1State = UP1_ENTRY;
                }
            }
        }
        break;

        case(UP2_ENTRY):
        {
            s_Button1Start = GetTick();
            s_Button1Dbnc = 0u;
            s_Button1State = UP2_MAIN;
        }
        break;

        case(UP2_MAIN):
        {
            if (BUTTON_DBL_CLICK_TIMEOUT <= Elapse(s_Button1Start, GetTick()))
            {
                Button1Events.single_press = 1u;
                if (NULL != Button_Callback) {Button_Callback();}
                s_Button1State = UP1_ENTRY;
            }

            // If the button is pressed...
            if (0 == BUTTON1)
            {
                s_Button1Dbnc += 1u;    // accumulate debounce samples
            }
            // If the button is unpressed...
            else
            {
                s_Button1Dbnc = 0u;     // reset the debounce value
            }

            // if there are N consecutive measurements...
            if (BUTTON_DBNC_THRESHOLD <= s_Button1Dbnc)
            {
                s_Button1State = DN2_ENTRY;
            }
        }
        break;


        case(DN2_ENTRY):
        {
            s_Button1Start = GetTick();
            s_Button1Dbnc = 0u;
            s_Button1State = DN2_MAIN;
        }
        break;

        case(DN2_MAIN):
        {
            // If the button is unpressed...
            if (1 == BUTTON1)
            {
                s_Button1Dbnc += 1u;    // accumulate debounce samples
            }
            // If the button is unpressed...
            else
            {
                s_Button1Dbnc = 0u;     // reset the debounce value
            }

            // if there are N consecutive measurements...
            if (BUTTON_DBNC_THRESHOLD <= s_Button1Dbnc)
            {
                Button1Events.double_click = 1u;
                if (NULL != Button_Callback) {Button_Callback();}
                s_Button1State = UP1_ENTRY;
            }
        }
        break;

        default:
        {
            s_Button1State = UP1_ENTRY;
        }
        break;
    }
}


/******************************************************************************
    End of File: MSP430F5529LP_BUTTONS.c
******************************************************************************/
