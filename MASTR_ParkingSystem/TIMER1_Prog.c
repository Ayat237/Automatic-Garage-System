/*
 * SERVO_MOTOR_Prog.c
 *
 *  Created on: Aug 29, 2023
 *      Author: Q
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER1_Private.h"
#include "TIMER1_Interface.h"

/* initialize timer1*/
void TIMER1_VidInit()
{
	/* non inverting mode FPWM (table 45 data sheet) */
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);

	/* setting waveform generation mode(table 14 data sheet) */
	CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1B_WGM13);

	/* SRT prescaler divided by 8 (table 48 data sheet) */
	TCCR1B &=0xF8; /*0b11111000*/
	TCCR1B |=0xF2; /*0b11111010*/
}

/* setting top value */
void TIMER1_VidSet_ICR_TopVlue(uint16 value)
{
	ICR1 = value;
}

void TIMER1_VidSet_OCR_CompMatch(uint16 value)
{
	OCR1A = value;
}


