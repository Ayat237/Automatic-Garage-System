/*
 *  LCD_Program.c
 *  Created on: Aug 20, 2023
 *  version :3
 *  Author: Ayat Mohamed
 */
#include "STD_TYPES.h"
#include "DIO_INTERFACE.h"
#include "LCD_Config.h"
#include "LCD_Interface.h"
#include <util/delay.h>
#include<stdlib.h>

static uint8 cursor = 1;

void LCD_VidSendCommand(uint8 Copy_Command)
{
	//make RS = 0; to send command
	DIO_VidSetPinValue(LCD_CTRL_PORT , LCD_RS_PIN , PinLow);

	// set RW = 0; to write
	DIO_VidSetPinValue(LCD_CTRL_PORT , LCD_RW_PIN ,PinLow);

	// set command to data pin on port
	DIO_VidSetPortValue(LCD_DATA_PORT , Copy_Command);

	// send enable pulse.
	// set enable to high
	DIO_VidSetPinValue(LCD_CTRL_PORT , LCD_E_PIN ,PinHigh);

	_delay_ms(2);

	// set enable to low
	DIO_VidSetPinValue(LCD_CTRL_PORT , LCD_E_PIN ,PinLow);
}

void LCD_VidSendData(uint8 Copy_Data)
{
	//make RS = 0; to send command
	DIO_VidSetPinValue(LCD_CTRL_PORT , LCD_RS_PIN , PinHigh);

	// set RW = 0; to write
	DIO_VidSetPinValue(LCD_CTRL_PORT , LCD_RW_PIN ,PinLow);

	// set command to data pin on port
	DIO_VidSetPortValue(LCD_DATA_PORT , Copy_Data);

	// send enable pulse.
	// set enable to high
	DIO_VidSetPinValue(LCD_CTRL_PORT , LCD_E_PIN ,PinHigh);

	_delay_ms(2);

	// set enable to low
	DIO_VidSetPinValue(LCD_CTRL_PORT , LCD_E_PIN ,PinLow);
}

void LCD_Vid_Init(void)
{
	// wait for more than 30 ms
	_delay_ms(40);

	// function set command 2 line ,and  5*8 font size.
	LCD_VidSendCommand(0b00111000);

	//display on off control : display enable disable cursor , no blink cursor.
	LCD_VidSendCommand(0b00001100);

	// clear screen.
	LCD_VidSendCommand(1);


}
// move cursor
void LCD_VidMoveCursor(uint8 row , uint8 column)
{
	switch(row)
	{
	case 0 :
		if(column < 16)
		{
			LCD_VidSendCommand((0x80) + (column));
			cursor = column;
		}
		break;
	case 1:
		if(column < 16)
		{
			LCD_VidSendCommand((0x80) + 0x40 + (column));
			cursor = 17 + column;
		}
		break;
	}
}
// print string in spasefic adderss
void LCD_VidPrintStringRowColumn(uint8 *Copy_Str , uint8 row , uint8 column)
{
	LCD_VidMoveCursor(row , column);
	LCD_VidPrintString(Copy_Str);

}

// print string
void LCD_VidPrintString(uint8 *Copy_Str)
{

	uint8 iterator = 0;
	// check if the string is ending or not
	while(Copy_Str[iterator] != '\0')
	{
		if(iterator == 16)
		{
			LCD_VidMoveCursor(1,0);
		}
		// print the data
		LCD_VidSendData(Copy_Str[iterator]);

		//increase the address by one to send the next element.
		iterator++;
	}
}


void LCD_VidPrintNumber(uint32 Copy_Integer)
{
	// string to hold the ascii
	uint8 Hold_Ascii[16] ;

	// function itoa convert the data to its corresponding the ascii value from (0 to 9)decimal;
	itoa(Copy_Integer,Hold_Ascii,10);

	//print the integer as a string .
	LCD_VidPrintString(Hold_Ascii);
}

void LCD_VidClear_Screen(void)
{
	// send command clear screen
	LCD_VidSendCommand(0x01);
	cursor = 1;
}









