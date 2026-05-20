/*
 * TMR0_interface.h
 *
 * Created: 2/11/2026 2:35:43 PM
 *  Author: hamza
 */ 


#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_

/************************** APIs Prototypes **************************/

void TMR0_voidInit(void);
void TMR0_voidStart(void);
void TMR0_voidStop(void);
void TMR0_voidSetCallBackOVF(void(*pTpFunCallBack)(void));
void TMR0_voidSetCallBackCTC(void(*pTpFunCallBack)(void));
void TMR0_voidSetDelay_msUsingCTC(u16 copy_u16Delay_ms);


#endif /* TMR0_INTERFACE_H_ */