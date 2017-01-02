
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
 * FileName:      LCD_HD44780_4BIT.h
 *
 * This file provides functions for the 20x4 character LCD modules that use the
 * The HD44780x dot-matrix liquid crystal display controller and driver in the
 * 4-bit parallel interface mode.
 *
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
 *
 *                                                                            */
/* ===========================================================================*/

#ifndef __LCD_HD44780_4BIT_H__
#define __LCD_HD44780_4BIT_H__

#include "MSP430F5529LP.h"


/******************************************************************************
   PUBLIC DEFINITIONS
******************************************************************************/

   #define LCD_ROW1  0x80 
   #define LCD_ROW2  0xC0 
   #define LCD_ROW3  0x94 
   #define LCD_ROW4  0xD4


/******************************************************************************
   PUBLIC FUNCTION PROTOTYPES
******************************************************************************/

   void LCD_Initialize(uint16_t LcdPin_RS,
                       uint16_t LcdPin_RW,
                       uint16_t LcdPin_EN,
                       uint16_t LcdPin_D4,
                       uint16_t LcdPin_D5,
                       uint16_t LcdPin_D6,
                       uint16_t LcdPin_D7);

   void LCD_SetPosition(uint16_t value);

   void LCD_Print(const char * format, ...);
   

/******************************************************************************
   PUBLIC VARIABLES (extern)
******************************************************************************/

   
/******************************************************************************
	End LCD_HD44780_4BIT.h
******************************************************************************/

#endif   // __LCD_HD44780_4BIT_H__

