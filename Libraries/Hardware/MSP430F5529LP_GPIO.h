
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
 * FileName:      MSP430F5529LP_GPIO.h
 *
 * This file provides functions to control and configure the General Purpose
 * Input / Output (GPIO) pins on the Texas Instruments MSP430F5529 Launchpad
 * development board. These functions provide "arduino-style" control of the
 * pins based on pin number (as viewed from the external package).
 *
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
 *
 *                                                                            */
/* ===========================================================================*/

#ifndef __MSP430F5529LP_GPIO_H__
#define __MSP430F5529LP_GPIO_H__


/******************************************************************************
    PUBLIC DEFINITIONS
******************************************************************************/

    // These definitions are identical to the arduino defintions for
    // GPIO control.

    typedef enum
    {
        LOW = 0,
        HIGH = 1
    } pinLevel_enum;

    typedef enum
    {
        INPUT = 0,
        OUTPUT = 1
    } pinDirection_enum;
   
    typedef enum
    {
        PULLDOWN = 0,
        PULLUP = 1
    } pinResType_enum;
   
    typedef enum
    {
        DISABLE = 0,
        ENABLE = 1
    } pinEnable_enum;
   
    typedef enum
    {
        GPIO = 0,
        ALT_FUNC = 1
    } pinSelect_enum;
   
   
/******************************************************************************
    PUBLIC FUNCTION PROTOTYPES
******************************************************************************/

    void pinDirection(uint8_t pin, pinDirection_enum pinDir);

    void pinResEnable(uint8_t pin, pinEnable_enum rEnable);

    void pinOutput(uint8_t pin, pinLevel_enum pLevel);

    void pinSelect(uint8_t pin, pinSelect_enum pSelect);

    uint8_t pinInput(uint8_t pin);
   

/******************************************************************************
    PUBLIC VARIABLES (extern)
******************************************************************************/


/******************************************************************************
     End MSP430F5529LP_GPIO.h
******************************************************************************/

#endif   // __MSP430F5529LP_GPIO_H__

