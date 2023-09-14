/*
 * SPI_Private.h
 *
 *  Created on: Sep 3, 2023
 *      Author: Q
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

/* SPI Control Register */
#define SPCR   *((volatile uint8*)0x2D)

#define SPCR_SPIE  7    /* SPI Interrupt Enable */
#define SPCR_SPE   6    /* SPI Enable */
#define SPCR_DORD  5    /* Data Order */
#define SPCR_MSTR  4    /* Master/Slave Select */
#define SPCR_CPOL  3    /* Clock Polarity */
#define SPCR_CPHA  2    /* Clock Phase */
#define SPCR_SPR1  1    /* SPI Clock Rate Select 1 (Prescaler bit 1) */
#define SPCR_SPR0  0    /* SPI Clock Rate Select 0 (Prescaler bit 0)*/

/* SPI Status Register */
#define SPSR   *((volatile uint8*)0x2E)

#define SPSR_SPIF  7    /* SPI Interrupt Flag */
#define SPSR_WCOL  6    /* Write COLlision Flag */
#define SPSR_SPI2X 0    /* Double SPI Speed Bit (Prescaler bit 2) */

/* SPI Data Register */
#define SPDR   *((volatile uint8*)0x2F)

#endif /* SPI_PRIVATE_H_ */
