/*
 * SWITCH_interface.h
 *
 * Created: 11/24/2025 2:09:52 PM
 *  Author: hamza
 */ 


#ifndef SWITCH_INTERFACE_H_
#define SWITCH_INTERFACE_H_

/*Macros for SWITCH Connection type*/
#define SWITCH_FORWARD_CONNECTION   0
#define SWITCH_REVERSE_CONNECTION   1

/*Macros for Swiitch Status*/
#define SWITCH_PRESSED         3
#define SWITCH_NOT_PRESSED     4

       /*****************************************************ABIs Prototypes************************************************/

void SWITCH_voidInit (u8 copy_u8SwitchPort, u8 copy_u8SwitchPin);
void SWITCH_voidGetStatus (u8 copy_u8SwitchPort, u8 copy_u8SwitchPin, u8 copy_u8SwitchConnectionType, u8* pu8SwitchStatus);	   



#endif /* SWITCH_INTERFACE_H_ */