
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
 * FileName:      LCD_HD44780_4BIT.c
 *
 * This example demonstrates writing to a 20x4 character LCD module based on
 * the HD44780 display controller using the 4-bit parallel interface mode. The
 * example uses a blocking delay to set the update speed of an 8-bit up-counter
 * which is displayed on decimal, hexadecimal, and binary formats on the LCD.
 * This example can be used to explore display characteristics such as refresh
 * rate.
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

    // These delays are from the HD44780 datasheet for various hold times,
    // minimum pulse width values, etc.

    #define LCD_DELAY_5ns       __delay_cycles((005e-9)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_10ns      __delay_cycles((010e-9)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_40ns      __delay_cycles((040e-9)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_80ns      __delay_cycles((080e-9)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_230ns     __delay_cycles((230e-9)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_270ns     __delay_cycles((270e-9)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_150us     __delay_cycles((150e-6)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_50us      __delay_cycles((050e-6)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_2ms       __delay_cycles((002e-3)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_5ms       __delay_cycles((005e-3)/(1.0/CLOCK_FREQ))
    #define LCD_DELAY_100ms     __delay_cycles((100e-3)/(1.0/CLOCK_FREQ))


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


/******************************************************************************
    PRIVATE FUNCTION PROTOTYPES (static)
******************************************************************************/

    static void LcdWriteReg(uint16_t value, LcdRegType_enum reg);

    static void LcdWrite4bits(uint16_t value, LcdNibble_enum nibble);

    static void SetPinsForRead(void);

    static void SetPinsForWrite(void);


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

   static   uint16_t    s_LcdStartTime;

   static   uint16_t    s_LCD_RS;
   static   uint16_t    s_LCD_RW;
   static   uint16_t    s_LCD_EN;
   static   uint16_t    s_LCD_D4;
   static   uint16_t    s_LCD_D5;
   static   uint16_t    s_LCD_D6;
   static   uint16_t    s_LCD_D7;

   static	uint16_t  	s_str_size;
   static	char        s_lcd_string[40];
   static	char*       s_lcd_stringPtr;

   
/******************************************************************************
    Subroutine:     LCD_Initialize
    Description:    This function initializes the LCD display.
    Inputs:         uint16_t LcdPin_RS: Pin number of the Register Select pin
                    uint16_t LcdPin_RW: Pin number of the Read/Write pin
                    uint16_t LcdPin_EN: Pin number of the Enable pin
                    uint16_t LcdPin_D4: Pin number of data bus pin 4
                    uint16_t LcdPin_D5: Pin number of data bus pin 5
                    uint16_t LcdPin_D6: Pin number of data bus pin 6
                    uint16_t LcdPin_D7: Pin number of data bus pin 7
                    NOTE: All pin numbers are package pins (see GPIO hardware
                    library for more information)
    Outputs:        None

******************************************************************************/
void LCD_Initialize(uint16_t LcdPin_RS,
                    uint16_t LcdPin_RW,
                    uint16_t LcdPin_EN,
                    uint16_t LcdPin_D4,
                    uint16_t LcdPin_D5,
                    uint16_t LcdPin_D6,
                    uint16_t LcdPin_D7)
{
	// Save the LCD pin assignments to file scope variables
    s_LCD_RS = LcdPin_RS;
    s_LCD_RW = LcdPin_RW;
    s_LCD_EN = LcdPin_EN;
	s_LCD_D4 = LcdPin_D4;
	s_LCD_D5 = LcdPin_D5;
	s_LCD_D6 = LcdPin_D6;
	s_LCD_D7 = LcdPin_D7;

	// Assign the direction of the LCD control lines. These will always be
	// outputs from the MCU
	pinDirection(s_LCD_EN, OUTPUT);
	pinDirection(s_LCD_RS, OUTPUT);
	pinDirection(s_LCD_RW, OUTPUT);

	pinOutput(s_LCD_EN, 0);     // Default state, EN = 0

	// Set data lines as outputs
	SetPinsForWrite();

	// Wait 100 ms for Internal LCD Initialization to complete
	LCD_DELAY_100ms;
   
	// put the LCD into 4 bit mode. This is according to the hitachi
	// HD44780 datasheet figure 24, pg 46
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

    return;
}


/******************************************************************************
    Subroutine:     LCD_SetPosition
    Description:    This function sets the cursor position of the LCD display.
                    Text sent via LCD_Print() will begin printing at the
                    cursor position specified.
    Inputs:         uint16_t value: The desired position of the cursor.
    Outputs:        None

******************************************************************************/
void LCD_SetPosition(uint16_t value)
{
    // if the cursor value is illegal, take no action
    if ( (LCD_ROW1 > value) || ((LCD_ROW4 + 20) < value) ) {return;}

    /* This next section is critical to ensuring that writing text that is too
     * large for the remaining characters in the row does not overflow beyond
     * the end of the current row. The size of the string that will be allowed
     * to be written using LCD_Print() will be limited based on the cursor
     * position requested. Without this limitation, the LCD controller would
     * normally overflow from row 1 to row 3, and from row 2 to row 4. This is
     * because the controller is actually made for 40x2 LCDs, but is being used
     * for a 20x4 LCD. If you're curious, comment this next section out, write
     * a very large text string and see what happens.
     */
    if      (LCD_ROW4 <= value)  {s_str_size = LCD_ROW4 + 20 - value;}
    else if (LCD_ROW2 <= value)  {s_str_size = LCD_ROW2 + 20 - value;}
    else if (LCD_ROW3 <= value)  {s_str_size = LCD_ROW3 + 20 - value;}
    else if (LCD_ROW1 <= value)  {s_str_size = LCD_ROW1 + 20 - value;}

    // Write the new cursor position to the LCD
    LcdWriteReg(value, COMMAND);

    return;
}


/******************************************************************************
    Subroutine:     LCD_Print
    Description:    This function prints the text string to the LCD display.
    Inputs:         const char * format, ...: This is the string that contains
                    the text to be written to the LCD. It can optionally
                    contain embedded format tags that are replaced by the
                    values specified in subsequent additional arguments and
                    formatted as requested. Works the same as printf().
    Outputs:        None

******************************************************************************/
void LCD_Print(const char * format, ...)
{
    int x;

    /* Using the C library stdarg.h the 2 lines of code are required to access
     * the unnamed arguments. One must declare a variable of type va_list. The
     * macro va_start is then called with two arguments: the first is the
     * variable declared of the type va_list, the second is the name of the
     * last named parameter of the function. After this, each invocation of the
     * va_arg macro yields the next argument. The first argument to va_arg
     * is the va_list and the second is the type of the next argument passed to
     * the function. Finally, the va_end macro must be called on the va_list
     * before the function returns. (It is not required to read in all the
     * arguments.)
     */
    va_list args;
    va_start(args, format);

    // This shouldn't ever change, but just in case, make sure the string
    // pointer is set to the beginning of the string variable.
    s_lcd_stringPtr = &s_lcd_string[0];

    // This function sends the formatted output to the string s_lcd_string
    // using the argument list passed to it. Because this function accepts the
    // arg list as-is, there is no need to parse the arguments.
    vsprintf(s_lcd_string, format, args);

    // If the string passed to LCD_Print is larger than the number of
    // remaining characters, limit the size to not exceed the row.
    if (s_str_size > strlen(s_lcd_string))
    {
        s_str_size = strlen(s_lcd_string);
    }

    // For each character in the string, send the character to the LCD display.
    // The LCD was initialized for the cursor to auto-increment, so each new
    // character will be placed at current position + 1.
    for (x=0; x<s_str_size; x++)
    {
        LcdWriteReg(s_lcd_stringPtr[x], DATA);
    }

    // The va_end macro performs cleanup for the args object initialized by the
    // call to vs_start(). This frees the va_list.
    va_end(args);

    return;
}


/******************************************************************************
    Subroutine:     LcdWriteReg
    Description:    This function writes the requested value to the LCD, and
                    blocks until the request is completed.
    Inputs:         uint16_t value: value to be written to the LCD
                    LcdRegType_enum reg: defines the register to be written.
                    Can be COMMAND or DATA register.
    Outputs:        None

******************************************************************************/
void LcdWriteReg(uint16_t value, LcdRegType_enum reg)
{
    static uint16_t     busy;

    pinOutput(s_LCD_EN, 0);     // EN = 0, should already be true

    // In case it wasn't, hold enable low for the minimum address hold time
    // before changing RS or RW.
    LCD_DELAY_10ns;

    pinOutput(s_LCD_RS, reg);   // RS = 0 for Instruction registers
                                // RS = 1 for Data registers
    pinOutput(s_LCD_RW, 0);     // RW = 0, select Write operation

    // After changing RS and RW, delay for the minimum address setup time
    // before changing the enable state.
    LCD_DELAY_40ns;

    LcdWrite4bits(value, UPPER_NIBBLE);     // Set the data D0-D7 = value (4-7)
    LcdWrite4bits(value, LOWER_NIBBLE);     // Set the data D0-D7 = value (0-3)

    // commands require at least 37us to settle.
    if (COMMAND == reg) { LCD_DELAY_50us; }

    SetPinsForRead();

    pinOutput(s_LCD_RS, 0);     // RS = 0; Select Instruction reg
    pinOutput(s_LCD_RW, 1);     // RW = 0, select Read operation
    LCD_DELAY_40ns;

    s_LcdStartTime = GetTick();

    do  // Spin here until busy = False, Or the timeout expires.
    {
        pinOutput(s_LCD_EN, 1);     // EN = 1, prepare to read data
        LCD_DELAY_230ns;

        busy = pinInput(s_LCD_D7);  // Read BUSY flag

        pinOutput(s_LCD_EN, 0);     // EN = 0, strobe data write
        LCD_DELAY_270ns;

        // In 4-bit mode the 2nd nibble must be read even if it isn't used.
        pinOutput(s_LCD_EN, 1);     // EN = 1, prepare to read data
        LCD_DELAY_230ns;
        pinOutput(s_LCD_EN, 0);     // EN = 0, strobe data write
        LCD_DELAY_270ns;
  
    } while ( busy  && (!(Expired(1000, s_LcdStartTime, GetTick()))) );
  
    SetPinsForWrite();

    return;
}


/******************************************************************************
    Subroutine:     LcdWrite4bits
    Description:    In 4-bit interface mode the full 8-bit command is broken
                    into 2 nibbles, and sent one nibble at a time, upper
                    nibble first. This function is used to write the nibbles.
    Inputs:         uint16_t value: The 8-bit data value
                    LcdNibble_enum nibble: defines which nibble to put on the
                    data bus (UPPER_NIBBLE or LOWER_NIBBLE)
    Outputs:        None

******************************************************************************/
void LcdWrite4bits(uint16_t value, LcdNibble_enum nibble)
{
    pinOutput(s_LCD_EN, 1);     // EN = 1, prepare to write data

    // Set the requested nibble to the data bus
    if (UPPER_NIBBLE == nibble)
    {
        pinOutput(s_LCD_D4, ((value >> 4) & 1));
        pinOutput(s_LCD_D5, ((value >> 5) & 1));
        pinOutput(s_LCD_D6, ((value >> 6) & 1));
        pinOutput(s_LCD_D7, ((value >> 7) & 1));
    }
    else
    {
        pinOutput(s_LCD_D4, (value & 1));
        pinOutput(s_LCD_D5, ((value >> 1) & 1));
        pinOutput(s_LCD_D6, ((value >> 2) & 1));
        pinOutput(s_LCD_D7, ((value >> 3) & 1));
    }

    // Hold enable high for minimum high level pulse width
    LCD_DELAY_230ns;

    pinOutput(s_LCD_EN, 0);     // EN = 0, strobe data write

    // Hold enable low for minimum data hold time (which is only 5 ns), or
    // the value required to ensure that the fastest enable cycle time is
    // longer than 500 ns.
    LCD_DELAY_270ns;

    return;
}


/******************************************************************************
    Subroutine:     SetPinsForRead
    Description:    This function changes the direction of the data bus pins
                    to inputs. This is needed to read the busy flag to
                    determine if the requsted action has completed.
    Inputs:         None
    Outputs:        None

******************************************************************************/
void SetPinsForRead(void)
{
    pinDirection(s_LCD_D4, INPUT);
    pinDirection(s_LCD_D5, INPUT);
    pinDirection(s_LCD_D6, INPUT);
    pinDirection(s_LCD_D7, INPUT);

    return;
}


/******************************************************************************
    Subroutine:     SetPinsForWrite
    Description:    This function changes the direction of the data bus pins
                    to outputs. This is needed to write the next request to
                    the LCD.
    Inputs:         None
    Outputs:        None

******************************************************************************/
void SetPinsForWrite(void)
{
    pinDirection(s_LCD_D4, OUTPUT);
    pinDirection(s_LCD_D5, OUTPUT);
    pinDirection(s_LCD_D6, OUTPUT);
    pinDirection(s_LCD_D7, OUTPUT);

    return;
}



/******************************************************************************
	End of File: LCD_HD44780_4bit.c
******************************************************************************/
