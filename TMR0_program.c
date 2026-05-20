/*
 * TMR0_program.c
 *
 * Created: 2/11/2026 2:35:28 PM
 *  Author: hamza
 */ 

/*UTILES_LIB*/
#include "Bit_Math.h"
#include "STD_types.h"

/*MCAL*/
#include "TMR0_interface.h"
#include "TMR0_register.h"
#include "TMR0_private.h"
#include "TMR0_config.h"

static void(*PRV_pToFunCallBackOVF)(void);
static void(*PRV_pToFunCallBackCTC)(void);
static u16 PRV_ctcCounter;

void TMR0_voidInit(void)
{
	#if TMR0_MODE == TMR0_NORMAL_MODE
	
	/* Select Normal Mode */
	CLR_BIT(TCCR0_REG, WGM00);
	CLR_BIT(TCCR0_REG, WGM01);
	
	/* Set Preload Value */
	TCNT0_REG = TMR0_PRELOAD_VLAUE;
	
	/* Enable OVF Interrupt	*/
	SET_BIT(TIMSK_REG, TOIE0);
	
	#elif TMR0_MODE == TMR0_CTC_MODE
	
	/* Select CTC Mode */
	CLR_BIT(TCCR0_REG, WGM00);
	SET_BIT(TCCR0_REG, WGM01);
	
	/* Set Preload Value */
	OCR0_REG = TMR0_OUTPUT_COMPARE_VLAUE;
	
	/* Enable OC Interrupt	*/
	SET_BIT(TIMSK_REG, OCIE0);
	
	#endif
}


void TMR0_voidStart(void)
{
	/* Select Prescaler Value = 64 */
	SET_BIT(TCCR0_REG, CS00);
	SET_BIT(TCCR0_REG, CS01);
	CLR_BIT(TCCR0_REG, CS02);
}


void TMR0_voidStop(void)
{
	CLR_BIT(TCCR0_REG, CS00);
	CLR_BIT(TCCR0_REG, CS01);
	CLR_BIT(TCCR0_REG, CS02);
}


void TMR0_voidSetCallBackOVF(void(*pTpFunCallBack)(void))
{
	if(pTpFunCallBack != NULL)
	{
		PRV_pToFunCallBackOVF = pTpFunCallBack;
	}
	else
	{
		//return Error State
	}
}


void TMR0_voidSetCallBackCTC(void(*pTpFunCallBack)(void))
{
	if(pTpFunCallBack != NULL)
	{
		PRV_pToFunCallBackCTC = pTpFunCallBack;
	}
	else
	{
		//return Error State
	}
}


void TMR0_voidSetDelay_msUsingCTC(u16 copy_u16Delay_ms)
{
	/* Under Condition Tick Time 4Ms and Output Compare Value 249 */
	/* Set Preload Value */
	OCR0_REG = 249;
	
	PRV_ctcCounter = copy_u16Delay_ms;
}


void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	static u16 local_u16Counter = 0;
	local_u16Counter++;
	
	if(TMR0_OVERFLOW_COUNTER == local_u16Counter)
	{
		/* Set Preload Value */
		TCNT0_REG = TMR0_PRELOAD_VLAUE;
		
		/* Clear Counter */
		local_u16Counter = 0;
		
		/* Call Action */
		if(PRV_pToFunCallBackOVF != NULL)
		{
			PRV_pToFunCallBackOVF();
		}
	}
}


void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	static u16 local_u16Counter = 0;
	local_u16Counter++;
	
	if(PRV_ctcCounter == local_u16Counter)
	{
		/* Clear Counter */
		local_u16Counter = 0;
		
		/* Call Action */
		if(PRV_pToFunCallBackCTC != NULL)
		{
			PRV_pToFunCallBackCTC();
		}
	}
}