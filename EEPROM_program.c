/*
 * EEPROM_program.c
 *
 * Created: 2/22/2026 2:17:25 PM
 *  Author: hamza
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "I2C_interface.h"

/* HAL */
#include "EEPROM_interface.h"
#include "EEPROM_private.h"

void EEPROM_voidInit()
{
	TWI_voidInitMaster();
}

void EEPROM_voidWriteByte(u16 copy_u16WordAddres, u8 copy_u8Data)
{
	/* divide Word Address */
	u8 Local_u8SlaveAdd = (u8)((copy_u16WordAddres >> 8) | EEPROM_FIXED_ADDRESS);
	
	/* Send Start Condition */
	TWI_voidSendStartCondition();
	
	/* Send Device Address with Write Operation */
	TWI_voidSendSlaveAddressWithWrite(Local_u8SlaveAdd);
	
	/* Send Word Address */
	TWI_voidSendMasterDataByte((u8)copy_u16WordAddres);
	
	/* Send byte data */
	TWI_voidSendMasterDataByte(copy_u8Data);
	
	/* Send Stop Condition */
	TWI_voidSendStopCondition();
	
	/* Self time Write data Delay */
	_delay_ms(5);
}

void EEPROM_voidReadByte(u16 copy_u16WordAddres, u8* pu8Data)
{
	if (pu8Data != NULL)
	{
		/* divide Word Address */
		u8 Local_u8SlaveAdd = (u8)((copy_u16WordAddres >> 8) | EEPROM_FIXED_ADDRESS);
		
		/* Send Start Condition */
		TWI_voidSendStartCondition();
		
		/* Send Device Address with Write Operation */
		TWI_voidSendSlaveAddressWithWrite(Local_u8SlaveAdd);
		
		/* Send Word Address */
		TWI_voidSendMasterDataByte((u8)copy_u16WordAddres);
		
		/* Send Repstart Condition In Order To Switch I2C operation (W>>R) */
		TWI_voidSendRepStartCondition();
		
		/* Send Device Address with Read Operation */
		TWI_voidSendSlaveAddressWithRead(Local_u8SlaveAdd);
		
		/* Read byte data and respond without ACK */
		TWI_voidReceiveMasterDataByteWithoutACK(pu8Data);
		
		/* Send Stop Condition */
		TWI_voidSendStopCondition();
		
		/* Self time Write data Delay */
		_delay_ms(5);
	} 
	else
	{
		//return error state
	}
}

void EEPROM_voidWritePage(u16 copy_u16BaseAddres, u8* pu8ArrTxData, u8 copy_u8DataLength)
{
	
	if ((pu8ArrTxData != NULL) && (copy_u8DataLength <= 16))
	{
		u8 Local_u8Counter;
		
		/* divide Word Address */
		u8 Local_u8SlaveAdd = (u8)((copy_u16BaseAddres >> 8) | EEPROM_FIXED_ADDRESS);
		
		/* Send Start Condition */
		TWI_voidSendStartCondition();
		
		/* Send Device Address with Write Operation */
		TWI_voidSendSlaveAddressWithWrite(Local_u8SlaveAdd);
		
		/* Send Word Address */
		TWI_voidSendMasterDataByte((u8)copy_u16BaseAddres);
		
		for (Local_u8Counter = 0; Local_u8Counter < copy_u8DataLength; Local_u8Counter++)
		{
			/* Send byte data */
			TWI_voidSendMasterDataByte(pu8ArrTxData[Local_u8Counter]);
		}
		
		/* Send Stop Condition */
		TWI_voidSendStopCondition();
		
		/* Self time Write data Delay */
		_delay_ms(5);
	} 
	else
	{
		//return error state
	}
}

void EEPROM_voidReadPage(u16 copy_u16BaseAddres, u8* pu8ArrRxData, u8 copy_u8DataLength)
{
	if ((pu8ArrRxData != NULL) && (copy_u8DataLength <= 16))
	{
		u8 Local_u8Counter;
		
		/* divide Word Address */
		u8 Local_u8SlaveAdd = (u8)((copy_u16BaseAddres >> 8) | EEPROM_FIXED_ADDRESS);
		
		/* Send Start Condition */
		TWI_voidSendStartCondition();
		
		/* Send Device Address with Write Operation */
		TWI_voidSendSlaveAddressWithWrite(Local_u8SlaveAdd);
		
		/* Send Word Address */
		TWI_voidSendMasterDataByte((u8)copy_u16BaseAddres);
		
		/* Send Repstart Condition In Order To Switch I2C operation (W>>R) */
		TWI_voidSendRepStartCondition();
		
		/* Send Device Address with Read Operation */
		TWI_voidSendSlaveAddressWithRead(Local_u8SlaveAdd);
		
		for (Local_u8Counter = 0; Local_u8Counter < (copy_u8DataLength-1); Local_u8Counter++)
		{	
			/* Read byte data and respond with ACK */
			TWI_voidReceiveMasterDataByteWithACK(&pu8ArrRxData[Local_u8Counter]);
		}
		/* Read byte data and respond without ACK */
		TWI_voidReceiveMasterDataByteWithoutACK(&pu8ArrRxData[Local_u8Counter]);
		
		/* Send Stop Condition */
		TWI_voidSendStopCondition();
		
		/* Self time Write data Delay */
		_delay_ms(5);
	} 
	else
	{
		//return error state
	}
}
