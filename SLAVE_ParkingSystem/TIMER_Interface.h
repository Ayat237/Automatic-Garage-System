/*
 * TIMER_Interface.h
 * SWC: TIMER
 * Created on: Aug 27, 2023
 * Author: Ayat Mohamed
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

/* select mode of Timer0 */
typedef enum
{
	TIMER0_NORMAL_MODE ,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE
}et_TIMER0MODE;

/* select presacler of Timer0 */
typedef enum
{
	NO_Clock_Source= 0,
	NO_Prescaling,
	CLK_8_Prescaler,
	CLK_64_Prescaler,
	CLK_256_Prescaler,
	CLK_1024_Prescaler,
	EXT_CLK_FallingEdge,
	EXT_CLK_RisingEdge
}et_TIMER0PRESCALLER;

typedef enum
{
	NORMAL,
	COMP_CTC
}INT_ENABLE;

typedef enum
{
	Normal_Operation,
	Reserved_OR_Toggle,
	NonInverting_OR_ClearOC0,
	Inverting_OR_SetOC0
}et_FastPWM;

/* initialization of TIMER0 */
void TIMER0_VidInit(et_TIMER0MODE mode , et_TIMER0PRESCALLER prescaler);

/* Enable interrupt of TIMER0 */
void TIMER0_Interrupt_Enable(INT_ENABLE Enable_Mode);

/* Disable interrupt of TIMER0 */
void TIMER0_Interrupt_Disable(INT_ENABLE Enable_Mode);

void TIMER0_VidSetCompMatchValue(uint8 copy_value);

void TIMER0_CompareOutputMode(et_FastPWM Mode);

void TIMER0_SetCallBack(void (*Copy_CallBackFunc)(void));

#endif /* TIMER_INTERFACE_H_ */
