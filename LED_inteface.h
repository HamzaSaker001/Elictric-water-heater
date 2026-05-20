/*
 * LED_inteface.h
 *
 * Created: 11/24/2025 1:33:40 PM
 *  Author: hamza
 */ 


#ifndef LED_INTEFACE_H_
#define LED_INTEFACE_H_


/*Macros for Led Connection type*/
#define LED_FORWARD_CONNECTION   0
#define LED_REVERSE_CONNECTION   1

           /*****************************************************ABIs Prototypes************************************************/

void LED_voidInit  (u8 copy_u8LedPort ,u8 copy_u8LedPin);
void LED_voidOn    (u8 copy_u8LedPort ,u8 copy_u8LedPin , u8 copy_u8LedConnectionType);
void LED_voidOff   (u8 copy_u8LedPort ,u8 copy_u8LedPin , u8 copy_u8LedConnectionType);
void LED_voidToggle  (u8 copy_u8LedPort ,u8 copy_u8LedPin);


#endif /* LED_INTEFACE_H_ */