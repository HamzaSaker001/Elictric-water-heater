/*
 * I2C_interface.h
 *
 * Created: 2/21/2026 11:52:00 AM
 *  Author: hamza
 */ 


#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_


/****************** API's Prototypes ******************/

/* Master */
void TWI_voidInitMaster(void);
void TWI_voidSendStartCondition(void);
void TWI_voidSendRepStartCondition(void);
void TWI_voidSendStopCondition(void);
void TWI_voidSendSlaveAddressWithWrite(u8 copy_u8SlaveAdd);
void TWI_voidSendSlaveAddressWithRead (u8 copy_u8SlaveAdd);
void TWI_voidSendMasterDataByte(u8 copy_u8TxData);
void TWI_voidReceiveMasterDataByteWithACK(u8* pu8RxData);
void TWI_voidReceiveMasterDataByteWithoutACK(u8* pu8RxData);


#endif /* I2C_INTERFACE_H_ */