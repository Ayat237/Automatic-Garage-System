/*
 * ADC_Private.h
 *
 *  Created on: Aug 24, 2023
 *      Author: Q
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

//ADMUX referance section bit
#define  ADMUX *((volatile uint8*)0x27)

// ADC control and status register
#define  ADCSRA *((volatile uint8*)0x26)

//read conversion value
#define  ADCL_H *((volatile uint16*)0x24)

#endif /* ADC_PRIVATE_H_ */
