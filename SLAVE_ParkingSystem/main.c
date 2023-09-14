/*
 * main.c
 *
 *  Created on: Sep 10, 2023
 *      Author: Ayat Mohamed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <string.h>
#include "DIO_PRIVATE.h"
#include "DIO_INTERFACE.h"
#include "SPI_Interface.h"
#include "UART_Private.h"
#include "UART_Interface.h"
#include "LCD_Interface.h"
#include "TIMER1_Private.h"
#include "TIMER1_Interface.h"
#include "EX_INTERRUPT_Interface.h"
#include "GIE_Interface.h"
#include <util/delay.h>

#define BUZZER   Pin0
#define DEFAULT  0xFF
#define BTN1 (PIND&0x08)
#define BTN2 (PIND&0x10)

uint8 RFID[15];
uint8 local_counter = 0;
uint8 counter=0;
uint8 local_counterID = 0;
uint8 local_ID = 0;
uint8 RFID_NO1[] = {"AFG345"};
uint8 RFID_NO2[] = {"ACD128"};
uint8 RFID_NO3[] = {"DFY567"};
uint8 RFID_NO4[] = {"AHG457"};
uint8 RFID_NO5[] = {"FHK798"};

void initialize_pins(void);
void initialize_peripherals(void);
void lighting_control(void);
void Gate_control(void);

int main ()
{

	initialize_pins();

	initialize_peripherals();

	_delay_ms(250);
	LCD_VidPrintString("CAR_ID: ");
	_delay_ms(250);
	LCD_VidMoveCursor(1,0);
	LCD_VidPrintString("NO_OF_CARS: ");

	while(1)
	{
		/* control the lighting of garage */
		lighting_control();

		/* control the gate of garage */
		if((counter>=0)&&(counter<=5))
		{
			if(BTN1==PinLow)
			{
				if(counter<6)
				{
					while(BTN1==PinLow)
					{
						DIO_VidSetPinValue(Port_D, Pin6 ,PinHigh);

						/* receive data from SPI */
						for(local_counter = 0 ; local_counter <6 ; local_counter++)
						{
							RFID[local_counter]= SPI_TransReceive(DEFAULT);
						}

						/* check on data receiving */
						if(local_counter == 6)
						{
							for(local_counterID = 0 ;RFID_NO1[local_counterID] != '\0'; local_counterID++)
							{

								if(RFID[local_counterID] == RFID_NO1[local_counterID])
								{
									local_ID ++;
								}
							}

							if(local_ID == 6)
							{
								Gate_control();
							}
							else
							{
								local_ID = 0;
								for(local_counterID = 0 ;RFID_NO2[local_counterID] != '\0'; local_counterID++)
								{

									if(RFID[local_counterID] == RFID_NO2[local_counterID])
									{
										local_ID ++;
									}
								}
								if(local_ID == 6)
								{
									Gate_control();

								}
								else
								{
									local_ID = 0;
									for(local_counterID = 0 ;RFID_NO3[local_counterID] != '\0'; local_counterID++)
									{

										if(RFID[local_counterID] == RFID_NO3[local_counterID])
										{
											local_ID ++;
										}
									}
									if(local_ID == 6)
									{
										Gate_control();
									}
									else
									{
										local_ID = 0;
										for(local_counterID = 0 ;RFID_NO4[local_counterID] != '\0'; local_counterID++)
										{

											if(RFID[local_counterID] == RFID_NO4[local_counterID])
											{
												local_ID ++;
											}
										}
										if(local_ID == 6)
										{
											Gate_control();

										}
										else
										{
											local_ID = 0;
											for(local_counterID = 0 ;RFID_NO5[local_counterID] != '\0'; local_counterID++)
											{

												if(RFID[local_counterID] == RFID_NO5[local_counterID])
												{
													local_ID ++;
												}
											}
											if(local_ID == 6)
											{
												Gate_control();
											}
											else
											{
												UART_VidSendDataString("Access Not Allowed");
												UART_VidSendData('\r');
												_delay_ms(250);
												LCD_VidMoveCursor(0,7);
												LCD_VidPrintString("Not Exist");
												_delay_ms(5000);
												LCD_VidSendCommand(0x01);
												_delay_ms(250);
												LCD_VidPrintString("CAR_ID: ");
												_delay_ms(250);
												LCD_VidMoveCursor(1,0);
												LCD_VidPrintString("NO_OF_CARS: ");
												DIO_VidSetPinValue(Port_B,Pin0,PinHigh);
												_delay_ms(5000);
												DIO_VidSetPinValue(Port_B,Pin0,PinLow);
											}
										}
									}
								}
							}
						}
					}
					DIO_VidSetPinValue(Port_D, Pin6 ,PinLow);
					_delay_ms(1000);
					TIMER1_VidSet_OCR_CompMatch(250);
				}
				else
				{
					counter=5;
				}
			}
			else if(BTN2==PinLow)
			{
				if(counter>=1){
					while(BTN2==PinLow)
					{
						DIO_VidSetPinValue(Port_D, Pin7 ,PinHigh);
						TIMER1_VidSet_OCR_CompMatch(0);
						_delay_ms(5000);

						TIMER1_VidSet_OCR_CompMatch(750);
						_delay_ms(10000);

					}
					DIO_VidSetPinValue(Port_D, Pin7 ,PinLow);
					_delay_ms(1000);
					TIMER1_VidSet_OCR_CompMatch(250);
					--counter;
				}
				else
				{
					counter=0;
				}

			}
		}
		/*print the no of cares*/
		LCD_VidMoveCursor(1,12);
		LCD_VidPrintNumber(counter);
	}
}

void initialize_pins(void)
{
	/*set pin direction of SLAVE */
	DIO_VidSetPinDirection(Port_B,Pin4,Input);    	/* SS : input (floating)for slave */
	DIO_VidSetPinDirection(Port_B,Pin5,Input);  	/* MOSI : master output slave input */
	DIO_VidSetPinDirection(Port_B,Pin6,Output);     /* MISO : master input slave output */
	DIO_VidSetPinDirection(Port_B,Pin7,Input);      /* SCK : Input for slave */

	/* set pin direction of TX */
	DIO_VidSetPinDirection(Port_D,Pin1,Output);

	/* set pin direction of IR Sensors */
	DIO_VidSetPinDirection(Port_D,Pin3,Input);
	DIO_VidSetPinDirection(Port_D,Pin4,Input);

	DIO_VidSetPinValue(Port_D, Pin3 ,PinHigh);
	DIO_VidSetPinValue(Port_D, Pin4 ,PinHigh);


	/* set pin direction of INPUT AND OUTPUT LED */
	DIO_VidSetPinDirection(Port_D ,Pin6,Output);
	DIO_VidSetPinDirection(Port_D ,Pin7,Output);
	DIO_VidSetPinValue(Port_D, Pin6 ,PinLow);
	DIO_VidSetPinValue(Port_D, Pin7 ,PinLow);

	/* set pin direction of LCD */
	DIO_VidSetPortDirection(Port_A , Output);
	DIO_VidSetPinDirection(Port_C, Pin0 , Output);
	DIO_VidSetPinDirection(Port_C, Pin1 , Output);
	DIO_VidSetPinDirection(Port_C, Pin2 , Output);

	/* set pin direction of servo motor */
	DIO_VidSetPinDirection(Port_D ,Pin5,Output);

	/* set pin direction of Buzzer */
	DIO_VidSetPinDirection(Port_B ,Pin0,Output);


	/* set pin direction of 4 Leds */
	DIO_VidSetPinDirection(Port_C, Pin3 , Output);
	DIO_VidSetPinDirection(Port_C, Pin4 , Output);
	DIO_VidSetPinDirection(Port_C, Pin5 , Output);
	DIO_VidSetPinDirection(Port_C, Pin6 , Output);
}
void initialize_peripherals(void)
{

	/* initialize slave */
	SPI_VidSlaveInit(CPHAS0,CPOL0);

	/* initialize UART */
	UART_VidInit(STOP_1BIT,DISABLED,DATA_8BIT);

	/* initialize LCD */
	LCD_Vid_Init();

	/* servo motor initialize */
	TIMER1_VidInit();
	TIMER1_VidSet_ICR_TopVlue(19999);
}

void lighting_control(void)
{
	if(counter == 0)
	{
		/* off all leds */
		DIO_VidSetPinValue(Port_C, Pin3 ,PinLow);
		DIO_VidSetPinValue(Port_C, Pin4 ,PinLow);
		DIO_VidSetPinValue(Port_C, Pin5 ,PinLow);
		DIO_VidSetPinValue(Port_C, Pin6 ,PinLow);
	}
	else
	{
		/* on all leds */
		DIO_VidSetPinValue(Port_C, Pin3 ,PinHigh);
		DIO_VidSetPinValue(Port_C, Pin4 ,PinHigh);
		DIO_VidSetPinValue(Port_C, Pin5 ,PinHigh);
		DIO_VidSetPinValue(Port_C, Pin6 ,PinHigh);
	}
}

void Gate_control(void)
{
	UART_VidSendDataString("Access Allowed");
	UART_VidSendData('\r');
	_delay_ms(250);
	LCD_VidMoveCursor(0,8);
	LCD_VidPrintString(RFID);
	TIMER1_VidSet_OCR_CompMatch(0);
	_delay_ms(5000);

	TIMER1_VidSet_OCR_CompMatch(750);

	LCD_VidMoveCursor(1,0);
	LCD_VidPrintString(".....Opening.....");
	_delay_ms(5000);
	LCD_VidClear_Screen();
	_delay_ms(250);
	LCD_VidPrintString("CAR_ID: ");
	_delay_ms(250);
	LCD_VidMoveCursor(1,0);
	LCD_VidPrintString("NO_OF_CARS: ");
	counter++;
	local_ID = 0;
}

