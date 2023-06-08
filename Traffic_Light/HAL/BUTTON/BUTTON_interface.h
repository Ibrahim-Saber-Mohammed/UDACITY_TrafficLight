/********************************************************************************/
/* Author 		: Ibrahim saber													*/
/* Date 		: 10/11/2020													*/
/* Version		: V00															*/
/********************************************************************************/

#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H

/**
 * @Function Name	: BUTTON_voidInit
 * @description		: This Function is used to initialize the Buttons (INPUT , PULL_UP/PULL_DOWN)
 * 					: The function is based on Link time configurations
 * @param[in]		: void
 * @param[out]		: void
 */
void BUTTON_voidInit(void );

/**
 * @Function Name	: BUTTON_u8Read
 * @description		: This Function is used to get the Button value(HIGH / LOW)
 * 					: The function is based on Link time configurations
 * @param[in]		: Copy_u8ButtonIndex  -> index of the Button in the array of buttons connected to the MC
 * @param[out]		: u8 -> pressed value
 */
u8 BUTTON_u8Read 	( u8 Copy_u8ButtonIndex );

#endif
