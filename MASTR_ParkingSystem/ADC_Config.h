/*
 * ADC_Config.h
 *
 *  Created on: Aug 24, 2023
 *      Author: Q
 */

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


//ADMUX referance section bit
#define ADMUX_REFS1    7   //use capacetor
#define ADMUX_REFS0    6   // use capcetor
#define ADMUX_ADLAR    5   // read right adjust

// ADC control and status register
#define ADCSRA_ADEN     7 // ADC enable
#define ADCSRA_ADSC     6 // ADC START TRAGRER
#define ADCSRA_ADTE     5 // ADC AUTO TRAGER INTERRUPT
#define ADCSRA_ADIF     4 // ADC INTTERUPT FLAG
#define ADCSRA_ADIE     3 // ADC INTERRUPT ENABLE
#define ADCSRA_ADPS2    2 // CLOCK (PRESCALER)
#define ADCSRA_ADPS1    1 // CLOCK (PRESCALER)
#define ADCSRA_ADPS0    0 // CLOCK (PRESCALER)

//Channel number
#define CANNEL_10        0b00000
#define CANNEL_11        0b00001
#define CANNEL_12        0b00010
#define CANNEL_13        0b00011
#define CANNEL_14        0b00100
#define CANNEL_15        0b00101
#define CANNEL_16        0b00110
#define CANNEL_17        0b00111

// Prescaller
#define PRE_SCALER_VALUE  128

#define IDLE       0
#define BUSY       1

#define SINGLE_CHANNEL_ASYNCH       0
#define CHAIN_ASYNCH                1

#endif /* ADC_CONFIG_H_ */
