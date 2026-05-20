/*
 * SSD_program.c
 *
 * Created: 12/4/2025 4:25:37 PM
 *  Author: hamza
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

/*UTILES Lib*/
#include "STD_types.h"
#include "Bit_Math.h"

/*MCAL*/
#include "DIO_interface.h"

/*MAL*/
#include "SSD_interface.h"
#include "SSD_config.h"
#include "SSD_private.h"

static u8 PRV_u8Numbers[10] = {SSD_ZERO, SSD_ONE, SSD_TWO, SSD_THREE, SSD_FOUR, SSD_FIVE, SSD_SIX, SSD_SEVEN, SSD_EIGHT, SSD_NINE};

void SSD_voidInit(void)
{
	DIO_voidSetPortDirection(SSD_DATA_PORT, DIO_PORT_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT, SSD_E1_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT, SSD_E2_PIN, DIO_PIN_OUTPUT);
}


void SSD_voidDisplayOneDigitNumber(u8 copy_u8SSD_id, u8 copy_u8DesiredNumber)
{
	if(copy_u8DesiredNumber <= 9)
	{
		DIO_voidSetPortValue(SSD_DATA_PORT, PRV_u8Numbers[copy_u8DesiredNumber]);
		
		switch(copy_u8SSD_id)
		{
			case SSD_ID_1:
			DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_E1_PIN, DIO_PIN_HIGH);
			break;
			
			case SSD_ID_2:
			DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_E2_PIN, DIO_PIN_HIGH);
			break;
		}
	}
	else
	{
		// return Error State
	}
}


void SSD_voidDisplayTwoDigitNumber(u8 copy_u8DesiredNumber)
{
	if(copy_u8DesiredNumber <= 99)
	{
		u8 local_u8Tens = copy_u8DesiredNumber / 10;
		u8 local_u8Ones = copy_u8DesiredNumber % 10;
		
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_E1_PIN, DIO_PIN_LOW);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_E2_PIN, DIO_PIN_LOW);
		DIO_voidSetPortValue(SSD_DATA_PORT, PRV_u8Numbers[local_u8Tens]);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_E1_PIN, DIO_PIN_HIGH);
		_delay_ms(10);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_E1_PIN, DIO_PIN_LOW);
		DIO_voidSetPortValue(SSD_DATA_PORT, PRV_u8Numbers[local_u8Ones]);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_E2_PIN, DIO_PIN_HIGH);
		_delay_ms(10);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_E2_PIN, DIO_PIN_LOW);
	}
	else
	{
		//return Error State
	}
}

void SSD_voidClear(void)
{
	
	DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_E1_PIN, DIO_PIN_LOW);
	DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_E2_PIN, DIO_PIN_LOW);
	
	
	DIO_voidSetPortValue(SSD_DATA_PORT, 0x00);
}