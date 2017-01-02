
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
 * FileName:      MSP430F5529LP_BUTTONS.h
 *
 * Description
 *
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
 *
 *                                                                            */
/* ===========================================================================*/

#ifndef __MSP430F5529LP_BUTTONS_H__
#define __MSP430F5529LP_BUTTONS_H__


/******************************************************************************
    PUBLIC DEFINITIONS
******************************************************************************/

    // These definitions provide the pin numbers for the buttons on the
    // MSP430F5529LP launchpad board.

    #define MSP430F5529LP_BUTTON1     30      // P2IN_bits.P2IN1
    #define MSP430F5529LP_BUTTON2     22      // P1IN_bits.P1IN1

    // This typedef is required to let the compiler know the type of function
    // pointer used in the function prototypes below.

    typedef void (*ButtonCallback_t) (void);

    typedef volatile union
    {
        uint16_t reg;
        struct
        {
            uint16_t    single_press    :1;
            uint16_t    double_click    :1;
            uint16_t    long_press      :1;
        };
    }ButtonEvents_t;


/******************************************************************************
    PUBLIC FUNCTION PROTOTYPES
******************************************************************************/

    void MSP430F5529LP_BUTTONS_Initialize(uint16_t  ButtonSrvcInterval_ms,
                                          uint16_t  ButtonDbncThresh_cnt,
                                          uint16_t  ButtonDblClickTimeout_ms,
                                          uint16_t  ButtonLngPressTimeout_ms);

    void Set_Button_Callback(uint16_t index,
                             uint16_t pin,
                             uint16_t polarity,
                             ButtonCallback_t callback);

    ButtonEvents_t Get_Button_Status(uint16_t index);

    void Clear_Button_Status(uint16_t index);


/******************************************************************************
    PUBLIC VARIABLES (extern)
******************************************************************************/


/******************************************************************************
    End MSP430F5529LP_BUTTONS.h
******************************************************************************/

#endif   // __MSP430F5529LP_BUTTONS_H__

