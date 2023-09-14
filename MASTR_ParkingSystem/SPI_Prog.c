/*
 * SPI_Prog.c
 *
 *  Created on: Sep 3, 2023
 *      Author: Q
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SPI_Private.h"
#include "SPI_Interface.h"


/* initialize master */
void SPI_VidMaterInit(ClkRate_type copy_Prescaler,ClkPhase_type copy_CPHA ,ClkPolarity_type copy_CLOP)
{
	/* Master initialization */
	SET_BIT(SPCR,SPCR_MSTR);

	/* clock polarity */
	switch(copy_CLOP)
	{
	case CPOL0:
		CLEAR_BIT(SPCR,SPCR_CPOL);
		break;
	case CPOL1:
		SET_BIT(SPCR,SPCR_CPOL);
		break;
	}

	/* clock phase */
	switch(copy_CPHA)
	{
	case CPHAS0:
		CLEAR_BIT(SPCR,SPCR_CPHA);
		break;
	case CPHAS1:
		SET_BIT(SPCR,SPCR_CPHA);
		break;
	}

	/* Clock prescaler /16*/
	switch(copy_Prescaler)
	{
	case Fosc_4:
		CLEAR_BIT(SPCR,SPCR_SPR0);
		CLEAR_BIT(SPCR,SPCR_SPR1);
		CLEAR_BIT(SPSR,SPSR_SPI2X);
		break;
	case Fosc_16:
		SET_BIT(SPCR,SPCR_SPR0);
		CLEAR_BIT(SPCR,SPCR_SPR1);
		CLEAR_BIT(SPSR,SPSR_SPI2X);
		break;
	case Fosc_64:
		CLEAR_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPCR,SPCR_SPR1);
		CLEAR_BIT(SPSR,SPSR_SPI2X);
		break;
	case Fosc_128:
		SET_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPCR,SPCR_SPR1);
		CLEAR_BIT(SPSR,SPSR_SPI2X);
		break;
	case Fosc_2:
		CLEAR_BIT(SPCR,SPCR_SPR0);
		CLEAR_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPSR,SPSR_SPI2X);
		break;
	case Fosc_8:
		SET_BIT(SPCR,SPCR_SPR0);
		CLEAR_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPSR,SPSR_SPI2X);
		break;
	case Fosc_32:
		CLEAR_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPSR,SPSR_SPI2X);
		break;
	case FoscDouble_64:
		SET_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPSR,SPSR_SPI2X);
		break;
	}

	/* Enable SPI */
	SET_BIT(SPCR,SPCR_SPE);
}

/* initialize slave */
void SPI_VidSlaveInit(ClkPhase_type copy_CPHA ,ClkPolarity_type copy_CLOP)
{
	/* Slave initialization to prevent the to be low */
	CLEAR_BIT(SPCR,SPCR_MSTR);

	/* clock polarity */
	switch(copy_CLOP)
	{
	case CPOL0:
		CLEAR_BIT(SPCR,SPCR_CPOL);
		break;
	case CPOL1:
		SET_BIT(SPCR,SPCR_CPOL);
		break;
	}

	/* clock phase */
	switch(copy_CPHA)
	{
	case CPHAS0:
		CLEAR_BIT(SPCR,SPCR_CPHA);
		break;
	case CPHAS1:
		SET_BIT(SPCR,SPCR_CPHA);
		break;
	}

	/* Enable SPI */
	SET_BIT(SPCR,SPCR_SPE);
}

/* transmit and receive at the same time */
uint8 SPI_TransReceive(uint8 copy_data)
{

	/* Send the data */
	SPDR = copy_data;

	/* wait until  transfer complete */
    while(GET_BIT(SPSR,SPSR_SPIF)== 0);
    /* after the tranfer comlete ,return the value of SPDR after update */
    return SPDR;
}


