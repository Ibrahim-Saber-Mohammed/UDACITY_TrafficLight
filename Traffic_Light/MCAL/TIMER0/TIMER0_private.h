/*
 * TIMER0_private.h
 *
 *  Created on: Aug 12, 2021
 *      Author: ibrahim
 */

#ifndef MCAL_TIMER0_TIMER0_PRIVATE_H_
#define MCAL_TIMER0_TIMER0_PRIVATE_H_

#define TCNT0				*( (volatile u8 * const) 0x52)
#define TCCR0				*( (volatile u8 * const) 0x53)
#define OCR0                *( (volatile u8 * const) 0x5C)
#define TIMSK               *( (volatile u8 * const) 0x59)
#define TIFR                *( (volatile u8 * const) 0x58)

#define	CS00				(0)
#define	CS01				(1)
#define CS02				(2)
#define WGM01				(3)
#define COM00				(4)
#define COM01				(5)
#define WGM00				(6)
#define FOC0				(7)

#define TOIE0				(0)
#define OCIE0				(1)

#define ENABLE	1
#define DISABLE	0

#define COMPARE_MATCH 1
#define NORMAL	0


/************** TIMER0 Pre-scaler options ******************/
#define TIM0_NO_CLK				(0b000)
#define TIM0_CLK				(0b001)
#define TIM0_CLK_8				(0b010)
#define TIM0_CLK_64				(0b011)
#define TIM0_CLK_256			(0b100)
#define TIM0_CLK_1024			(0b101)
#define TIM0_EXTERNAL_FALLING	(0b110)
#define TIM0_EXTERNAL_RISING	(0b111)
/***********************************************************/


#endif /* MCAL_TIMER0_TIMER0_PRIVATE_H_ */
