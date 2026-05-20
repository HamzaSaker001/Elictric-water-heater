/*
 * LM35_interface.h
 *
 * Created: 2/25/2026 2:28:46 PM
 *  Author: hamza
 */ 


#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

/* API to initialize LM35 ADC channel */
void LM35_voidInit(void);

/* API to read temperature in °C */
void LM35_voidGetTemperature(u8* pu8Temperature);

#endif /* LM35_INTERFACE_H_ */