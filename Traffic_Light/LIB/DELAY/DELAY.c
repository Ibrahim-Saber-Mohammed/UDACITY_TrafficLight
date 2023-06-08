/*
 * DELAY.c
 *
 *  Created on: Aug 12, 2022
 *      Author: saber
 */

#include "../STD_TYPES/STD_TYPES.h"

#include "DELAY.h"
static void delay_loop_2(u16 __count);
void delay_ms(f64 __ms)
{
	u16 __ticks;
	double __tmp = ((F_CPU) / 4e3) * __ms;
	if (__tmp < 1.0)
		__ticks = 1;
	else if (__tmp > 65535)
	{
		//	__ticks = requested delay in 1/10 ms
		__ticks = (u16) (__ms * 10.0);
		while(__ticks)
		{
			// wait 1/10 ms
			delay_loop_2(((F_CPU) / 4e3) / 10);
			__ticks --;
		}
		return;
	}
	else
		__ticks = (u16)__tmp;
	delay_loop_2(__ticks);
}

static void delay_loop_2(u16 __count)
{
	__asm__ volatile (
		"1: sbiw %0,1" "\n\t"
		"brne 1b"
		: "=w" (__count)
		: "0" (__count)
	);
}
