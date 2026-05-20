/*
 * SWITCH_program.c
 *
 * Created: 11/24/2025 2:09:21 PM
 *  Author: hamza
 */ 
 
/*UTILES Lib*/
#include "STD_types.h"
#include "Bit_Math.h"

/*MCAL*/
#include "DIO_interface.h"

/*MAL*/
#include "SWITCH_interface.h"

void SWITCH_voidInit (u8 copy_u8SwitchPort, u8 copy_u8SwitchPin)
{
	DIO_voidSetPinDirection(copy_u8SwitchPort, copy_u8SwitchPin , DIO_PIN_INPUT);
}

void SWITCH_voidGetStatus (u8 copy_u8SwitchPort, u8 copy_u8SwitchPin, u8 copy_u8SwitchConnectionType, u8* pu8SwitchStatus)
{
	u8 Local_u8PinVal;
	switch (copy_u8SwitchConnectionType)
	{
	case SWITCH_FORWARD_CONNECTION:
	DIO_voidGetPinValue(copy_u8SwitchPort, copy_u8SwitchPin, &Local_u8PinVal);
	switch (Local_u8PinVal)
	{
	case DIO_PIN_HIGH:
	*pu8SwitchStatus = SWITCH_PRESSED;
	break;
	
	case DIO_PIN_LOW:
	*pu8SwitchStatus = SWITCH_NOT_PRESSED;
	break;	
	}
	break;
	
	case SWITCH_REVERSE_CONNECTION:
	DIO_voidGetPinValue(copy_u8SwitchPort, copy_u8SwitchPin, &Local_u8PinVal);
	switch (Local_u8PinVal)
	{
		case DIO_PIN_HIGH:
		*pu8SwitchStatus = SWITCH_NOT_PRESSED;
		break;
		
		case DIO_PIN_LOW:
		*pu8SwitchStatus = SWITCH_PRESSED;
		break;
	}
	break;
	
	}
}

