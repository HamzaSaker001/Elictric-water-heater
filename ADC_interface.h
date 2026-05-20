/*
 * ADC_interface.h
 *
 * Created: 2/9/2026 8:34:52 PM
 *  Author: hamza
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/*enum for reference voltage*/
typedef enum
{
	ADC_REFERENCE_AVCC,
	ADC_REFERENCE_AREF,
	ADC_REFERENCE_INTERNAL	
}ADC_refVoltage_t;

/*enum for channel number as single ended input*/
typedef enum
{
	ADC_CHANNEL_0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7
}ADC_ChannelId_t;

      /*********************************************** APIs prototypes ****************************************/
	  
void ADC_voidInit(ADC_refVoltage_t copy_tRefVol);
void ADC_voidGetDigitalValue(ADC_ChannelId_t copy_tChannelId, u16* pu16DigitalValue);




#endif /* ADC_INTERFACE_H_ */