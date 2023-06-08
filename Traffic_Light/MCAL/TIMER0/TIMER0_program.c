/*
 * TIMER0_program.c
 *
 *  Created on: Aug 12, 2021
 *      Author: ibrahim
 */

#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "TIMER0_interface.h"
#include "TIMER0_config.h"
#include "TIMER0_private.h"

/************** TIMER ISR Functions prototype **************/

/****** TIMER0 COMP ISR ********/
void __vector_10(void)__attribute__((signal));

static void (*TIMER0_COMP_CALLBACK)(void) = NULL;
/*********************************************************/

void TIM0_voidInit(void)
{
#if TIMER0_MODE_OPERATION == COMPARE_MATCH
	SET_BIT(TCCR0 , WGM01);
	CLR_BIT(TCCR0 , WGM00);
#elif TIMER0_MODE_OPERATION == NORMAL
	CLR_BIT(TCCR0 , WGM01);
	CLR_BIT(TCCR0 , WGM00);
#else
#error "Wrong Timer Mode"
#endif


#ifndef TIMER0_COMPARE_MATCH_INTERRUPT
#if TIMER0_OVERFLOW_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TOIE0);
#elif TIMER0_OVERFLOW_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TOIE0);
#else
#error"Wrong Timer Interrupt configurations"
#endif
#endif

#ifndef TIMER0_OVERFLOW_INTERRUPT
#if TIMER0_COMPARE_MATCH_INTERRUPT == ENABLE
	SET_BIT(TIMSK , OCIE0);
#elif TIMER0_COMPARE_MATCH_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , OCIE0);
#else
#error"Wrong Timer Interrupt configurations"
#endif
#endif

#if TIMER0_ENABLE_DISABLE == ENABLE
	#if TIMER0_CLK_PRESCALLER == TIM0_CLK
		SET_BIT(TCCR0 , CS00);
		CLR_BIT(TCCR0 , CS01);
		CLR_BIT(TCCR0 , CS02);

	#elif	TIMER0_CLK_PRESCALLER == TIM0_CLK_8
		CLR_BIT(TCCR0 , CS00);
		SET_BIT(TCCR0 , CS01);
		CLR_BIT(TCCR0 , CS02);

	#elif	TIMER0_CLK_PRESCALLER == TIM0_CLK_64
		SET_BIT(TCCR0 , CS00);
		SET_BIT(TCCR0 , CS01);
		CLR_BIT(TCCR0 , CS02);

	#elif	TIMER0_CLK_PRESCALLER == TIM0_CLK_256
		CLR_BIT(TCCR0 , CS00);
		CLR_BIT(TCCR0 , CS01);
		SET_BIT(TCCR0 , CS02);

	#elif	TIMER0_CLK_PRESCALLER == TIM0_CLK_1024
		SET_BIT(TCCR0 , CS00);
		CLR_BIT(TCCR0 , CS01);
		SET_BIT(TCCR0 , CS02);
	#endif

	#elif TIMER0_ENABLE_DISABLE == DISABLE
		CLR_BIT(TCCR0 , CS00);
		CLR_BIT(TCCR0 , CS01);
		CLR_BIT(TCCR0 , CS02);
	#else
	#error"Wrong Timer0 Configurations"
#endif

}

void TIM0_u8Set_CompareRegister_Value(u8 Copy_u8Counts)
{
	OCR0 = Copy_u8Counts;
}

u8 TIM0_voidSetCompareCallBack(void(*Copy_ptrCallBackFunc)(void))
{
	u8 Local_ErrorState = STD_OK;
	if(Copy_ptrCallBackFunc != NULL)
	{
		TIMER0_COMP_CALLBACK = Copy_ptrCallBackFunc;
	}
	else
	{
		Local_ErrorState = STD_NOK;
	}
	return Local_ErrorState;
}

void __vector_10(void)
{
	if (TIMER0_COMP_CALLBACK != NULL)
	{
		TIMER0_COMP_CALLBACK();
	}
}
