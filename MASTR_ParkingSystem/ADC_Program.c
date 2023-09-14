/*
 * ADC_Program.c
 *
 *  Created on: Aug 24, 2023
 *      Author: Q
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_INTERFACE.h"
#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Config.h"

/* global variable to carry the reading value of ADC*/
uint8* ADC_Reading = NULL;

/*global variable of struct to carry notification of complete start conversion  */
void (*ADC_pvCallBackFunc)(void) = NULL;

/*global variable of struct to carry the chain array */
static uint8* ADC_ChainChannelArr = NULL;

/*global variable of struct to carry number of channel */
static uint8* ADC_ChainSize;

/*global variable of struct to carry chain result */
static uint16* ADC_ChainResultArr = NULL;

/* global variable to carry conversion index */
static uint8 ADC_ChainConvesionIndex = 0;

/* global variable to check about source */
static uint8 ADC_ISRSource ;

uint8 ADC_BusyState = IDLE;

void ADC_VidInit(void)
{
	// INTERNAL REFERANCE VOLTAGE (5)V
	SET_BIT(ADMUX ,ADMUX_REFS0);
	CLEAR_BIT(ADMUX ,ADMUX_REFS1);

	// ACTIVE RIGHT ADJUST
	CLEAR_BIT(ADMUX ,ADMUX_ADLAR);

	// ADC CLOCK (PRESCALER)
	SET_BIT(ADCSRA ,ADCSRA_ADPS2);
	SET_BIT(ADCSRA ,ADCSRA_ADPS1);
	SET_BIT(ADCSRA ,ADCSRA_ADPS0);

	// ENABLE ADC
	SET_BIT(ADCSRA ,ADCSRA_ADEN);

}

// ADC using POLLING (synchronous)
uint16 ADC_U16ReadChannelSyn(uint8 copy_Channel)
{
	// clear the mux bit
	ADMUX &=0b11100000;

	// set the required change into the mux
	ADMUX |= copy_Channel;

	// start conversion
	SET_BIT(ADCSRA ,ADCSRA_ADSC);

	// polling (busy waiting) until the conversion complete flag is set
	while (GET_BIT(ADCSRA ,ADCSRA_ADIF));

	// clear the conversion complete flag --> set to 1
	SET_BIT(ADCSRA ,ADCSRA_ADIF);

	// return the conversion reading
	return ADCL_H;

}

// ADC using INTRRUPT (Asynchronous)
uint8 ADC_U8ReadChannelAsyn(uint8 copy_Channel , uint8* copy_Reading ,void(*copy_pvIntrFunc)(void))
{
	// variable to hold the error state
	uint8 Error_State = NO_ERROR_STATE;

	if(copy_Reading == NULL && copy_pvIntrFunc == NULL)
	{
		Error_State = NULLPOINTER;
	}
	else
	{
		/* make ADC busy in order not to work until being ideal*/
		ADC_BusyState = BUSY;

		/* make ISR source : single channel asynchronous*/
		ADC_ISRSource = SINGLE_CHANNEL_ASYNCH;

		// initialized the reading variable global
		ADC_Reading = copy_Reading;

		// initialized the call back function global
		ADC_pvCallBackFunc = copy_pvIntrFunc;

		// clear the mux bit
		ADMUX &=0b11100000;


		// set the required change into the mux
		ADMUX |= copy_Channel;

		// start conversion
		SET_BIT(ADCSRA ,ADCSRA_ADSC);

		// ENABLE THE INTTERUPT
		SET_BIT(ADCSRA ,ADCSRA_ADIE);
	}

	return Error_State;
}
/* ADC using INTRRUPT (Asynchronous) FOR CHAIN  */
uint8 ADC_U8ReadChainAsyn(Chain_type * copy_chain)
{
	uint8 Error_State = NO_ERROR_STATE;

	/*check Null pointer*/
	if(copy_chain == NULL)
	{
		Error_State = NULLPOINTER;
	}
	else
	{
		if(ADC_BusyState == IDLE)
		{
			/* make ADC busy in order not to work until being ideal*/
			ADC_BusyState = BUSY;

			/* make ISR source : chain asynchronous*/
			ADC_ISRSource = CHAIN_ASYNCH;

			/* initialize chain channel array*/
			ADC_ChainChannelArr = copy_chain->Channel;

			/* initialize chain Result array*/
			ADC_ChainResultArr = copy_chain->Result;

			/* initialize chain Size*/
			ADC_ChainSize = copy_chain->Size;

			/* initialize chain Notification function */
			ADC_pvCallBackFunc = copy_chain->NotficationFunc;

			/* initialize current conversion index  */
			ADC_ChainConvesionIndex = 0;

			// clear the mux bit (first five bit to select channel)
			ADMUX &= 0b11100000;
			/* select the first channel */
			ADMUX |= ADC_ChainChannelArr[ADC_ChainConvesionIndex];

			/* start conversion */
			SET_BIT(ADCSRA ,ADCSRA_ADSC);

			/*enable conversion complete interrupt */
			SET_BIT(ADCSRA ,ADCSRA_ADIE);
		}

	}

	return Error_State;
}

// ISR of ADC
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	if (ADC_ISRSource == SINGLE_CHANNEL_ASYNCH)
	{
		/* return the conversion reading */
		*ADC_Reading = ADCL_H;

		/* invoke the call back function */
		ADC_pvCallBackFunc();

		// disable ADC conversion complete  the interrupt
		CLEAR_BIT(ADCSRA ,ADCSRA_ADIE);
	}
	else if(ADC_ISRSource == CHAIN_ASYNCH)
	{
		/* read current conversion */
		ADC_ChainResultArr[ADC_ChainConvesionIndex] = ADCL_H;

		/* increment the index*/
		ADC_ChainConvesionIndex++;

		/* check the chain is finished or not */
		if(ADC_ChainConvesionIndex == ADC_ChainSize)
		{
			/* the chain is finished */
			/* make ADC idle */
			ADC_BusyState = IDLE;

			/* invoke the callback notification function */
			ADC_pvCallBackFunc();

			/* disable conversion complete interrupt*/
			CLEAR_BIT(ADCSRA ,ADCSRA_ADIE);

		}
		else
		{
			/* the chain is not finished */
			// clear the mux bit (first five bit to select channel)
			ADMUX &= 0b11100000;
			/* select the first channel */
			ADMUX |= ADC_ChainChannelArr[ADC_ChainConvesionIndex];

			/* start conversion */
			SET_BIT(ADCSRA ,ADCSRA_ADSC);

		}

	}

}


