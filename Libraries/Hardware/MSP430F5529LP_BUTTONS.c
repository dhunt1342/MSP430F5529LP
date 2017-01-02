
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
#include "MSP430F5529LP_TIMERA2.h"
#include "MSP430F5529LP_GPIO.h"
#include "MSP430F5529LP_BUTTONS.h"


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

    /*  This defines the maximum number of buttons (or signals) that can be
     * registered at the same time. This value can be increased to accommodate
     * more buttons as needed, however this will affect the amount of
     * processing that occurs within the interrupt context of the TIMERA2
     * ISR at the button service interval.
     */
    #define MAX_BUTTONS  10


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
    } ButtonState_t;

    typedef struct
    {
        uint16_t            pin;
        pinLevel_enum       polarity;
        ButtonCallback_t    callback;
        ButtonState_t       state;
        ButtonEvents_t      status;
        uint16_t            start;
        uint16_t            debounce;
        uint16_t            longpressed;
    } Button_Callback_t;


/******************************************************************************
    PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/

    void Button_Service_Callback(void);

    static void Button_State_Machine(uint16_t x);


    // This function prototype is needed to expose a function in the TIMERA2
    // library that is only called by the BUTTON library. This prototype is
    // not in the TIMERA2 header file.

    extern void Set_Button_Service(uint16_t intvl_ms,
                                   TIMERA2_ButtonService_t callback);


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

    static volatile Button_Callback_t  Buttons[MAX_BUTTONS];

    static uint16_t s_ButtonSrvcInterval_ms;
    static uint16_t s_ButtonDbncThresh_cnt;
    static uint16_t s_ButtonDblClickTimeout_ms;
    static uint16_t s_ButtonLngPressTimeout_ms;


/******************************************************************************
    Subroutine:     MSP430F5529LP_BUTTONS_Initialize
    Description:    This function initializes the button service framework
    Inputs:         uint16_t  ButtonSrvcInterval_ms: This value defines how
                    often the TIMERA2 library will call the
                    Button_Service_Callback.
                    uint16_t  ButtonDbncThresh_cnt: This value defines how many
                    times the button service must see a valid new button state
                    before considering it "debounced". The debounce time equals
                    the srvc interval x dbnc count (i.e. 8 ms x 3 = 24 ms)
                    uint16_t  ButtonDblClickTimeout_ms: This value defines the
                    time that a press/unpress event must occur within to be
                    considered as a double-click event.
                    uint16_t  ButtonLngPressTimeout_ms: This value defines how
                    long a button press must be held to be considered a
                    long-press event.
    Outputs:        None

******************************************************************************/
void MSP430F5529LP_BUTTONS_Initialize(uint16_t  ButtonSrvcInterval_ms,
                                      uint16_t  ButtonDbncThresh_cnt,
                                      uint16_t  ButtonDblClickTimeout_ms,
                                      uint16_t  ButtonLngPressTimeout_ms)
{
    uint16_t    x;

    /* There are two buttons provided on the MSP430F5529LP launchpad boards:
     * BUTTON1 is connected to Pin P2.1
     * BUTTON2 is connected to Pin P1.1
     * Both of these buttons are shorted to ground when the button is pressed.
     * In order to make the circuit work, an internal pull-up resistor is
     * enabled. This makes the polarity 1=not pushed, 0=pushed.
     *
     */
    P2DIR_bits.P2DIR1 = 0u;     // set BUTTON1 pin as input (DIR=0)
    P2REN_bits.P2REN1 = 1u;     // enable the pin's resistor
    P2OUT_bits.P2OUT1 = 1u;     // set resistor to PULL-UP

    P1DIR_bits.P1DIR1 = 0u;     // set BUTTON2 pin as input (DIR=0)
    P1REN_bits.P1REN1 = 1u;     // enable the pin's resistor
    P1OUT_bits.P1OUT1 = 1u;     // set the resistor to PULL-UP


    // Loop through and initialize all of the buttons...
    for (x=0u; x<MAX_BUTTONS; x++)
    {
        // And make sure all of the callback values are NULL (disabled)
        Buttons[x].callback = (ButtonCallback_t)NULL;
    }


    // set the variable values that define the button service behavior.
    s_ButtonSrvcInterval_ms = ButtonSrvcInterval_ms;
    s_ButtonDbncThresh_cnt = ButtonDbncThresh_cnt;
    s_ButtonDblClickTimeout_ms = ButtonDblClickTimeout_ms;
    s_ButtonLngPressTimeout_ms = ButtonLngPressTimeout_ms;


    // Configure and start the button service in the TIMERA2 library.
    Set_Button_Service(s_ButtonSrvcInterval_ms,
                       Button_Service_Callback);
}


/******************************************************************************
    Subroutine:     Set_Button_Callback
    Description:    Use this function to register a pin (connected to a button
                    or signal) to be serviced by the button service library.
    Inputs:         uint16_t index: The index of the Buttons[] array to place
                    the new pin (button) being registered. Valid values are from
                    zero to MAX_BUTTONS-1. However, index values need to be
                    sequential, without gaps, as the service will stop
                    processing the array at the first unregistered index.
                    uint16_t pin: The arduino-style definition of a pin based
                    on it's pin number in the package (see GPIO library).
                    uint16_t polarity: This value defines the "asserted" state
                    of the pin being registered. For example, for a pin that is
                    connected to a pull-up (1), that gets shorted to gnd (0)
                    when a button is pressed, 0 would be the asserted state.
                    ButtonCallback_t callback: The name of the function to be
                    called when the button service detects a button event.
    Outputs:        None

******************************************************************************/
void Set_Button_Callback(uint16_t index,
                         uint16_t pin,
                         uint16_t polarity,
                         ButtonCallback_t callback)
{
    // perform basic integrity checks. Take no action for invalid requests.
    if (MAX_BUTTONS <= index) {return;}
    if (0u == pinValid(pin)) {return;}
    if (NULL == callback) {return;}
    if ((0u != polarity) && (1u != polarity)) {return;}

    Buttons[index].pin = pin;
    Buttons[index].polarity = polarity;
    Buttons[index].callback = callback;
}


/******************************************************************************
    Subroutine:     Get_Button_Status
    Description:    Use this function to read the button events of the
                    button at the index provided.
    Inputs:         uint16_t index: The index of the Buttons[] array from which
                    the button events are to be read.
    Outputs:        ButtonEvents_t: The return value which provides the
                    button events. See .h file for structure definition.

******************************************************************************/
ButtonEvents_t Get_Button_Status(uint16_t index)
{
    static ButtonEvents_t retval;

    // perform basic integrity checks.
    // If the index is invalid, return an invalid response.
    if (MAX_BUTTONS <= index)
    {
        retval.reg = 0xFF;
    }
    else
    {
        retval = Buttons[index].status;
    }

    return retval;
}



/******************************************************************************
    Subroutine:     Clear_Button_Status
    Description:    Use this function to clear the button events of the
                    button at the index provided.
    Inputs:         uint16_t index: The index of the Buttons[] array for which
                    the button events are to be cleared.
    Outputs:        None

******************************************************************************/
void Clear_Button_Status(uint16_t index)
{
    // perform basic integrity checks. Take no action for invalid requests.
    if (MAX_BUTTONS <= index) {return;}

    Buttons[index].status.reg = 0u;
}


/******************************************************************************
    Subroutine:     Button_Service_Callback
    Description:    After the BUTTON library has been initialized by calling
                    MSP430F5529LP_BUTTONS_Initialize(), and after global
                    interrupts have been enabled, this function is called
                    repeatedly by the TIMERA2 library module at an interval
                    defined by s_ButtonSrvcInterval_ms.
    Inputs:         None
    Outputs:        None

    NOTE: This function is called within the context of an ISR.

******************************************************************************/
void Button_Service_Callback(void)
{
    uint16_t    x;

    // Loop through all of the Buttons
    for (x=0u; x<MAX_BUTTONS; x++)
    {
        // If the current index is registered (not NULL)...
        if (NULL != Buttons[x].callback)
        {
            // Run the button state machine for this button
            Button_State_Machine(x);
        }
        // If the current index is NULL...
        else
        {
            // Stop processing the array.
            break;
        }
    }
}

/******************************************************************************
    Subroutine:     Button_State_Machine
    Description:    This function is called for each registered button, and
                    pushes the buttons through the state machine based on the
                    variables within the Button_Callback_t structure. This
                    makes the state machine operation for each button
                    independent.
    Inputs:         uint16_t x: The index of the Buttons[] array for which the
                    state machine is being called.
    Outputs:        None

    NOTE: This function is called within the context of an ISR.

******************************************************************************/
static void Button_State_Machine(uint16_t x)
{
    switch(Buttons[x].state)
    {

        //#####################################################################
        //  STATE: UP1
        //#####################################################################

        case(UP1_ENTRY):
        {
            Buttons[x].debounce = 0;
            Buttons[x].state = UP1_MAIN;
        }
        break;

        case(UP1_MAIN):
        {
            // If the button is pressed...
            if (Buttons[x].polarity == pinInput(Buttons[x].pin))
            {
                Buttons[x].debounce += 1u;    // accumulate debounce samples
            }
            // If the button is unpressed...
            else
            {
                Buttons[x].debounce = 0u;     // reset the debounce value
            }

            // if there are N consecutive measurements...
            if (s_ButtonDbncThresh_cnt <= Buttons[x].debounce)
            {
                Buttons[x].state = DN1_ENTRY;
            }
        }
        break;


        //#####################################################################
        //  STATE: DN1
        //#####################################################################

        case(DN1_ENTRY):
        {
            Buttons[x].start = GetTick();
            Buttons[x].debounce = 0u;
            Buttons[x].longpressed = 0u;
            Buttons[x].state = DN1_MAIN;
        }
        break;

        case(DN1_MAIN):
        {
            if (!Buttons[x].longpressed)
            {
                if (Expired(s_ButtonLngPressTimeout_ms, Buttons[x].start, GetTick()))
                {
                    Buttons[x].longpressed = 1u;
                    Buttons[x].status.long_press = 1u;
                    if (NULL != Buttons[x].callback) {Buttons[x].callback();}
                }
            }

            // If the button is unpressed...
            if (Buttons[x].polarity != pinInput(Buttons[x].pin))
            {
                Buttons[x].debounce += 1u;    // accumulate debounce samples
            }
            // If the button is pressed...
            else
            {
                Buttons[x].debounce = 0u;     // reset the debounce value
            }

            // if there are N consecutive measurements...
            if (s_ButtonDbncThresh_cnt <= Buttons[x].debounce)
            {
                if (!Buttons[x].longpressed)
                {
                    if (Expired(s_ButtonDblClickTimeout_ms, Buttons[x].start, GetTick()))
                    {
                        Buttons[x].status.single_press = 1u;
                        if (NULL != Buttons[x].callback) {Buttons[x].callback();}
                        Buttons[x].state = UP1_ENTRY;
                    }
                    else
                    {
                        Buttons[x].state = UP2_ENTRY;
                    }
                }
                else
                {
                    Buttons[x].state = UP1_ENTRY;
                }
            }
        }
        break;


        //#####################################################################
        //  STATE: UP2
        //#####################################################################

        case(UP2_ENTRY):
        {
            Buttons[x].start = GetTick();
            Buttons[x].debounce = 0u;
            Buttons[x].state = UP2_MAIN;
        }
        break;

        case(UP2_MAIN):
        {
            if (Expired(s_ButtonDblClickTimeout_ms, Buttons[x].start, GetTick()))
            {
                Buttons[x].status.single_press = 1u;
                if (NULL != Buttons[x].callback) {Buttons[x].callback();}
                Buttons[x].state = UP1_ENTRY;
            }

            // If the button is pressed...
            if (Buttons[x].polarity == pinInput(Buttons[x].pin))
            {
                Buttons[x].debounce += 1u;    // accumulate debounce samples
            }
            // If the button is unpressed...
            else
            {
                Buttons[x].debounce = 0u;     // reset the debounce value
            }

            // if there are N consecutive measurements...
            if (s_ButtonDbncThresh_cnt <= Buttons[x].debounce)
            {
                Buttons[x].state = DN2_ENTRY;
            }
        }
        break;


        //#####################################################################
        //  STATE: DN2
        //#####################################################################

        case(DN2_ENTRY):
        {
            Buttons[x].start = GetTick();
            Buttons[x].debounce = 0u;
            Buttons[x].state = DN2_MAIN;
        }
        break;

        case(DN2_MAIN):
        {
            // If the button is unpressed...
            if (Buttons[x].polarity != pinInput(Buttons[x].pin))
            {
                Buttons[x].debounce += 1u;    // accumulate debounce samples
            }
            // If the button is unpressed...
            else
            {
                Buttons[x].debounce = 0u;     // reset the debounce value
            }

            // if there are N consecutive measurements...
            if (s_ButtonDbncThresh_cnt <= Buttons[x].debounce)
            {
                Buttons[x].status.double_click = 1u;
                if (NULL != Buttons[x].callback) {Buttons[x].callback();}
                Buttons[x].state = UP1_ENTRY;
            }
        }
        break;


        //#####################################################################
        //  DEFAULT
        //#####################################################################

        default:
        {
            Buttons[x].state = UP1_ENTRY;
        }
        break;
    }
}


/******************************************************************************
    End of File: MSP430F5529LP_BUTTONS.c
******************************************************************************/
