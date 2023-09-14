/*
 * TIMER_Private.h
 * SWC: TIMER
 * Created on: Aug 27, 2023
 * Author: Ayat Mohamed
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

/* Timer/counter0 register */
#define TCNT0        *((volatile uint8*)0x52)

/* Timer0 Control Register */
#define TCCR0        *((volatile uint8*)0x53)

/* Generation mode Bit0 normal or CTC */
#define TCCR0_WGM00   6

/* Generation mode Bit1 normal or CTC */
#define TCCR0_WGM01   3

/* Prescaler Bit 2*/
#define TCCR0_CS02    2

/* Prescaler Bit 1*/
#define TCCR0_CS01    1

/* Prescaler Bit 0*/
#define TCCR0_CS00    0

/* MODE OD CTC OR FAST MODE BIT 0*/
#define TCCR0_COM00   4

/* MODE OD CTC OR FAST MODE BIT 1*/
#define TCCR0_COM01   5

/* Output Compare Register0 */
#define OCR0        *((volatile uint8*)0x5C)

/* Timer Mask */
#define TIMSK       *((volatile uint8*)0x59)

/* Output Compare 0 Interrupt Enable */
#define TIMSK_OCIE0   1

/* Normal Mode Interrupt Enable */
#define TIMSK_TOIE0   0

#endif /* TIMER_PRIVATE_H_ */
