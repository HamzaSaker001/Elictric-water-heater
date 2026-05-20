/*
 * I2C_register.h
 *
 * Created: 2/21/2026 11:52:18 AM
 *  Author: hamza
 */ 


#ifndef I2C_REGISTER_H_
#define I2C_REGISTER_H_

#define TWBR_REG			(*(volatile u8*)0x20)

#define TWCR_REG			(*(volatile u8*)0x56)
#define TWINT 		        7
#define TWEA 		        6
#define TWSTA 		        5
#define TWSTO 		        4
#define TWWC 		        3
#define TWEN 		        2
#define TWIE		        0

#define TWSR_REG			(*(volatile u8*)0x21)
#define TWPS1               1
#define TWPS0               0

#define TWDR_REG			(*(volatile u8*)0x23)

#define TWAR_REG			(*(volatile u8*)0x22)
#define TWGCE				0




#endif /* I2C_REGISTER_H_ */