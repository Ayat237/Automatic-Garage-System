/*
 * SPI_Interface.h
 *
 *  Created on: Sep 3, 2023
 *      Author: Q
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

typedef enum
{
	CPOL0,  /* leading -> rising  or  trailing -> falling */
	CPOL1   /* leading -> falling or  trailing -> rising  */

}ClkPolarity_type;


typedef enum
{
	CPHAS0,  /* leading -> sample  or  trailing -> setup */
	CPHAS1   /* leading -> setup or  trailing -> sample  */

}ClkPhase_type;


typedef enum
{
	Fosc_4,
	Fosc_16,
	Fosc_64,
	Fosc_128,
	Fosc_2,
	Fosc_8,
	Fosc_32,
	FoscDouble_64

}ClkRate_type;



/* initialize master */
void SPI_VidMaterInit(ClkRate_type copy_Prescaler,ClkPhase_type copy_CPHA ,ClkPolarity_type copy_CLOP);

/* initialize slave */
void SPI_VidSlaveInit(ClkPhase_type copy_CPHA ,ClkPolarity_type copy_CLOP);

/* transmit and receive at the same time */
uint8 SPI_TransReceive(uint8 copy_data);

#endif /* SPI_INTERFACE_H_ */
