/*
 *  EX_INTERRUPT_Prog.c
 *  SWC: External inttrupt
 *  Created on: Aug 23, 2023
 *  Author: Ayat Mohamed
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "EX_INTERRUPT_Config.h"
#include "EX_INTERRUPT_Private.h"
#include "EX_INTERRUPT_Interface.h"

/*  Global pointer to function  to hold INT0 ISR address */
void (*EXTI_pvINT0Func)(void) = NULL;

/*  Global pointer to function  to hold INT1 ISR address */
void (*EXTI_pvINT1Func)(void) = NULL;

/*  Global pointer to function  to hold INT2 ISR address */
void (*EXTI_pvINT2Func)(void) = NULL;

void EXTINT_VidINT0_Init()
{
	// set sens control to any logical change
	SET_BIT(MCUCR ,MCUCR_ISC00);
	CLEAR_BIT(MCUCR ,MCUCR_ISC01);

	// peripheral interrupt enableINT0
	SET_BIT(GICR ,GICR_INT0);
}


void EXTINT_VidINT1_Init()
{
	// set sense control to any logical change
	SET_BIT(MCUCR ,MCUCR_ISC10);
	CLEAR_BIT(MCUCR ,MCUCR_ISC11);

	// peripheral interrupt enable INT1
	SET_BIT(GICR ,GICR_INT1);

}

void EXTINT_VidINT2_Init()
{
	// set sense control to rising edge
	SET_BIT(MCUCSR ,MCUCSR_INT2);

	// peripheral interrupt enable INT2
	SET_BIT(GICR ,GICR_INT2);
}

/* CALL BACK DFUNCTION OF INT0 */
uint8 EXTINT_U8INT0_CallBack(void(* Copy_PtrToFunc(void)))
{
	uint8 Error_State = NO_ERROR_STATE;
	if(Copy_PtrToFunc != NULL)
	{
		EXTI_pvINT0Func = Copy_PtrToFunc;
	}
	else
	{
		Error_State = NULLPOINTER;
	}
	return Error_State;
}


/* CALL BACK DFUNCTION OF INT1 */
uint8 EXTINT_U8INT1_CallBack(void(* Copy_PtrToFunc(void)))
{
	uint8 Error_State = NO_ERROR_STATE;
	if(Copy_PtrToFunc != NULL)
	{
		EXTI_pvINT1Func = Copy_PtrToFunc;
	}
	else
	{
		Error_State = NULLPOINTER;
	}
	return Error_State;
}

/* CALL BACK DFUNCTION OF INT2 */
uint8 EXTINT_U8INT2_CallBack(void(* Copy_PtrToFunc(void)))
{
	uint8 Error_State = NO_ERROR_STATE;
	if(Copy_PtrToFunc != NULL)
	{
		EXTI_pvINT2Func = Copy_PtrToFunc;
	}
	else
	{
		Error_State = NULLPOINTER;
	}
	return Error_State;
}

/* ISR function for INT0 */
void __vector_1 (void) __attribute__((signal));

void __vector_1 (void)
{
	EXTI_pvINT0Func();
}


/* ISR function for INT1 */
void __vector_2 (void) __attribute__((signal));

void __vector_2 (void)
{
	EXTI_pvINT1Func();
}


/* ISR function for INT2 */
void __vector_3 (void) __attribute__((signal));

void __vector_3 (void)
{
	EXTI_pvINT2Func();
}

