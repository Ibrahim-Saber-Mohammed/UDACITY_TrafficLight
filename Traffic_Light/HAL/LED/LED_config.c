/*
 * LED_config.c
 *
 *  Created on: Aug 8, 2022
 *      Author: saber
 */
#include "../../LIB/STD_TYPES/STD_TYPES.h"

#include "LED_private.h"
#include "LED_config.h"
#include "../../MCAL/DIO/DIO_interface.h"

ST_LedConfigs_t LEDS[MAX_LED_NUMBER] = {
		{PORTA , PIN0 , Active_HIGH},
		{PORTA , PIN1 , Active_HIGH},
		{PORTA , PIN2 , Active_HIGH},
		{PORTB , PIN0 , Active_HIGH},
		{PORTB , PIN1 , Active_HIGH},
		{PORTB , PIN2 , Active_HIGH}
};
