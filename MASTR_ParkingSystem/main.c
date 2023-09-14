/*
 * main.c
 *
 *  Created on: Sep 10, 2023
 *      Author: Ayat Mohamed
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <string.h>
#include "DIO_INTERFACE.h"
#include "SPI_Interface.h"
#include "UART_Private.h"
#include "UART_Interface.h"
#include "LCD_Interface.h"
#include "TIMER1_Private.h"
#include "TIMER1_Interface.h"
#include "ADC_Config.h"
#include "ADC_Interface.h"
#include "EX_INTERRUPT_Interface.h"
#include "GIE_Interface.h"
#include <util/delay.h>


#define BUZZER   Pin0
#define DEFAULT   0xFF

static uint16 digital_temp;
static float analog_temp ;
static uint8 LedToggel;
volatile uint8 RFID[15];
volatile uint8 local_counter = 0;
volatile uint8 isRFIDDataAvailable = 0;

void initialize_pins(void);
void initialize_peripherals(void);
void print_temperature(void);
void activate_alarm(void);
void read_RFID(void);

int main()
{
	/* initialize all pins*/
	initialize_pins();

	/* initialize all peripherals */
	initialize_peripherals();

	/* print on lcd */
	_delay_ms(250);
	LCD_VidPrintString("Temperature: ");

	while (1)
	{
		/* print the temp value */
		print_temperature();

		/* check the temp value */
		if (analog_temp > 40)
		{
			activate_alarm();
		}
		/* check on flag if data is received from UART */
		if(isRFIDDataAvailable)
		{
			// Access the RFID data from the global variable for further processing
			for(local_counter = 0 ; local_counter < 6 ; local_counter++)
			{
				SPI_TransReceive(RFID[local_counter]);
			}
			// Reset the flag
			isRFIDDataAvailable = 0;
		}
	}
}

void initialize_pins(void)
{
	/* set pin direction of MSTR */
	DIO_VidSetPinDirection(Port_B, Pin4, Input);     // SS: input pull up for master
	DIO_VidSetPinDirection(Port_B, Pin5, Output);    // MOSI: master output slave input
	DIO_VidSetPinDirection(Port_B, Pin6, Input);     // MISO: master input slave output
	DIO_VidSetPinDirection(Port_B, Pin7, Output);    // SCK: output

	/* set pin direction of RX */
	DIO_VidSetPinDirection(Port_D, Pin0, Input);


	/* set pin direction of Buzzer */
	DIO_VidSetPinDirection(Port_B, Pin1, Output);

	/* set pin direction of Fire Led */
	DIO_VidSetPinDirection(Port_D, Pin2, Output);

	/* set pin direction of RFID Interrupt */
	DIO_VidSetPinDirection(Port_D, Pin3, Input);

	/* set pin direction of LCD */
	DIO_VidSetPortDirection(Port_C, Output);
	DIO_VidSetPinDirection(Port_A, Pin1, Output);
	DIO_VidSetPinDirection(Port_A, Pin2, Output);
	DIO_VidSetPinDirection(Port_A, Pin3, Output);
}
void initialize_peripherals(void)
{
	/* initialize ADC */
	ADC_VidInit();

	/* initialize UART */
	UART_VidInit(STOP_1BIT, DISABLED, DATA_8BIT);

	/* initialize master */
	SPI_VidMaterInit(Fosc_16, CPHAS0, CPOL0);

	/* initialize LCD */
	LCD_Vid_Init();

	GIE_VidEnable();
}

void print_temperature(void)
{
	// take the digital reading of ADC
	digital_temp = ADC_U16ReadChannelSyn(0);

	// convert the digital value to analog value
	analog_temp = (150 * digital_temp * 5.0) / (1023 * 1.5);

	_delay_ms(250);
	LCD_VidMoveCursor(0, 13);

	// print temp degree
	LCD_VidPrintNumber(analog_temp);

	// display the celsius
	LCD_VidSendData(0xDF);
	LCD_VidSendData('c');
	LCD_VidSendData(0x20);
}

void activate_alarm(void)
{
	/* activate the alarm */
	DIO_VidSetPinValue(Port_B, Pin1, PinHigh);

	for (LedToggel = 0; LedToggel < 10; LedToggel++)
	{
		/* activate the led firing */
		DIO_VidSetPinValue(Port_D, Pin2, PinHigh);

		LCD_VidMoveCursor(1,0);
		LCD_VidPrintString(".....Firing.....");
		_delay_ms(750);
		/* deactivate the led firing */
		DIO_VidSetPinValue(Port_D, Pin2, PinLow);
		_delay_ms(750);
	}
	LCD_VidClear_Screen();
	_delay_ms(250);
	LCD_VidMoveCursor(0,0);
	LCD_VidPrintString("Temperature: ");

	/* deactivate the alarm */
	DIO_VidSetPinValue(Port_B, Pin1, PinLow);
}

void read_RFID(void)
{

	/* check if the data is available or not */
	if(UART_U8DataAvailable())
	{
		/* receive the string from UART */
		for(local_counter = 0 ; local_counter < 6 ; local_counter++)
		{
			RFID[local_counter] = UART_U8ReciveData();
		}

		if (local_counter == 6)
		{
			local_counter = 0;
			// Send RFID data to main program using a global variable or queue
			isRFIDDataAvailable = 1;
		}
	}
}


void __vector_13 (void) __attribute__((signal));

void __vector_13 (void)
{
	read_RFID();
}


