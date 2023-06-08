/*
 * BUTTON_config.c
 *
 *  Created on: Aug 11, 2022
 *      Author: saber
 */


#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"

#include "BUTTON_private.h"
#include "BUTTON_config.h"

//{ Port Number , Pin Number , PULL_UP / PULL_DOWN / INPUT_FLOATING  }
ST_Switch_CONFIG_t Buttons[NUMBER_OF_BUTTONS]=
{
		{ PORTD, PIN2 , PULL_UP }
};
