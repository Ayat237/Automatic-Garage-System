/*
 * UART_Interface.h
 * SWC: UART communication protocol
 * Created on: Aug 31, 2023
 * Author: Ayat Mohamed
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

typedef enum
{
	STOP_1BIT,
	STOP_2BIT
}StopBit_type;

typedef enum
{
	DISABLED,
	RESEVED,
	EVEN_PARITY,
	ODD_PARITY
}ParityBit_type;

typedef enum
{
	DATA_5BIT,
	DATA_6BIT,
	DATA_7BIT,
	DATA_8BIT,
	DATA_9BIT=7
}DataBit_type;




void UART_VidSendData(uint8 copy_data);

uint8 UART_U8ReciveData(void);

uint8 UART_U8DataAvailable(void);

void UART_VidSendDataString(char *copy_dataString);

uint8 UART_U8ReciveDataString(uint8 *copy_dataString , uint8 copy_stringSize);

void UART_VidInit(uint8 copy_stopBit ,uint8 copy_ParityBit ,uint8 copy_dataBit);

#endif /* UART_INTERFACE_H_ */
