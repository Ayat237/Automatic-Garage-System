/*
 * TIMER1_Private.h
 *
 *  Created on: Aug 29, 2023
 *      Author: Q
 */

#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

/* TIMER 1A CONTROL REGISTER */
#define TCCR1A   *((volatile uint8*)0x4F)

#define TCCR1A_WGM10    0
#define TCCR1A_WGM11    1
#define TCCR1A_COM1A0   6
#define TCCR1A_COM1A1   7


/* TIMER 1B CONTROL REGISTER */
#define TCCR1B  *((volatile uint8*)0x4E)

#define TCCR1B_WGM12    3
#define TCCR1B_WGM13    4

/* ICR1 REGISTER */
#define ICR1 *((volatile uint16*)0x46)

/* OCR1A REGISTER */
#define OCR1A *((volatile uint16*)0x4A)

#endif /* TIMER1_PRIVATE_H_ */
