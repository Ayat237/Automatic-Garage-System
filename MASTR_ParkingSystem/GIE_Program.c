/*
 * GIE_Program.c
 *  SWC: External inttrupt
 * Created on: Aug 23, 2023
 * Author: Ayat Mohamed
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "GIE_Config.h"
#include "GIE_Private.h"
#include "GIE_Interface.h"

//enable the interrupt
void GIE_VidEnable()
{
	SET_BIT(SREG,SREF_I);
}

//disable the interrupt
void GIE_VidDisable()
{
	CLEAR_BIT(SREG,SREF_I);
}
