/*
===================================================================================================
* Auther : Ayat Mohamed MOhamed 
* Object : DIO_Registter
* SWC : DIO_Registter.h
===================================================================================================
*/

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

// Access the addresses of ALL Registers in PORTA
#define DDRA   *((volatile uint8*)0x3A)
#define PORTA  *((volatile uint8*)0x3B)
#define PINA   *((volatile uint8*)0x39)

// Access the addresses of ALL Registers in PORTB
#define DDRB   *((volatile uint8*)0x37)
#define PORTB  *((volatile uint8*)0x38)
#define PINB   *((volatile uint8*)0x36)
// Access the addresses of ALL Registers in PORTC
#define DDRC   *((volatile uint8*)0x34)
#define PORTC  *((volatile uint8*)0x35)
#define PINC   *((volatile uint8*)0x33)

// Access the addresses of ALL Registers in PORTD
#define DDRD   *((volatile uint8*)0x31)
#define PORTD  *((volatile uint8*)0x32)
#define PIND   *((volatile uint8*)0x30)

#endif
