/********************************************************************************/
/* Author 		: Ibrahim saber													*/
/* Date 		: 10/11/2020													*/
/* Version		: V01															*/
/********************************************************************************/

#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

typedef enum{
	LED_WRONG_PORT_NUMBER,
	LED_WRONG_PIN_NUMBER,
	LED_INDEX_EXCEED_RANGE,
	LED_WRONG_CONNECTION_TYPE,
	LED_OK = 5
}EN_LedErrors_t;

/**
 * @Function Name 	: LED_voidInit
 * @description		: This Function is used to initialize the LEDs as OUTPUT , Active_high/Active_Low
 * 					: The Function is based on the Link time Configurations
 * @see LED_config.c
 * @param[in]		: void
 * @param[out]		: EN_LedErrors_t -> Error state indicates the possible error may occur
 */

EN_LedErrors_t LED_voidInit	( void );


/**
 * @Function Name 	: LED_voidON
 * @description		: This Function is used to Turn ON the LED
 * @see LED_config.c
 * @param[in]		: Copy_u8LedIndex  -> index of the LED in the array of the connected LEDs to MC
 * @param[out]		: EN_LedErrors_t -> Error state indicates the possible error may occur
 */
EN_LedErrors_t LED_voidON  	( u8 Copy_u8LedIndex);


/**
 * @Function Name 	: LED_voidOFF
 * @description		: This Function is used to Turn OFF the LED
 * @see LED_config.c
 * @param[in]		: Copy_u8LedIndex  -> index of the LED in the array of the connected LEDs to MC
 * @param[out]		: EN_LedErrors_t -> Error state indicates the possible error may occur
 */
EN_LedErrors_t LED_voidOFF 	( u8 Copy_u8LedIndex);


#endif
