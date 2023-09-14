/*
 * ADC_Interface.h
 *
 *  Created on: Aug 24, 2023
 *      Author: Q
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

//typedef enum
//{
//	CANNEL_10,
//	CANNEL_11,
//	CANNEL_12,
//	CANNEL_13,
//	CANNEL_14,
//	CANNEL_15,
//	CANNEL_16,
//	CANNEL_17
//}ChannelName;

typedef struct
{
	uint8* Channel;
	uint16* Result;
	uint8 Size;
	void (*NotficationFunc)(void);
}Chain_type;


void ADC_VidInit(void);
uint16 ADC_U16ReadChannelSyn(uint8 copy_Channel);
uint8 ADC_U8ReadChannelAsyn(uint8 copy_Channel , uint8* copy_Reading ,void(*copy_pvIntrFunc)(void));
uint8 ADC_U8ReadChainAsyn(Chain_type * copy_chain);

#endif /* ADC_INTERFACE_H_ */
