/*
 * DIO_program.c
 *
 * Created: 11/3/2025 1:26:05 PM
 *  Author: hamza
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_register.h"


void DIO_voidSetPinDirection(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection)
{
	switch(copy_u8PinDirection)
	{
		case DIO_PIN_INPUT:
		switch(copy_u8PortId)
		{
			case DIO_PORTA: CLR_BIT(DDRA_REG, copy_u8PinId); break;
			case DIO_PORTB: CLR_BIT(DDRB_REG, copy_u8PinId); break;
			case DIO_PORTC: CLR_BIT(DDRC_REG, copy_u8PinId); break;
			case DIO_PORTD: CLR_BIT(DDRD_REG, copy_u8PinId); break;
		}
		break;
		
		case DIO_PIN_OUTPUT:
		switch(copy_u8PortId)
		{
			case DIO_PORTA: SET_BIT(DDRA_REG, copy_u8PinId); break;
			case DIO_PORTB: SET_BIT(DDRB_REG, copy_u8PinId); break;
			case DIO_PORTC: SET_BIT(DDRC_REG, copy_u8PinId); break;
			case DIO_PORTD: SET_BIT(DDRD_REG, copy_u8PinId); break;
		}
		break;
	}
}


void DIO_voidSetPinValue(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue)
{
	switch(copy_u8PinValue)
	{
		case DIO_PIN_LOW:
		switch(copy_u8PortId)
		{
			case DIO_PORTA: CLR_BIT(PORTA_REG, copy_u8PinId); break;
			case DIO_PORTB: CLR_BIT(PORTB_REG, copy_u8PinId); break;
			case DIO_PORTC: CLR_BIT(PORTC_REG, copy_u8PinId); break;
			case DIO_PORTD: CLR_BIT(PORTD_REG, copy_u8PinId); break;
		}
		break;
		
		case DIO_PIN_HIGH:
		switch(copy_u8PortId)
		{
			case DIO_PORTA: SET_BIT(PORTA_REG, copy_u8PinId); break;
			case DIO_PORTB: SET_BIT(PORTB_REG, copy_u8PinId); break;
			case DIO_PORTC: SET_BIT(PORTC_REG, copy_u8PinId); break;
			case DIO_PORTD: SET_BIT(PORTD_REG, copy_u8PinId); break;
		}
		break;
	}
}


void DIO_voidTogglePinValue(u8 copy_u8PortId, u8 copy_u8PinId)
{
	switch(copy_u8PortId)
	{
		case DIO_PORTA: TOG_BIT(PORTA_REG, copy_u8PinId); break;
		case DIO_PORTB: TOG_BIT(PORTB_REG, copy_u8PinId); break;
		case DIO_PORTC: TOG_BIT(PORTC_REG, copy_u8PinId); break;
		case DIO_PORTD: TOG_BIT(PORTD_REG, copy_u8PinId); break;
	}	
}


/*u8 DIO_u8GetPinValue(u8 copy_u8PortId, u8 copy_u8PinId)
{
	u8 local_u8PinValue;
	switch(copy_u8PortId)
	{
		case DIO_PORTA: local_u8PinValue = GET_BIT(PINA_REG, copy_u8PinId); break;
		case DIO_PORTB: local_u8PinValue = GET_BIT(PINB_REG, copy_u8PinId); break;
		case DIO_PORTC: local_u8PinValue = GET_BIT(PINC_REG, copy_u8PinId); break;
		case DIO_PORTD: local_u8PinValue = GET_BIT(PIND_REG, copy_u8PinId); break;
	}
	return local_u8PinValue;
}*/


void DIO_voidGetPinValue(u8 copy_u8PortId, u8 copy_u8PinId, u8* pu8PinValue)
{
	if((copy_u8PortId <= 3) && (copy_u8PinId <= 7) )
	{
		switch(copy_u8PortId)
		{
			case DIO_PORTA: *pu8PinValue = GET_BIT(PINA_REG, copy_u8PinId); break;
			case DIO_PORTB: *pu8PinValue = GET_BIT(PINB_REG, copy_u8PinId); break;
			case DIO_PORTC: *pu8PinValue = GET_BIT(PINC_REG, copy_u8PinId); break;
			case DIO_PORTD: *pu8PinValue = GET_BIT(PIND_REG, copy_u8PinId); break;
		}
	} 
	else
	{
		// return Error State
	}	
}


void DIO_voidActivePinInternalPUR(u8 copy_u8PortId, u8 copy_u8PinId)
{
	if((copy_u8PortId <= 3) && (copy_u8PinId <= 7))
	{
		switch(copy_u8PortId)
		{
			case DIO_PORTA: SET_BIT(PORTA_REG, copy_u8PinId); break;
			case DIO_PORTB: SET_BIT(PORTB_REG, copy_u8PinId); break;
			case DIO_PORTC: SET_BIT(PORTC_REG, copy_u8PinId); break;
			case DIO_PORTD: SET_BIT(PORTD_REG, copy_u8PinId); break;
		}
	}
	else
	{
		// return Error State
	}
}


/* Port APIs */
void DIO_voidSetPortDirection(u8 copy_u8PortId, u8 copy_u8PortDirection)
{
	switch(copy_u8PortDirection)
	{
		case DIO_PORT_INPUT:
		switch(copy_u8PortId)
		{
			case DIO_PORTA: DDRA_REG = 0x00; break;
			case DIO_PORTB: DDRB_REG = 0x00; break;
			case DIO_PORTC: DDRC_REG = 0x00; break;
			case DIO_PORTD: DDRD_REG = 0x00; break;
		}
		break;
		
		case DIO_PORT_OUTPUT:
		switch(copy_u8PortId)
		{
			case DIO_PORTA: DDRA_REG = 0xFF; break;
			case DIO_PORTB: DDRB_REG = 0xFF; break;
			case DIO_PORTC: DDRC_REG = 0xFF; break;
			case DIO_PORTD: DDRD_REG = 0xFF; break;
		}
		break;
	}
}


void DIO_voidSetPortValue(u8 copy_u8PortId, u8 copy_u8PortValue)
{
	switch(copy_u8PortId)
	{
		case DIO_PORTA: PORTA_REG = copy_u8PortValue; break;
		case DIO_PORTB: PORTB_REG = copy_u8PortValue; break;
		case DIO_PORTC: PORTC_REG = copy_u8PortValue; break;
		case DIO_PORTD: PORTD_REG = copy_u8PortValue; break;
	}
}