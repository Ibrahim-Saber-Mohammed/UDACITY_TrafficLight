/********************************************************************************/
/* Author 		: Ibrahim saber													*/
/* Date 		: 10/11/2020													*/
/* Version		: V01															*/
/********************************************************************************/

#ifndef LED_PRIVATE_H
#define LED_PRIVATE_H

/// The Led can be connected either active low or active high
/// Active Low connection means that the cathode of the led is connected to 5v
/// Active HIGH connection means that the cathode of the led is connected to 0v "GND"
/// The Led should have voltage difference to be on
/// The LED_Connection is an enum that contains the two possible types of connection
typedef enum {

	Active_LOW,
	Active_HIGH

}LED_Connection;


typedef struct LED
{
	u8 LED_Port;
	u8 LED_Pin;
	LED_Connection LED_State;
}ST_LedConfigs_t;

#endif
