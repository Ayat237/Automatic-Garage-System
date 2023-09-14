/*
 *  UART_Prog.c
 *  SWC: UART communication protocol
 *  Created on: Aug 31, 2023
 *  Author: Ayat Mohamed
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include "UART_Private.h"
#include "UART_Interface.h"

/* Send Data */
void UART_VidSendData(uint8 copy_data)
{
	/* wait until the transmit is empty*/
	while(GET_BIT(UCSRA,UCSRA_UDRE) == 0);

	/* write the data in UDR */
	UDR = copy_data;
}

/* Receive Data */
uint8 UART_U8ReciveData(void)
{
	/* wait receive operation until complete */
	while(GET_BIT(UCSRA,UCSRA_RXC) == 0);

	/* return the value of UDR */
	return UDR;
}

/*send string to UART */
void UART_VidSendDataString(char *copy_dataString)
{
	uint8 local_counter=0;
	while(copy_dataString[local_counter] != '\0')
	{
		UART_VidSendData(copy_dataString[local_counter]);
		local_counter++;
	}
}

uint8 UART_U8ReciveDataString(uint8 *copy_dataString , uint8 copy_stringSize)
{
	    uint8 local_counter = 0;
	    uint8 local_ErrorState = NO_ERROR_STATE;
	    if(copy_dataString == NULL)
	    {
	    	local_ErrorState = NULLPOINTER;
	    }
	    else
	    {
		    for(local_counter = 0 ; local_counter < copy_stringSize ; local_counter++)
		    {
		    	copy_dataString[local_counter] = UART_U8ReciveData();
		    }

	    }
	    return local_ErrorState;
}

/* initialize UART */
void UART_VidInit(uint8 copy_stopBit ,uint8 copy_ParityBit ,uint8 copy_dataBit)
{
	uint8 Local = 0;

	/* RX Enable And TX Enable */
	SET_BIT(UCSRB,UCSRB_RXEN);
	SET_BIT(UCSRB,UCSRB_TXEN);

	/* Register Select */
	SET_BIT(Local,UCSRC_URSEL);

	/* select stop bit */
	switch(copy_stopBit)
	{
	case STOP_1BIT:
		CLEAR_BIT(Local,UCSRC_USBS);
		break;
	case STOP_2BIT:
		SET_BIT(Local,UCSRC_USBS);
		break;
	}
	/* select parity bit */
	switch(copy_ParityBit)
	{
	case DISABLED:
		CLEAR_BIT(Local,UCSRC_UPM0);
		CLEAR_BIT(Local,UCSRC_UPM1);
		break;
	case RESEVED:
		SET_BIT(Local,UCSRC_UPM0);
		CLEAR_BIT(Local,UCSRC_UPM1);
		break;
	case EVEN_PARITY:
		CLEAR_BIT(Local,UCSRC_UPM0);
		SET_BIT(Local,UCSRC_UPM1);
		break;
	case ODD_PARITY:
		SET_BIT(Local,UCSRC_UPM0);
		SET_BIT(Local,UCSRC_UPM1);
		break;
	}
	/* select no of data bit */
	switch(copy_dataBit)
	{
	case DATA_5BIT:
		CLEAR_BIT(Local,UCSRC_UCSZ0);
		CLEAR_BIT(Local,UCSRC_UCSZ1);
		CLEAR_BIT(UCSRB,UCSRB_UCSZ2);
		break;
	case DATA_6BIT:
		SET_BIT(Local,UCSRC_UCSZ0);
		CLEAR_BIT(Local,UCSRC_UCSZ1);
		CLEAR_BIT(UCSRB,UCSRB_UCSZ2);
		break;
	case DATA_7BIT:
		CLEAR_BIT(Local,UCSRC_UCSZ0);
		SET_BIT(Local,UCSRC_UCSZ1);
		CLEAR_BIT(UCSRB,UCSRB_UCSZ2);
		break;
	case DATA_8BIT:
		SET_BIT(Local,UCSRC_UCSZ0);
		SET_BIT(Local,UCSRC_UCSZ1);
		CLEAR_BIT(UCSRB,UCSRB_UCSZ2);
		break;
	case DATA_9BIT:
		SET_BIT(Local,UCSRC_UCSZ0);
		SET_BIT(Local,UCSRC_UCSZ1);
		SET_BIT(UCSRB,UCSRB_UCSZ2);
		break;
	}

	/* Synchronos mode */
	CLEAR_BIT(Local,UCSRC_UMSEL);

	/* 0x86 or 0b10000110 */
	UCSRC = Local;


	/* Baud rate 9600bps */
	UBRRL = 51;
}


/*
 *
uint8 * UART_U8ReciveDataString()
{
	while(GET_BIT(UCSRA,UCSRA_RXC) == 0);

	while(UDR != '\0')
	{
		*copy_bufferString = UDR;

		copy_bufferString++;

		while(GET_BIT(UCSRA,UCSRA_RXC) == 0);
	}

	*copy_bufferString = UDR;

	return copy_bufferString;
}
*/
