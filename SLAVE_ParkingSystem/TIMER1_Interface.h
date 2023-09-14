/*
 * SERVO_MOTOR_Interface.h
 *
 *  Created on: Aug 29, 2023
 *      Author: Q
 */

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

void TIMER1_VidInit();

void TIMER1_VidSet_ICR_TopVlue(uint16 value);

void TIMER1_VidSet_OCR_CompMatch(uint16 value);
#endif /* TIMER1_INTERFACE_H_ */
