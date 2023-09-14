/*
 * UARET_Private.h
 * SWC: UART communication protocol
 * Created on: Aug 31, 2023
 * Author: Ayat Mohamed
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/* Data register (transmit and receiver buffer register)*/
#define UDR     *((volatile uint8*)0x2C)

/* control and status register A */
#define UCSRA   *((volatile uint8*)0x2B)

#define UCSRA_MPCM  0    /* Multi-processor communication mode */
#define UCSRA_U2X   1    /* double transmission speed */
#define UCSRA_PE    2    /* parity Error */
#define UCSRA_DOR   3    /* Data overRun */
#define UCSRA_FE    4    /* Frame Error */
#define UCSRA_UDRE  5    /* Data register empty */
#define UCSRA_TXC   6    /* Transmit complete */
#define UCSRA_RXC   7    /* Receive complete  */

/* control and status register B*/
#define UCSRB   *((volatile uint8*)0x2A)

#define UCSRB_TXB8  0    /* Transmit data bit 8 (bit no 9 if 9bit data used)*/
#define UCSRB_RXB8  1    /* Receive data bit 8 (bit no 9 if 9bit data used)**/
#define UCSRB_UCSZ2 2    /* Character data size (combined with UCSZ1 , UCSZ0)*/
#define UCSRB_RXEN  3    /* Receiver enable*/
#define UCSRB_TXEN  4    /* Transmitter enable*/
#define UCSRB_UDRIE 5    /* Data register empty interrupt enable */
#define UCSRB_TXCIE 6    /* TX complete interrupt enable*/
#define UCSRB_RXCIE 7    /* RX complete interrupt enable*/

/* control and status register B */
#define UCSRC   *((volatile uint8*)0x40)

/*  Baud Rate Registers – UBRRL and UBRRH */
#define UBRRL   *((volatile uint8*)0x29)

#define UCSRC_UCPOL 0  /* Clock Polarity used for synchronous */
#define UCSRC_UCSZ0 1  /* The UCSZ1 bits combined with the UCSZ2 bit in UCSRB*/
#define UCSRC_UCSZ1 2  /* The UCSZ0 bits combined with the UCSZ2 bit in UCSRB*/
#define UCSRC_USBS  3  /* Stop Bit Select */
#define UCSRC_UPM0  4  /* Parity Mode*/
#define UCSRC_UPM1  5  /* Parity Mode*/
#define UCSRC_UMSEL 6  /* Mode Select */
#define UCSRC_URSEL 7  /* Register Select*/




#endif /* UART_PRIVATE_H_ */
