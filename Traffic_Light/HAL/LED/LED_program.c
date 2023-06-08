/********************************************************************************/
/* Author 		: Ibrahim saber													*/
/* Date 		: 10/11/2020													*/
/* Version		: V01															*/
/********************************************************************************/

#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "LED_interface.h"
#include "LED_config.h"
#include "LED_private.h"

extern ST_LedConfigs_t LEDS[MAX_LED_NUMBER];

/*********************************************************************************************************************/
/** 
	@brief 	* The function configure the LED Pin as Output
 * The function takes the LED_PORT and THE lED-PIN from the LED_CONFIG struct
 * The function Writes 1 at the DDRx to make the pin OUTPUT

	@param[in] LED_CONFIG Copy_struct_Led_Config "the input parameter is an object of struct LED_CONFIG"
	@param[out] void
 */
/*********************************************************************************************************************/
EN_LedErrors_t LED_voidInit	( void )
{
	EN_LedErrors_t Local_enumErrorState = LED_OK;
	u8 Local_u8LoopIterator = 0;
	for(Local_u8LoopIterator =0 ; Local_u8LoopIterator < MAX_LED_NUMBER; Local_u8LoopIterator++)
	{
		Local_enumErrorState = DIO_SetPinDirection(LEDS[Local_u8LoopIterator].LED_Port, LEDS[Local_u8LoopIterator].LED_Pin, OUTPUT);
	}
	return Local_enumErrorState;
}

/*************************************************************************************************************************/
/* 
	@brief	* The function Turn the LED ON
 * The function takes the LED_PORT and THE lED-PIN from the LED_CONFIG struct
 * The function Checks if
								1-the connection type is "Active_HIGH" Writes 1 to the pin at the PORTx to logic HIGH 
								2-the connection type is "Active_LOW" Writes 0 to the pin at the PORTx to logic LOW 
	@param[in] LED_CONFIG Copy_struct_Led_Config "the input parameter is an object of struct LED_CONFIG"
	@param[out] void
 */
/************************************************************************************************************************/
EN_LedErrors_t LED_voidON  	( u8 Copy_u8LedIndex)
{
	EN_LedErrors_t Local_enumErrorState = LED_OK;
	if (Copy_u8LedIndex < MAX_LED_NUMBER)
	{
		if ( (LEDS[Copy_u8LedIndex].LED_State == Active_HIGH) || ( LEDS[Copy_u8LedIndex].LED_State == Active_LOW ))
		{
			if(LEDS[Copy_u8LedIndex].LED_State == Active_HIGH)
			{

				Local_enumErrorState = DIO_SetPinValue(LEDS[Copy_u8LedIndex].LED_Port, LEDS[Copy_u8LedIndex].LED_Pin, HIGH);
			}
			else if(LEDS[Copy_u8LedIndex].LED_State == Active_LOW)
			{
				Local_enumErrorState = DIO_SetPinValue(LEDS[Copy_u8LedIndex].LED_Port, LEDS[Copy_u8LedIndex].LED_Pin, LOW);
			}
		}
		else
		{
			Local_enumErrorState = LED_WRONG_CONNECTION_TYPE;
		}
	}
	else
	{
		Local_enumErrorState = LED_INDEX_EXCEED_RANGE;
	}
	return Local_enumErrorState;
}

/******************************************************************************************************************************/
/* 
	@berief		* The function Turn the LED OFF
 * The function takes the LED_PORT and THE lED-PIN from the LED_CONFIG struct
 * The function Checks if
								1-the connection type is "Active_HIGH" Writes 0 to the pin at the PORTx to logic LOW 
								2-the connection type is "Active_LOW" Writes 1 to the pin at the PORTx to logic HIGH

	@param[in] LED_CONFIG Copy_struct_Led_Config "the input parameter is an object of struct LED_CONFIG"
	@param[out] void
 */
/******************************************************************************************************************************/
EN_LedErrors_t LED_voidOFF 	( u8 Copy_u8LedIndex )
{
	EN_LedErrors_t Local_enumErrorState = LED_OK;
	if (Copy_u8LedIndex < MAX_LED_NUMBER)
	{
		if ( (LEDS[Copy_u8LedIndex].LED_State == Active_HIGH) || ( LEDS[Copy_u8LedIndex].LED_State == Active_LOW ) )
		{
			if(LEDS[Copy_u8LedIndex].LED_State == Active_HIGH)
			{

				Local_enumErrorState = DIO_SetPinValue(LEDS[Copy_u8LedIndex].LED_Port, LEDS[Copy_u8LedIndex].LED_Pin, LOW);
			}
			else if(LEDS[Copy_u8LedIndex].LED_State == Active_LOW)
			{
				Local_enumErrorState = DIO_SetPinValue(LEDS[Copy_u8LedIndex].LED_Port, LEDS[Copy_u8LedIndex].LED_Pin, HIGH);
			}
		}
		else
		{
			Local_enumErrorState = LED_WRONG_CONNECTION_TYPE;
		}
	}
	else
	{
		Local_enumErrorState = LED_INDEX_EXCEED_RANGE;
	}
	return Local_enumErrorState;
}
