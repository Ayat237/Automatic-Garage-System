/*
 *  LCD_INTERFACE.h
 *  Created on: Aug 20, 2023
 *  Author: Ayat Mohamed
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

// send command to LCD -- RS=0
void LCD_VidSendCommand(uint8 Copy_Command);

// send Data to LCD -- RS=1
void LCD_VidSendData(uint8 Copy_Data);

//print string
void LCD_VidPrintString(uint8 *Copy_Str);

// print the number by covert the string into integer
void LCD_VidPrintNumber(uint32 Copy_Integer);

// move cursor
void LCD_VidMoveCursor(uint8 row , uint8 column);

//
void LCD_VidPrintStringRowColumn(uint8 *Copy_Str,uint8 row , uint8 column);

// initialize the LCD.
void LCD_Vid_Init(void);

void LCD_VidClear_Screen(void);

#endif /* LCD_INTERFACE_H_ */
