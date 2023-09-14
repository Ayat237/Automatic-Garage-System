/*
 * TIMER_Prog.c
 * SWC: TIMER
 * Created on: Aug 27, 2023
 * Author: Ayat Mohamed
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_Private.h"
#include "TIMER_Interface.h"

/* Global call back notification function */
static void (*TIMER0_pvCallBackFun)(void)= NULL;

/* Description : initialization of TIMER0
   Input : Timer mode and clock prescaler
   output : select mode and prescaler
 */
void TIMER0_VidInit(et_TIMER0MODE mode , et_TIMER0PRESCALLER prescaler)
{
	switch (mode)
	{
	case TIMER0_NORMAL_MODE :
		CLEAR_BIT(TCCR0,TCCR0_WGM00);
		CLEAR_BIT(TCCR0,TCCR0_WGM01);
		break;

	case TIMER0_PHASECORRECT_MODE :
		SET_BIT(TCCR0,TCCR0_WGM00);
		CLEAR_BIT(TCCR0,TCCR0_WGM01);
		break;

	case TIMER0_CTC_MODE :
		CLEAR_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);
		break;

	case TIMER0_FASTPWM_MODE :
		SET_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);
		break;
	}
	/* Prescaler */
	TCCR0 |= 0xF8; //0b11111000 make the first 3bit = 0
	TCCR0 |= prescaler;
}

/* Description : Choose the compare output mode
                 if mode is CTC or FastPWM
   Input : Mode
   output : select output compare mode of CTC or PWM.
 */

void TIMER0_CompareOutputMode(et_FastPWM Mode)
{
	switch(Mode)
	{
	/* COM01   COM00
	     0       0
	   Normal Operation In Fast-PWM OR CTC. */
	case Normal_Operation:
		CLEAR_BIT(TCCR0,TCCR0_COM00);
		CLEAR_BIT(TCCR0,TCCR0_COM01);
		break;
		/* COM01   COM00
		 0       1
	   Reserved In Fast-PWM And Toggle In CTC. */
	case Reserved_OR_Toggle:
		SET_BIT(TCCR0,TCCR0_COM00);
		CLEAR_BIT(TCCR0,TCCR0_COM01);
		break;
		/* COM01   COM00
		     1       0
	       Non Inverting In Fast-PWM And Clear OC0 On Compare In CTC. */
	case NonInverting_OR_ClearOC0:
		CLEAR_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		break;
		/* COM01   COM00
			 1       1
		   Inverting In Fast-PWM And Set OC0 On Compare In CTC. */
	case Inverting_OR_SetOC0:
		SET_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		break;
	}

}


/* Description :  Enable interrupt of TIMER0
   Input : void
   output : Enable the normal mode interrupt enable */
void TIMER0_Interrupt_Enable(INT_ENABLE Enable_Mode)
{
	if(Enable_Mode == NORMAL)
	{
		SET_BIT(TIMSK, TIMSK_TOIE0);
	}
	else if(Enable_Mode == COMP_CTC)
	{
		SET_BIT(TIMSK, TIMSK_OCIE0);
	}

}


/* Description : Disable interrupt of TIMER0
   Input : void
   output : Disable the normal mode interrupt enable */
void TIMER0_Interrupt_Disable(INT_ENABLE Enable_Mode)
{
	if(Enable_Mode == NORMAL)
	{
		CLEAR_BIT(TIMSK, TIMSK_TOIE0);
	}
	else if(Enable_Mode == COMP_CTC)
	{
		CLEAR_BIT(TIMSK, TIMSK_OCIE0);
	}
}


/* Set value to OCR0 */
void TIMER0_VidSetCompMatchValue(uint8 copy_value)
{
	OCR0 = copy_value;
}

void TIMER0_SetCallBack(void (*Copy_CallBackFunc)(void))
{
	TIMER0_pvCallBackFun = Copy_CallBackFunc;
}

/* ISR function for INT1 */
void __vector_10 (void) __attribute__((signal));

void __vector_10 (void)
{
	TIMER0_pvCallBackFun();
}
