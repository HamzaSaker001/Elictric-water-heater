 /*
 * SSD.h
 *
 * Created: 12/4/2025 4:25:50 PM
 *  Author: hamza
 */ 


#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_


#define SSD_ID_1			3
#define SSD_ID_2			4

/************************************** APIs Prototypes **************************************/

void SSD_voidInit(void);
void SSD_voidDisplayOneDigitNumber(u8 copy_u8SSD_id, u8 copy_u8DesiredNumber);
void SSD_voidDisplayTwoDigitNumber(u8 copy_u8DesiredNumber);
void SSD_voidClear(void);

#endif /* SSD_INTERFACE_H_ */