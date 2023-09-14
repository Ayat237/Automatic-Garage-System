/*
 * EX_INTERRUPT_Private.h
*  SWC: External inttrupt
 * Created on: Aug 23, 2023
 * Author: Ayat Mohamed
 */

#ifndef EX_INTERRUPT_PRIVATE_H_
#define EX_INTERRUPT_PRIVATE_H_

// GICR BITS ENABLE INTERRUPT INT1->BIT7 , INT1->BIT6 ,INT2->BIT5
#define GICR *((volatile uint8*)0x5B)

//GIFR READ FLAG
#define GIFR *((volatile uint8*)0x5A)

// MCUCR BITS INTERRUPT PIN INT1 OR INT2
#define MCUCR *((volatile uint8*)0x55)

// MCUCSR BITS INTERRUPT PIN INT2 BIT6-->ISC2
#define MCUCSR *((volatile uint8*)0x54)

#endif /* EX_INTERRUPT_PRIVATE_H_ */
