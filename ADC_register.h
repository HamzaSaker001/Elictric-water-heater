/*
 * ADC_register.h
 *
 * Created: 2/9/2026 8:36:48 PM
 *  Author: hamza
 */ 


#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX_REG    (*(volatile u8*)0x27)
#define REFS1        7
#define REFS0 		 6
#define ADLAR 		 5
#define MUX4 		 4
#define MUX3 		 3
#define MUX2 		 2
#define MUX1 		 1
#define MUX0		 0

#define ADCSRA_REG   (*(volatile u8*)0x26)
#define ADEN         7
#define ADSC 		 6
#define ADATE 		 5
#define ADIF 		 4
#define ADIE 		 3
#define ADPS2 		 2
#define ADPS1 		 1
#define ADPS0		 0

#define ADCL_REG     (*(volatile u8*)0x25)
#define ADCH_REG     (*(volatile u8*)0x24)
#define ADC_u16_REG  (*(volatile u16*)0x24)

#define SFIOR_REG    (*(volatile u8*)0x50)	
#define ADTS2        7
#define ADTS1 		 6
#define ADTS0		 5

#endif /* ADC_REGISTER_H_ */