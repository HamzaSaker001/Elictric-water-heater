/*
 * EEPROM_interface.h
 *
 * Created: 2/22/2026 2:17:39 PM
 *  Author: hamza
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_voidInit();
void EEPROM_voidWriteByte(u16 copy_u16WordAddres, u8 copy_u8Data);
void EEPROM_voidReadByte(u16 copy_u16WordAddres, u8* pu8Data);
void EEPROM_voidWritePage(u16 copy_u16BaseAddres, u8* pu8ArrTxData, u8 copy_u8DataLength);
void EEPROM_voidReadPage(u16 copy_u16BaseAddres, u8* pu8ArrRxData, u8 copy_u8DataLength);

#endif /* EEPROM_INTERFACE_H_ */