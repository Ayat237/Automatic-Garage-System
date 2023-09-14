/*
===================================================================================================
* Auther : Ayat Mohamed MOhamed 
* Object : DIO interface
* DIO_Interface.h
===================================================================================================
*/

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_
// 4 PROTS
typedef enum
{
	Port_A,
	Port_B,
	Port_C,
	Port_D
}et_Port;

// 8 pin of ports
typedef enum
{
	Pin0,
	Pin1,
	Pin2,
	Pin3,
	Pin4,
	Pin5,
	Pin6,
	Pin7

}et_Pin;

// pin direction
typedef enum
{
	Input,
	Output
}et_Direction;

// 0--> pinLow , 1-->pinHigh
typedef enum
{
	PinLow,
    PinHigh
}et_status;

// setting Pin Direction
void DIO_VidSetPinDirection(uint8 Copy_Port , uint8 Copy_Pin ,uint8 Copy_Direction);

// setting Pin Value
void DIO_VidSetPinValue(uint8 Copy_Port , uint8 Copy_Pin ,uint8 Copy_Value);

// Getting Pin Value
void DIO_VidGetPinValue(uint8 Copy_Port , uint8 Copy_Pin ,uint8 *Ptr_Data);

// setting Port Direction
void DIO_VidSetPortDirection(uint8 Copy_Port , uint8 Copy_Direction);

// setting Port Value
void DIO_VidSetPortValue(uint8 Copy_Port , uint8 Copy_Value);

// Getting Port Value
void DIO_VidGetPortValue(uint8 Copy_Port , uint8 *Ptr_Data);









#endif
