/********************************************************************************/
/* Author 		: Ibrahim saber													*/
/* Date 		: 10/11/2020													*/
/* Version		: V00															*/
/********************************************************************************/

#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include <util/delay.h>

#include "BUTTON_interface.h"
#include "BUTTON_config.h"
#include "BUTTON_private.h"

extern ST_Switch_CONFIG_t Buttons[NUMBER_OF_BUTTONS];

/* 
 * The function configure the BUTTON Pin as INPUT
 * The function takes the BUTTON_PORT and THE BUTTON-PIN
 * The function Writes 0 at the DDRx to make the pin INPUT
 */
void BUTTON_voidInit( void )
{
	u8 Local_u8LoopIterator = 0;
	for (Local_u8LoopIterator = 0; Local_u8LoopIterator< NUMBER_OF_BUTTONS ; Local_u8LoopIterator++)
	{
		DIO_SetPinDirection(Buttons[Local_u8LoopIterator].Port , Buttons[Local_u8LoopIterator].Pin ,INPUT);
		// Enable the Internal Pull up resistor
		if( Buttons[Local_u8LoopIterator].Type == PULL_UP )
		{
			DIO_SetPinValue(Buttons[Local_u8LoopIterator].Port , Buttons[Local_u8LoopIterator].Pin ,HIGH);
		}
	}
}

/* 
 * The function read the Button State
 * The function takes the BUTTON_PORT and THE BUTTON-PIN
 * The function reads the pin at PINx and return the value (0 , 1)
 */
u8 BUTTON_u8Read(u8 Copy_u8ButtonIndex )
{

	u8 Local_u8ReadVal ;
	DIO_GetPinValue( Buttons[Copy_u8ButtonIndex].Port , Buttons[Copy_u8ButtonIndex].Pin , &Local_u8ReadVal );
	_delay_ms(30);
	DIO_GetPinValue( Buttons[Copy_u8ButtonIndex].Port , Buttons[Copy_u8ButtonIndex].Pin , &Local_u8ReadVal );
	return Local_u8ReadVal;
}


