/*
===================================================================================================
 * Auther : Ayat Mohamed MOhamed
 * Object : DIO Program
 * DIO_Prog.h
===================================================================================================
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_PRIVATE.h"
#include "DIO_INTERFACE.h"

/*
 ***************************************************************************************
 ***************************************** PINS ****************************************
 ***************************************************************************************
 */

//******************************* setting Pin Direction ********************************
void DIO_VidSetPinDirection(uint8 Copy_Port , uint8 Copy_Pin , uint8 Copy_Direction)
{
	if(Copy_Direction == Input)
	{
		switch(Copy_Port)
		{
		case Port_A:
			CLEAR_BIT(DDRA,Copy_Pin);
			break;
		case Port_B:
			CLEAR_BIT(DDRB,Copy_Pin);
			break;
		case Port_C:
			CLEAR_BIT(DDRC,Copy_Pin);
			break;
		case Port_D:
			CLEAR_BIT(DDRD,Copy_Pin);
			break;
		}
	}
	else if(Copy_Direction == Output)
	{
		switch(Copy_Port)
		{
		case Port_A:
			SET_BIT(DDRA,Copy_Pin);
			break;
		case Port_B:
			SET_BIT(DDRB,Copy_Pin);
			break;
		case Port_C:
			SET_BIT(DDRC,Copy_Pin);
			break;
		case Port_D:
			SET_BIT(DDRD,Copy_Pin);
			break;
		}
	}
}

//******************************** setting Pin Value ***********************************
void DIO_VidSetPinValue(uint8 Copy_Port , uint8 Copy_Pin ,uint8 Copy_Value)
{
	if(Copy_Value == PinHigh)
	{
		switch(Copy_Port)
		{
		case Port_A:
			SET_BIT(PORTA,Copy_Pin);
			break;
		case Port_B:
			SET_BIT(PORTB,Copy_Pin);
			break;
		case Port_C:
			SET_BIT(PORTC,Copy_Pin);
			break;
		case Port_D:
			SET_BIT(PORTD,Copy_Pin);
			break;
		}
	}

	else if(Copy_Value == PinLow)
	{
		switch(Copy_Port)
		{
		case Port_A:
			CLEAR_BIT(PORTA,Copy_Pin);
			break;
		case Port_B:
			CLEAR_BIT(PORTB,Copy_Pin);
			break;
		case Port_C:
			CLEAR_BIT(PORTC,Copy_Pin);
			break;
		case Port_D:
			CLEAR_BIT(PORTD,Copy_Pin);
			break;
		}
	}
}


//********************************* Getting Pin Value *********************************
void DIO_VidGetPinValue(uint8 Copy_Port , uint8 Copy_Pin ,uint8 *Ptr_Data)
{
	switch (Copy_Port)
	{
	case Port_A:
		*Ptr_Data = GET_BIT(PINA,Copy_Pin);
		break;
	case Port_B:
		*Ptr_Data = GET_BIT(PINB,Copy_Pin);
		break;
	case Port_C:
		*Ptr_Data = GET_BIT(PINC,Copy_Pin);
		break;
	case Port_D:
		*Ptr_Data = GET_BIT(PIND,Copy_Pin);
		break;
	}
}


/*
 ***************************************************************************************
 ***************************************** PINS ****************************************
 ***************************************************************************************
 */

//******************************* setting Port Direction *******************************
void DIO_VidSetPortDirection(uint8 Copy_Port , uint8 Copy_Direction)
{
	if(Copy_Direction == Input)
	{
		switch(Copy_Port)
		{
		case Port_A:
			DDRA = 0x00;
			break;
		case Port_B:
			DDRB = 0x00;
			break;
		case Port_C:
			DDRC = 0x00;
			break;
		case Port_D:
			DDRD = 0x00;
			break;
		}
	}
	else if(Copy_Direction == Output)
	{
		switch(Copy_Port)
		{
		case Port_A:
			DDRA = 0xFF;
			break;
		case Port_B:
			DDRB = 0xFF;
			break;
		case Port_C:
			DDRC = 0xFF;
			break;
		case Port_D:
			DDRD = 0xFF;
			break;
		}
	}
}


//******************************* setting Port Value **********************************
void DIO_VidSetPortValue(uint8 Copy_Port , uint8 Copy_Value)
{
		switch(Copy_Port)
		{
		case Port_A:
			PORTA = Copy_Value;
			break;
		case Port_B:
			PORTB = Copy_Value;
			break;
		case Port_C:
			PORTC = Copy_Value;
			break;
		case Port_D:
			PORTD = Copy_Value;
			break;
		}
}

//******************************* Getting Port Value **********************************
void DIO_VidGetPortValue(uint8 Copy_Port , uint8 *Ptr_Data)
{
	switch (Copy_Port)
		{
		case Port_A:
			*Ptr_Data = PINA;
			break;
		case Port_B:
			*Ptr_Data = PINB;
			break;
		case Port_C:
			*Ptr_Data = PINC;
			break;
		case Port_D:
			*Ptr_Data = PIND;
			break;
		}
}

















