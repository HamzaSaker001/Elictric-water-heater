/*
 * LM35_program.c
 *
 * Created: 2/25/2026 2:28:28 PM
 *  Author: hamza
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "LM35_interface.h"
#include "LM35_config.h"

void LM35_voidInit(void)
{
    /* Initialize ADC module (MCAL) */
    ADC_voidInit(ADC_REFERENCE_AVCC);
}

void LM35_voidGetTemperature(u8* pu8Temperature)
{
    u16 local_u16ADCValue;

    if(pu8Temperature != NULL)
    {
        /* Read ADC value from configured channel */
        ADC_voidGetDigitalValue(LM35_ADC_CHANNEL,&local_u16ADCValue);

        /* Convert ADC value to temperature in °C
           LM35 gives 10mV per °C, ADC resolution = 10-bit (0-1023) */
        *pu8Temperature = (u8)((local_u16ADCValue * LM35_VREF_MV) / 1024 /10);
    }
}