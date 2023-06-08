/*
 * APP.h
 *
 *  Created on: Aug 8, 2022
 *      Author: saber
 */

#ifndef APPLICATION_APP_H_
#define APPLICATION_APP_H_

// Macros specifies the leds index inside the LEDs configurations according to their connection
#define LED_RED_CAR				(u8)2
#define LED_GREEN_CAR			(u8)0
#define LED_YELLOW_CAR			(u8)1
#define LED_RED_PEDESTRIANS		(u8)5
#define LED_GREEN_PEDESTRIANS	(u8)3
#define LED_YELLOW_PEDESTRIANS	(u8)4


// Enum contains all the APP file States of the two modes
typedef enum{
	APP_LED_WRONG_PORT_NUMBER,
	APP_LED_WRONG_PIN_NUMBER,
	APP_LED_INDEX_EXCEED_RANGE,
	APP_LED_WRONG_CONNECTION_TYPE,
	APP_FAILED,
	APP_LED_OK,
	APP_CHANGE_STATE_FAILED,
	APP_OK
}EN_ApplicationError_t;

typedef enum{
	APP_CAR_RED_PEDESTRIANS_GREEN,
	APP_RED_TO_YELLOW,
	APP_GREEN_TO_YELLOW,
	APP_CAR_GREEN_PEDESTRIANS_RED,
	APP_NORMAL_MODE,
	APP_PEDESTRIAN_MODE,
	APP_PEDESTRIAN_RED,
	APP_PEDESTRIAN_YELLOW,
	APP_PEDESTRIAN_BLINK,
	APP_PEDESTRIAN_GREEN,
	APP_PEDESTRIAN_END

}EN_Application_t;

/**
 * @Function Name 	: APP_enumNormalModeNextState
 * @description		: This Function is used to change the state to the next state of the normal mode
 * 					  The Function changes the next state according to the current state.
 * @param [in] 		: void
 * @param [out]		: EN_ApplicationError_t
 *
 */
EN_ApplicationError_t APP_enumNormalModeNextState(void);

/**
 * @Function Name 	: APP_enumPedestriansModeNextState
 * @description		: This Function is used to change the state to the next state of the Pedestrians mode
 * 					  The Function changes the next state according to the current state.
 * @param [in] 		: void
 * @param [out]		: EN_ApplicationError_t
 */
EN_ApplicationError_t APP_enumPedestriansModeNextState(void);

/**
 * @Function Name 	: APP_enumStart
 * @description		: This Function is the project algorithm. This function contains the implementation of the project sequence
 *					  The Function is called inside the main.
 * @param [in] 		: void
 * @param [out]		: EN_ApplicationError_t
 */
EN_ApplicationError_t APP_enumStart(void);

#endif /* APPLICATION_APP_H_ */
