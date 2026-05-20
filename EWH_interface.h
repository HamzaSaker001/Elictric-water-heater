/*
 * EWH_interface.h
 *
 * Created: 2/27/2026
 *  Author: hamza
 */

#ifndef EWH_INTERFACE_H_
#define EWH_INTERFACE_H_

#include "STD_TYPES.h"

void EWH_voidInit(void);
void EWH_voidTask(void);
void EWH_voidTimerCallback(void);   /* Called from TMR0 ISR every 100 ms */

/* Getters (optional, for debugging / future LCD) */
void EWH_voidGetCurrentAvgTemp(u8 *Copy_pu8Temp);
void EWH_voidGetSetTemp(u8 *Copy_pu8Temp);

#endif /* EWH_INTERFACE_H_ */
