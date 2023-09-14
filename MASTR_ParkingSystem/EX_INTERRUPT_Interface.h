/*
 * EX_INTERRUPT_Interface.h
*  SWC: External inttrupt
 * Created on: Aug 23, 2023
 * Author: Ayat Mohamed
 */

#ifndef EX_INTERRUPT_INTERFACE_H_
#define EX_INTERRUPT_INTERFACE_H_

// set sense control to any logical change
void EXTINT_VidINT0_Init();

// set sense control to rising edge
void EXTINT_VidINT1_Init();

// set sense control to falling edge
void EXTINT_VidINT2_Init();

/* CALL BACK DFUNCTION OF INT0 */
uint8 EXTINT_U8INT0_CallBack(void(* Copy_PtrToFunc(void)));

/* CALL BACK DFUNCTION OF INT1 */
uint8 EXTINT_U8INT1_CallBack(void(* Copy_PtrToFunc(void)));

/* CALL BACK DFUNCTION OF INT2 */
uint8 EXTINT_U8INT2_CallBack(void(* Copy_PtrToFunc(void)));

#endif /* EX_INTERRUPT_INTERFACE_H_ */
