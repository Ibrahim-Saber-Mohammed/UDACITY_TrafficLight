#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"

void __vector_1(void)__attribute__((signal));
void __vector_2(void)__attribute__((signal));
void __vector_3(void)__attribute__((signal));

/* array of pointers to Funcions */
void(*EXTI_CALLBACK[3])(void) = {NULL};

void EXTI_voidInit(void)
{
	#if EXTI_LINE == EXTI_LINE0
		SET_BIT(GICR, INT0);
		#if EXTI_SENSE == EXTI_RISING_EDGE
			SET_BIT(MCUCR, ISC00);
			SET_BIT(MCUCR, ISC01);
		#elif EXTI_SENSE == EXTI_FALLING_EDGE
			SET_BIT(MCUCR, ISC01);
			CLR_BIT(MCUCR, ISC00);
		#elif EXTI_SENSE == EXTI_ON_CHANGE
			SET_BIT(MCUCR, ISC00);
			CLR_BIT(MCUCR, ISC01);
		#elif EXTI_SENSE == EXTI_LOW_LEVEL
			CLR_BIT(MCUCR, ISC00);
			CLR_BIT(MCUCR, ISC01);
		#else
			#error 
		#endif
		
	#elif EXTI_LINE == EXTI_LINE1
		SET_BIT(GICR, INT1);
		#if EXTI_SENSE == EXTI_RISING_EDGE
			SET_BIT(MCUCR, ISC10);
			SET_BIT(MCUCR, ISC11);
		#elif EXTI_SENSE == EXTI_FALLING_EDGE
			SET_BIT(MCUCR, ISC11);
			CLR_BIT(MCUCR, ISC10);
		#elif EXTI_SENSE == EXTI_ON_CHANGE
			SET_BIT(MCUCR, ISC10);
			CLR_BIT(MCUCR, ISC11);
		#elif EXTI_SENSE == EXTI_LOW_LEVEL
			CLR_BIT(MCUCR, ISC10);
			CLR_BIT(MCUCR, ISC11);
		#else
			#error
		#endif
		
	#elif EXTI_LINE == EXTI_LINE2
		SET_BIT(GICR, INT2);
		#if EXTI_SENSE == EXTI_RISING_EDGE
			SET_BIT(MCUCSR, ISC2);
		#elif EXTI_SENSE == EXTI_FALLING_EDGE
			CLR_BIT(MCUCSR, ISC2);
		#else
			#error 
		#endif
	#else
		#error 
	#endif
}

void EXTI_voidEnable(const EXTI_Config * Configurations)
{
	switch(Configurations->LINE){
		case LINE0 :
			SET_BIT(GICR, INT0);
			switch(Configurations->SENSE){
				case RISING_EDGE:
					SET_BIT(MCUCR, ISC00);
					SET_BIT(MCUCR, ISC01);
					break;
				case FALLING_EDGE:
					SET_BIT(MCUCR, ISC01);
					CLR_BIT(MCUCR, ISC00);
					break;
				case ON_CHANGE:
					SET_BIT(MCUCR, ISC00);
					CLR_BIT(MCUCR, ISC01);
					break;
				case LOW_LEVEL:
					CLR_BIT(MCUCR, ISC00);
					CLR_BIT(MCUCR, ISC01);
					break;
			}
			break;
		case LINE1 :
			SET_BIT(GICR, INT1);
			switch(Configurations->SENSE){
				case RISING_EDGE:
					SET_BIT(MCUCR, ISC10);
					SET_BIT(MCUCR, ISC11);
					break;
				case FALLING_EDGE:
					SET_BIT(MCUCR, ISC11);
					CLR_BIT(MCUCR, ISC10);
					break;
				case ON_CHANGE:
					SET_BIT(MCUCR, ISC10);
					CLR_BIT(MCUCR, ISC11);
					break;
				case LOW_LEVEL:
					CLR_BIT(MCUCR, ISC10);
					CLR_BIT(MCUCR, ISC11);
					break;
			}
			break;
		case LINE2 :
			SET_BIT(GICR, INT2);
			switch(Configurations->SENSE){
				case RISING_EDGE:
					SET_BIT(MCUCSR, ISC2);
					break;
				case FALLING_EDGE:
					CLR_BIT(MCUCSR, ISC2);
					break;
				default :
					/* Error */ break;
			}
			break;
	}
	
}
void EXTI_voidDisable(EXTI_Line Copy_enumLine)
{
	switch(Copy_enumLine){
		case LINE0:
			CLR_BIT(GICR, INT0);
			break;
		case LINE1:
			CLR_BIT(GICR, INT1);
			break;
		case LINE2:
			CLR_BIT(GICR, INT2);
			break;
		default:
			/* Return Error */ break;
	}
}

void EXTI_voidSetCALLBACK( EXTI_Line Copy_enumLine, void(*CALLBACK)(void) )
{
	if (CALLBACK!=NULL)
	{
		EXTI_CALLBACK[Copy_enumLine]= CALLBACK;
	}
}

static void EXTI_voidClearflag(EXTI_Line Copy_enumLine )
{
	/* Clearing the Flag by Writing One */
	switch(Copy_enumLine)
	{
		case LINE0	: SET_BIT(GIFR, INTF0); break;
		case LINE1	: SET_BIT(GIFR, INTF1); break;
		case LINE2	: SET_BIT(GIFR, INTF2); break;
		default : /* Error */
			break;
	}
}

void __vector_1(void)
{
	if ( EXTI_CALLBACK[0]!=NULL )
	{
		EXTI_CALLBACK[0]();
	}
	EXTI_voidClearflag(LINE0);
}
void __vector_2(void)
{
	if ( EXTI_CALLBACK[1]!=NULL )
	{
		EXTI_CALLBACK[1]();
	}
	EXTI_voidClearflag(LINE1);
}
void __vector_3(void)
{
	if ( EXTI_CALLBACK[2]!=NULL )
	{
		EXTI_CALLBACK[2]();
	}
	EXTI_voidClearflag(LINE2);
}
