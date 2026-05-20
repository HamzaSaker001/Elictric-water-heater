/*
 * LED_program.c
 *
 * Created: 11/24/2025
 *  Author: hamza
 *  Fixed : LED_voidOn / LED_voidOff were calling DIO_voidGetPinValue
 *          instead of DIO_voidSetPinValue.
 */

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LED_inteface.h"

void LED_voidInit(u8 copy_u8LedPort, u8 copy_u8LedPin)
{
    DIO_voidSetPinDirection(copy_u8LedPort, copy_u8LedPin, DIO_PIN_OUTPUT);
}

void LED_voidOn(u8 copy_u8LedPort, u8 copy_u8LedPin, u8 copy_u8LedConnectionType)
{
    switch (copy_u8LedConnectionType)
    {
        case LED_FORWARD_CONNECTION:
            DIO_voidSetPinValue(copy_u8LedPort, copy_u8LedPin, DIO_PIN_HIGH);
            break;

        case LED_REVERSE_CONNECTION:
            DIO_voidSetPinValue(copy_u8LedPort, copy_u8LedPin, DIO_PIN_LOW);
            break;

        default:
            break;
    }
}

void LED_voidOff(u8 copy_u8LedPort, u8 copy_u8LedPin, u8 copy_u8LedConnectionType)
{
    switch (copy_u8LedConnectionType)
    {
        case LED_FORWARD_CONNECTION:
            DIO_voidSetPinValue(copy_u8LedPort, copy_u8LedPin, DIO_PIN_LOW);
            break;

        case LED_REVERSE_CONNECTION:
            DIO_voidSetPinValue(copy_u8LedPort, copy_u8LedPin, DIO_PIN_HIGH);
            break;

        default:
            break;
    }
}

void LED_voidToggle(u8 copy_u8LedPort, u8 copy_u8LedPin)
{
    DIO_voidTogglePinValue(copy_u8LedPort, copy_u8LedPin);
}
