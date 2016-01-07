
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
 * FileName:      LCD_HD44780_I2C.c
 *
 * This file provides functions for the 20x4 character LCD modules that use the
 * The HD44780x dot-matrix liquid crystal display controller and driver in the
 * 4-bit parallel interface mode, driven by an I2C expander interface.
 *
 * Version 1.0
 *
 * Rev. 1.0, Initial Release
 *
 *                                                                            */
/* ===========================================================================*/

#include "MSP430F5529LP.h"
#include "MSP430F5529LP_CLOCK.h"
#include "LCD_HD44780_I2C.h"
#include "MSP430F5529LP_I2C.h"

#include "ctype.h"
#include "stdio.h"
#include "string.h"
#include "stdarg.h"


/******************************************************************************
    PUBLIC DEFINITIONS
******************************************************************************/

   
/******************************************************************************
    PUBLIC VARIABLES
******************************************************************************/
  
 
/******************************************************************************
    PRIVATE DEFINITIONS (static const)
******************************************************************************/

    // These delays are from the HD44780 datasheet, for various hold times,
    // minimum pulse width values, etc. The defined names are based on the
    // actual datasheet values. The corresponding delay setting is actually
    // twice the required value.

    #define LCD_DELAY_5ns       __delay_cycles((10e-9)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_10ns      __delay_cycles((20e-9)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_40ns      __delay_cycles((80e-9)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_80ns      __delay_cycles((160e-9)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_230ns     __delay_cycles((460e-9)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_270ns     __delay_cycles((540e-9)/(1.0/CLOCK_FREQ))

    #define LCD_DELAY_50us      __delay_cycles((50e-6)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_150us     __delay_cycles((150e-6)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_2ms       __delay_cycles((2e-3)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_5ms       __delay_cycles((5e-3)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_50ms      __delay_cycles((50e-3)/(1.0/CLOCK_FREQ))


    typedef enum
    {
        COMMAND = 0,
        DATA = 1
    } LcdRegType_enum;

    typedef enum
    {
        UPPER_NIBBLE = 0,
        LOWER_NIBBLE = 1
    } LcdNibble_enum;

    typedef union
    {
        uint8_t     reg;
        struct
        {
            uint8_t    RS        : 1;    // Register Select bit
            uint8_t    RW        : 1;    // Read / Write Select bit
            uint8_t    EN        : 1;    // Enable strobe (starts read/write)
            uint8_t    BL        : 1;    // Backlight
            uint8_t    D4        : 1;    // Data port bit 4
            uint8_t    D5        : 1;    // Data port bit 5
            uint8_t    D6        : 1;    // Data port bit 6
            uint8_t    D7        : 1;    // Data port bit 7
        } bits;
    } I2cExpndrBits_t;

    #define I2C_ADDR    0x27


/******************************************************************************
    PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/

    static void LcdWriteReg(uint16_t value, LcdRegType_enum reg);

    void LcdWrite4bits(uint16_t value, LcdNibble_enum nibble);


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


   STATIC   uint16_t    s_str_size;
   STATIC   char        s_lcd_string[40];
   STATIC   char*       s_lcd_stringPtr;

   STATIC   I2cExpndrBits_t     I2cBits;

   STATIC   uint8_t *   sp_reg;

   
/******************************************************************************
    Subroutine:     LCD_Initialize
    Description:
    Inputs:
    Outputs:

******************************************************************************/
void LCD_Initialize(void)
{
    sp_reg = &I2cBits.reg;

    // Power-on initialization

    // SEE PAGE 45/46 OF HD44780U DATASHEET FOR INITIALIZATION SPECIFICATION!
    // need at least 40ms after power rises above 2.7V before sending commands.
    LCD_DELAY_50ms;

    // Set initial state of the variable used to reflect remote expander ports.
    // Write this to i2c expander to reset the LCD interface. This also ensures
    // that RS and RW = 0 before sending initialization sequence.
    I2cBits.reg = 0;
    I2C_Write(I2C_ADDR, &I2cBits.reg);
    LCD_DELAY_40ns;

    // put the LCD into 4 bit mode
    // this is according to the hitachi HD44780 datasheet
    // figure 24, pg 46
    LcdWrite4bits(0x03, LOWER_NIBBLE);
    LCD_DELAY_5ms;
    LcdWrite4bits(0x03, LOWER_NIBBLE);
    LCD_DELAY_5ms;
    LcdWrite4bits(0x03, LOWER_NIBBLE);
    LCD_DELAY_150us;
    LcdWrite4bits(0x02, LOWER_NIBBLE);

    // function set: 4-bit interface, 2 display lines, 5x7 font
    LcdWriteReg(0x28, COMMAND);
    // entry mode set: increment automatically, no display shift
    LcdWriteReg(0x06, COMMAND);
    // display control: turn display on, cursor off, no blinking
    LcdWriteReg(0x0C, COMMAND);
    // clear display: clear display, set cursor position to zero
    LcdWriteReg(0x01, COMMAND);
    LCD_DELAY_2ms;  // clear command requires at least 1.5ms

    // Turn the backlight on to signify end of initialization
    I2cBits.bits.BL = 1;
    I2C_Write(I2C_ADDR, &I2cBits.reg);

    return;
}



/******************************************************************************
    Subroutine:     LCD_Print
    Description:
    Inputs:
    Outputs:

******************************************************************************/
void LCD_Print(const char * format, ...)
{
    int x;

    va_list args;
    va_start(args, format);

    s_lcd_stringPtr = &s_lcd_string[0];

    vsprintf(s_lcd_string, format, args);

    if (s_str_size > strlen(s_lcd_string))
    {
        s_str_size = strlen(s_lcd_string);
    }

    for (x=0; x<s_str_size; x++)
    {
        LcdWriteReg(s_lcd_stringPtr[x], DATA);
    }
}


/******************************************************************************
    Subroutine:     LCD_SetPosition
    Description:
    Inputs:
    Outputs:

******************************************************************************/
void LCD_SetPosition(uint16_t value)
{
    if      (LCD_ROW4 <= value)  {s_str_size = LCD_ROW4 + 20 - value;}
    else if (LCD_ROW2 <= value)  {s_str_size = LCD_ROW2 + 20 - value;}
    else if (LCD_ROW3 <= value)  {s_str_size = LCD_ROW3 + 20 - value;}
    else if (LCD_ROW1 <= value)  {s_str_size = LCD_ROW1 + 20 - value;}

    LcdWriteReg(value, COMMAND);

    return;
}


void LcdWriteReg(uint16_t value, LcdRegType_enum reg)
{
    I2cBits.bits.EN = 0;        // EN = 0, should already be true
    I2C_Write(I2C_ADDR, &I2cBits.reg);
    LCD_DELAY_10ns;

    I2cBits.bits.RS = reg;      // RS = 0 for Instruction registers
                                // RS = 1 for Data registers
    I2cBits.bits.RW = 0;        // RW = 0, select Write operation
    I2C_Write(I2C_ADDR, &I2cBits.reg);
    LCD_DELAY_40ns;

    LcdWrite4bits(value, UPPER_NIBBLE);     // Set the data D0-D7 = value (4-7)
    LcdWrite4bits(value, LOWER_NIBBLE);     // Set the data D0-D7 = value (0-3)

    // commands require at least 37us to settle.
    if (COMMAND == reg) { LCD_DELAY_50us; }

    return;
}


void LcdWrite4bits(uint16_t value, LcdNibble_enum nibble)
{
    // Set the data values on D7-D4 (4-bit interface)
    if (UPPER_NIBBLE == nibble)
    {
        I2cBits.bits.D4 = ((value >> 4) & 1);
        I2cBits.bits.D5 = ((value >> 5) & 1);
        I2cBits.bits.D6 = ((value >> 6) & 1);
        I2cBits.bits.D7 = ((value >> 7) & 1);
    }
    else
    {
        I2cBits.bits.D4 = (value & 1);
        I2cBits.bits.D5 = ((value >> 1) & 1);
        I2cBits.bits.D6 = ((value >> 2) & 1);
        I2cBits.bits.D7 = ((value >> 3) & 1);
    }

    I2cBits.bits.EN = 1;                // EN = 1, setup data bus
    I2C_Write(I2C_ADDR, &I2cBits.reg);
    LCD_DELAY_230ns;

    I2cBits.bits.EN = 0;                // EN = 0, strobe data write
    I2C_Write(I2C_ADDR, &I2cBits.reg);
    LCD_DELAY_270ns;

    return;
}



/******************************************************************************
    End of File: LCD_HD44780.c
******************************************************************************/
