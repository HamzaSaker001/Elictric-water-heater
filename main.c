/*
 * main.c
 *
 * Created: 2/27/2026 1:40:04 PM
 *  Author: hamza
 */ 


#include "STD_TYPES.h"
#include "GI_interface.h"
#include "EWH_interface.h"

int main(void)
{
	/* 1. Initialise all EWH hardware (ADC, I2C, EEPROM, Timer config) */
	EWH_voidInit();

	/* 2. Enable global interrupts – TMR0 ISR can now fire             */
	GI_voidEnable();

	/* 3. Super-loop                                                    */
	while (1)
	{
		EWH_voidTask();
	}

	return 0;
}
