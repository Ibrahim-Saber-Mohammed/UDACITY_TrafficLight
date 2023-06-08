/*
 * APP.c
 *
 *  Created on: Aug 8, 2022
 *      Author: saber
 */

/* Include the Libraries */
#include "../LIB/STD_TYPES/STD_TYPES.h"
#include "../LIB/BIT_MATH/BIT_MATH.h"
/* Include MCAL Drivers */
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/INTERRUPT/GIE_interface.h"
#include "../MCAL/TIMER0/TIMER0_interface.h"
/* Include HAL Drivers */
#include "../HAL/LED/LED_interface.h"
#include "../HAL/BUTTON/BUTTON_interface.h"

#include "../LIB/DELAY/DELAY.h"
#include "APP.h"
#include "APP_private.h"

// Global variable indicates the Mode of Operation
volatile EN_Application_t Global_ModeOfOperation = APP_NORMAL_MODE;
// Global variable indicates the current state of the LEDs
volatile EN_Application_t Global_enumCurrentState = APP_GREEN_TO_YELLOW;
// Global variable indicates the next state of the LEDs
volatile EN_Application_t Global_enumNextState = APP_CAR_RED_PEDESTRIANS_GREEN;


EN_ApplicationError_t APP_enumNormalModeNextState(void)
{
	/*
	 * The Function is used to Change the next state of the Normal Mode
	 * If the Current State is Cars' Green ON the Next will be Green to Yellow
	 * If the Current State is Cars' Red ON the Next will be Red to Yellow
	 * If the Current State is Green to Yellow the Next will be cars' Red ON
	 * If the Current State is Red to Yellow the Next will be cars' Green ON
	 * */
	EN_ApplicationError_t Local_enumErrorState = APP_OK;
	if (Global_enumCurrentState == APP_CAR_GREEN_PEDESTRIANS_RED)
	{
		Global_enumNextState = APP_GREEN_TO_YELLOW;
	}
	else if (Global_enumCurrentState == APP_CAR_RED_PEDESTRIANS_GREEN)
	{
		Global_enumNextState = APP_RED_TO_YELLOW;
	}
	else if (Global_enumCurrentState == APP_GREEN_TO_YELLOW)
	{
		Global_enumNextState = APP_CAR_RED_PEDESTRIANS_GREEN;
	}
	else if (Global_enumCurrentState == APP_RED_TO_YELLOW)
	{
		Global_enumNextState = APP_CAR_GREEN_PEDESTRIANS_RED;
	}
	else
	{
		Local_enumErrorState = APP_CHANGE_STATE_FAILED; // Error Changing the state
	}
	return Local_enumErrorState; // return Error State
}


EN_ApplicationError_t APP_enumPedestriansModeNextState(void)
{
	/*
	 * The Function is used to Change the next state of the Pedestrian Mode
	 * If the Current State is Cars' Green ON the Next will be APP_PEDESTRIAN_YELLOW
	 * If the Current State is Cars' Red ON the Next will be APP_PEDESTRIAN_RED (Nothing changed)
	 * If the Current State is Green to Yellow or Red to Yellow the Next will be APP_PEDESTRIAN_YELLOW (Blink for 5 seconds)
	 * If the Current State is APP_PEDESTRIAN_RED the Next is Blinking with Green of the pedestrian is ON
	 * IF the current state is APP_PEDESTRIAN_BLINK then the Next is ending the Mode and back to Normal Mode
	 *
	 * */
	EN_ApplicationError_t Local_enumErrorState = APP_OK;
	switch(Global_enumCurrentState)
	{
	case APP_CAR_GREEN_PEDESTRIANS_RED:
		// Blink Yellow 5 seconds then Green of Pedestrian will be ON
		Global_enumNextState = APP_PEDESTRIAN_YELLOW;
		break;
	case APP_CAR_RED_PEDESTRIANS_GREEN:
		// Stay in the state (Nothing Change)
		Global_enumNextState = APP_PEDESTRIAN_RED; // stay for 5 seconds more
		break;
	case APP_GREEN_TO_YELLOW:
	case APP_RED_TO_YELLOW:
		// Blink for 5 seconds then Open Green of Pedestrian ON
		Global_enumNextState = APP_PEDESTRIAN_YELLOW;
		break;
	case APP_PEDESTRIAN_RED:
		// this mean that the previous state was Cars' Red ON
		// So We need after Blinking to go Back to Normal Mode as Nothing Changed in the sequence of states
		// As the cars' Red On the Pedestrian is already green
		// So after blinking turn run normal Mode
		Global_enumNextState = APP_PEDESTRIAN_BLINK;
		break;
	case APP_PEDESTRIAN_YELLOW:
		// means that the previous state is a state that pedestrian mode is On
		// So we need After Blinking to Turn the Pedestrian Green LED ON
		Global_enumNextState = APP_PEDESTRIAN_GREEN;
		break;
	case APP_PEDESTRIAN_GREEN:
		// After pedestrians' Green LED is ON  Blink the yellow
		Global_enumNextState = APP_PEDESTRIAN_BLINK;
		break;
	case APP_PEDESTRIAN_BLINK:
		// end the Mode and back to Normal Mode
		Global_enumNextState = APP_PEDESTRIAN_END;
		break;
	default : Local_enumErrorState = APP_CHANGE_STATE_FAILED; // Error
	}
	return Local_enumErrorState;
}

static EN_ApplicationError_t APP_enumCarRedPedestriansGreen(void)
{
	/*
	 * The Function is Used to Turn ON the Cars' Red LED
	 * and Turn ON the Pedestrians' Green LED
	 * Turn Off All other LEDs
	 */
	EN_ApplicationError_t Local_enumErrorState = APP_OK;
	Local_enumErrorState = LED_voidON(LED_RED_CAR);
	if (Local_enumErrorState == APP_LED_OK)
	{
		Local_enumErrorState = LED_voidON(LED_GREEN_PEDESTRIANS);
		if (Local_enumErrorState == APP_LED_OK)
		{
			Local_enumErrorState = LED_voidOFF(LED_YELLOW_CAR);
			if(Local_enumErrorState == APP_LED_OK)
			{
				Local_enumErrorState = LED_voidOFF(LED_YELLOW_PEDESTRIANS);
			}
		}
	}
	if (Local_enumErrorState == APP_LED_OK)
	{
		Local_enumErrorState = APP_OK;
	}
	else
	{
		Local_enumErrorState = APP_FAILED;
	}
	return Local_enumErrorState;
}
static EN_ApplicationError_t APP_enumCarGreenPedestriansRed(void)
{
	/*
	 * The Function is Used to Turn ON the Cars' Green LED
	 * and Turn ON the Pedestrians' Red LED
	 * Turn Off All other LEDs
	 */
	EN_ApplicationError_t Local_enumErrorState = APP_OK;
	Local_enumErrorState = LED_voidON(LED_GREEN_CAR);
	if (Local_enumErrorState == APP_LED_OK)
	{
		Local_enumErrorState = LED_voidON(LED_RED_PEDESTRIANS);
		if (Local_enumErrorState == APP_LED_OK)
		{
			Local_enumErrorState = LED_voidOFF(LED_YELLOW_CAR);
			if(Local_enumErrorState == APP_LED_OK)
			{
				Local_enumErrorState = LED_voidOFF(LED_YELLOW_PEDESTRIANS);
			}
		}
	}
	if (Local_enumErrorState == APP_LED_OK)
	{
		Local_enumErrorState = APP_OK;
	}
	else
	{
		Local_enumErrorState = APP_FAILED;
	}
	return Local_enumErrorState;
}

static EN_ApplicationError_t APP_enumCarPedestriansYellow(void)
{
	/*
	 * The Function is Used to Blink the yellow LEDs
	 * Turn Off All other LEDs
	 */
	EN_ApplicationError_t Local_enumErrorState = APP_OK;
	Local_enumErrorState = LED_voidOFF(LED_RED_CAR);
	if (Local_enumErrorState == APP_LED_OK)
	{
		Local_enumErrorState = LED_voidOFF(LED_RED_PEDESTRIANS);
		if (Local_enumErrorState == APP_LED_OK)
		{
			Local_enumErrorState = LED_voidOFF(LED_GREEN_CAR);
			if (Local_enumErrorState == APP_LED_OK)
			{
				Local_enumErrorState = LED_voidOFF(LED_GREEN_PEDESTRIANS);
				if (Local_enumErrorState == APP_LED_OK)
				{
					Local_enumErrorState = LED_voidON(LED_YELLOW_CAR);
					if (Local_enumErrorState == APP_LED_OK)
					{
						Local_enumErrorState = LED_voidON(LED_YELLOW_PEDESTRIANS);

						if (Local_enumErrorState == APP_LED_OK)
						{
							delay_ms(200);
							Local_enumErrorState = LED_voidOFF(LED_YELLOW_CAR);
							if (Local_enumErrorState == APP_LED_OK)
							{
								Local_enumErrorState = LED_voidOFF(LED_YELLOW_PEDESTRIANS);
								delay_ms(200);
							}
						}
					}
				}
			}
		}
	}
	if (Local_enumErrorState == APP_LED_OK)
	{
		Local_enumErrorState = APP_OK;
	}
	else
	{
		Local_enumErrorState = APP_FAILED;
	}
	return Local_enumErrorState;
}

static EN_ApplicationError_t APP_enumPedestriansBlink(void)
{
	/*
	 * The Function is Used to Blink the yellow LEDs
	 * Turn the pedestrians' Green LED ON
	 * Turn Off All other LEDs
	 */
	EN_ApplicationError_t Local_enumErrorState = APP_OK;
	Local_enumErrorState = LED_voidOFF(LED_RED_CAR);
	if (Local_enumErrorState == APP_LED_OK)
	{
		Local_enumErrorState = LED_voidOFF(LED_RED_PEDESTRIANS);
		if (Local_enumErrorState == APP_LED_OK)
		{
			Local_enumErrorState = LED_voidOFF(LED_GREEN_CAR);
			if (Local_enumErrorState == APP_LED_OK)
			{
				Local_enumErrorState = LED_voidON(LED_GREEN_PEDESTRIANS);
				if (Local_enumErrorState == APP_LED_OK)
				{
					Local_enumErrorState = LED_voidON(LED_YELLOW_CAR);
					if (Local_enumErrorState == APP_LED_OK)
					{
						Local_enumErrorState = LED_voidON(LED_YELLOW_PEDESTRIANS);

						if (Local_enumErrorState == APP_LED_OK)
						{
							delay_ms(200);
							Local_enumErrorState = LED_voidOFF(LED_YELLOW_CAR);
							if (Local_enumErrorState == APP_LED_OK)
							{
								Local_enumErrorState = LED_voidOFF(LED_YELLOW_PEDESTRIANS);
								delay_ms(200);
							}
						}
					}
				}
			}
		}
	}
	if (Local_enumErrorState == APP_LED_OK)
	{
		Local_enumErrorState = APP_OK;
	}
	else
	{
		Local_enumErrorState = APP_FAILED;
	}
	return Local_enumErrorState;
}

EN_ApplicationError_t APP_enumStart(void)
{
	/**
	 * The Function is to check the state then perform the correct action based on the required state
	 * if the Mode is NORMAL_MODE
	 * 		- Then check the State (one of the three possible states)
	 * 		- Save the current state
	 * 		- The Timer every 5 seconds calls the Function NormalNextState to change the state
	 * else if the Mode is PEDESTRIAN_MODE
	 * 		- Now Check the state
	 * 		- Turn the Correct LEDSs
	 * 		- Save the Current state
	 * 		- if the State is APP_PEDESTRIAN_END
	 * 			- Change the Mode back to Normal Mode
	 */
	EN_ApplicationError_t Local_enumApplicationErrorState = APP_OK;
	if ( Global_ModeOfOperation == APP_NORMAL_MODE )
	{
		switch(Global_enumNextState)
		{
		case APP_CAR_GREEN_PEDESTRIANS_RED:
			/* Function to turn the cars' Green Led and the Pedestrians' Red LED */
			APP_enumCarGreenPedestriansRed();
			Global_enumCurrentState = APP_CAR_GREEN_PEDESTRIANS_RED;
			break;
		case APP_CAR_RED_PEDESTRIANS_GREEN:
			/* Function to turn the cars' Red Led and the Pedestrians' Green LED */
			APP_enumCarRedPedestriansGreen();
			Global_enumCurrentState = APP_CAR_RED_PEDESTRIANS_GREEN;
			break;
		case APP_GREEN_TO_YELLOW:
			/* Function to Blink the cars Pedestrians' Yellow LED */
			APP_enumCarPedestriansYellow();
			Global_enumCurrentState = APP_GREEN_TO_YELLOW;
			break;
		case APP_RED_TO_YELLOW:
			/* Function to Blink the cars Pedestrians' Yellow LED */
			APP_enumCarPedestriansYellow();
			Global_enumCurrentState = APP_RED_TO_YELLOW;
			break;
		default:

			break;
		}
	}
	else if (Global_ModeOfOperation == APP_PEDESTRIAN_MODE)
	{
		switch (Global_enumNextState)
		{
		case APP_PEDESTRIAN_RED:
			// Cars' Red LED ON
			// Pedestrians' Green LED ON
			APP_enumCarRedPedestriansGreen();
			Global_enumCurrentState = APP_PEDESTRIAN_RED;
			break;
		case APP_PEDESTRIAN_END:
			// Cars' Green LED ON
			// Pedestrians' RED LED ON
			APP_enumCarGreenPedestriansRed();
			LED_voidOFF(LED_GREEN_PEDESTRIANS);
			Global_enumCurrentState = APP_CAR_GREEN_PEDESTRIANS_RED;
			// end pedestrian Mode and back to Normal Mode
			Global_ModeOfOperation = APP_NORMAL_MODE;
			break;
		case APP_PEDESTRIAN_GREEN:
			// Cars' Red LED ON
			// Pedestrians' Green LED ON
			APP_enumCarRedPedestriansGreen();
			Global_enumCurrentState = APP_PEDESTRIAN_GREEN;
			break;
		case APP_PEDESTRIAN_YELLOW:
			// Blink the yellow LEDs
			APP_enumCarPedestriansYellow();
			Global_enumCurrentState = APP_PEDESTRIAN_YELLOW;
			break;
		case APP_PEDESTRIAN_BLINK :
			// Blink the Yellow LEDS
			// Keep the Pedestrians' Green LED ON
			APP_enumPedestriansBlink();
			Global_enumCurrentState = APP_PEDESTRIAN_BLINK;
			break;
		default:
			break;
		}
	}
	else
	{
		Local_enumApplicationErrorState = APP_FAILED; // Error state
	}
	return Local_enumApplicationErrorState;
}
