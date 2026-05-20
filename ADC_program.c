/*
 * ADC_program.c
 *
 * Created: 2/9/2026 8:34:25 PM
 *  Author: hamza
 */ 

/*UTILES_LIB*/
#include "Bit_Math.h"
#include "STD_types.h"

/*MCAL*/
#include "ADC_interface.h"
#include "ADC_register.h"

void ADC_voidInit(ADC_refVoltage_t copy_tRefVol)
{
	switch(copy_tRefVol)
	{
		case ADC_REFERENCE_AVCC :
		CLR_BIT(ADMUX_REG, REFS1);
		SET_BIT(ADMUX_REG, REFS0);
		break;
		
		case ADC_REFERENCE_AREF :
		CLR_BIT(ADMUX_REG, REFS1);
		CLR_BIT(ADMUX_REG, REFS0);
		break;
		
		case ADC_REFERENCE_INTERNAL :
		SET_BIT(ADMUX_REG, REFS1);
		SET_BIT(ADMUX_REG, REFS0);
		break;
	}
	/*select right adjustment*/
	CLR_BIT(ADMUX_REG, ADLAR);
	
	/*ADC anable*/
	SET_BIT(ADCSRA_REG, ADEN);
	
	/*Single conversion mode*/
	CLR_BIT(ADCSRA_REG, ADATE);
	
	/*Disable ADC Interrupt*/
	CLR_BIT(ADCSRA_REG, ADIE);
	
	/*Prescaler 128 for 16MHZ (125 KHZ)*/
	SET_BIT(ADCSRA_REG,  ADPS2);
	SET_BIT(ADCSRA_REG,  ADPS1);
	SET_BIT(ADCSRA_REG,  ADPS0);
}

void ADC_voidGetDigitalValue(ADC_ChannelId_t copy_tChannelId, u16* pu16DigitalValue)
{
	if ((copy_tChannelId<32 ) && (pu16DigitalValue != NULL))
	{
		/*Clear ADMUX Channel Bits*/
		ADMUX_REG &= 0xE0;
		
		/*Select Channel Number*/
		ADMUX_REG |= copy_tChannelId;
		
		/*Start Converting*/
		SET_BIT(ADCSRA_REG, ADSC);
		
		/*Busy Wait For ADC Flag*/
		while(0==GET_BIT(ADCSRA_REG, ADIF));
		
		/*Clear ADC Flag (WROC >> Write One To Clear)*/
		SET_BIT(ADCSRA_REG, ADIF);
		
		/*Pass Out ADC Data*/
		*pu16DigitalValue = ADC_u16_REG;
	} 
	else
	{
		//return Error state
	}
}
