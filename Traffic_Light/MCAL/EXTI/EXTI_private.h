#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define GICR			*(( volatile u8 * const)0x5B)
#define INT0			6
#define INT1 			7
#define INT2			5

#define GIFR			*(( volatile u8 * const)0x5A)
#define INTF0			6
#define INTF1 			7
#define INTF2			5

#define MCUCR 			*(( volatile u8 * const)0x55)
#define ISC00			0
#define ISC01			1
#define ISC10			2
#define ISC11			3

#define MCUCSR 			*(( volatile u8 * const)0x54)
#define ISC2			6


#define EXTI_LINE0					0
#define EXTI_LINE1					1
#define EXTI_LINE2					2

#define EXTI_RISING_EDGE			0	
#define EXTI_FALLING_EDGE			1
#define EXTI_ON_CHANGE				2
#define EXTI_LOW_LEVEL				3


static void EXTI_voidClearflag(EXTI_Line Copy_enumLine );

#endif
