 /*
 * _3DCH_program.c
 *
 * Created: 2/27/2026 2:25:39 PM
 *  Author: hamza
 */ 

/*UTILES Lib*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAL*/
#include "DIO_interface.h"

/* HAL */
#include "DCH_inteface.h"
#include "LM35_interface.h"
#include "DCH_config.h"


static u8 DCH_u8SetTemp = 0;
static u8 DCH_u8CurrentTemp = 0;

void DCH_voidInit(void)
{
	LM35_voidInit();                        
	DIO_voidSetPinDirection(DCH_PORT, DCH_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinValue(DCH_PORT, DCH_PIN, DIO_PIN_LOW);
}

void DCH_voidSetTemperature(u8 Copy_u8Temp)
{
	if(Copy_u8Temp <= DCH_MAX_TEMP)
	{
		DCH_u8SetTemp = Copy_u8Temp;
	}
}

void DCH_voidUpdate(void)
{
	LM35_voidGetTemperature(&DCH_u8CurrentTemp);

	if(DCH_u8CurrentTemp < (DCH_u8SetTemp - DCH_HYSTERESIS))
	{
		DIO_voidSetPinValue(DCH_PORT, DCH_PIN, DIO_PIN_HIGH);  //Heater On
	}
	else if(DCH_u8CurrentTemp > (DCH_u8SetTemp + DCH_HYSTERESIS))
	{
		DIO_voidSetPinValue(DCH_PORT, DCH_PIN, DIO_PIN_LOW);   //Heater Off
	}
}

void DCH_voidStop(void)
{
	DIO_voidSetPinValue(DCH_PORT, DCH_PIN, DIO_PIN_LOW); // ????? ??????
}