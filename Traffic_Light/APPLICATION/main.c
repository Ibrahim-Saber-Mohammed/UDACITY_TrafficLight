/*
 * main.c
 *
 *  Created on: Aug 8, 2022
 *      Author: ibrahim
 */

/* Include The Libraries Used  */
#include "../LIB/STD_TYPES/STD_TYPES.h"
#include "../LIB/BIT_MATH/BIT_MATH.h"

/* Include the MCAL Layer device drivers */
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/TIMER0/TIMER0_interface.h"
#include "../MCAL/INTERRUPT/GIE_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
/* Include HAL Layer device drivers  */
#include "../HAL/LED/LED_interface.h"
#include "../HAL/BUTTON/BUTTON_interface.h"

/* Include Application File */
#include "APP.h"

// extern the Global_ModeOfOperation from the APP.c to change inside the ISR
extern volatile EN_Application_t Global_ModeOfOperation;

// volatile Global Variable represents the timer ticks
volatile u16 u16TimerTicks = 0;

void EXTI_LINE0_CallBack(void)
{
	if (Global_ModeOfOperation == APP_NORMAL_MODE) // only one press is to be handled
	{
		// When the Button is pressed Change the mode of Operation to APP_PEDESTRIAN_MODE
		Global_ModeOfOperation = APP_PEDESTRIAN_MODE;
		u16TimerTicks = 0;
		APP_enumPedestriansModeNextState();
	}

}
void TIMER0_CallBack(void)
{
	/*
	 * F_CPU = 8000000
	 * Pre-scaler = 64
	 * F = 8000000/64
	 * ToverFlow = 2^8 * 1/F = 256 * 64/8000000
	 * 256-------> 2.048ms
	 * X  -------> 1ms
	 * X = 125
	 * Compare Register = X = 125
	 * Interrupt Occurs every 1 ms
	 * so to delay 5 seconds we need 5000 Ticks
	 * the u16TimerTicks is incremented every time we enter ISR
	 *  */
	u16TimerTicks++;
	if (u16TimerTicks == 5000)
	{
		if (Global_ModeOfOperation == APP_NORMAL_MODE)
		{
			u16TimerTicks = 0; // reset the timer ticks
			APP_enumNormalModeNextState(); // Change the state of the next state of the leds in Normal Mode
		}
		else if (Global_ModeOfOperation == APP_PEDESTRIAN_MODE)
		{
			u16TimerTicks = 0; // reset the timer ticks
			APP_enumPedestriansModeNextState(); // change the next state of the leds in pedestrian mode
		}
	}
}

int main(void)
{
	LED_voidInit(); // Initialize  all LEDs
	TIM0_voidInit(); // initialize Timer0
	TIM0_u8Set_CompareRegister_Value(125); // pre-load the timer CTC register with 125 tick
	TIM0_voidSetCompareCallBack(TIMER0_CallBack); // Set the Callback Function to be called in the ISR
	GIE_voidEnable(); // Enable the Global Interrupt
	EXTI_Config EXTI_PushButton ; // Create an Object of the External Interrupt Configurations
	EXTI_PushButton.LINE = LINE0; // Select LIN0
	EXTI_PushButton.SENSE = FALLING_EDGE; // Interrupt on Falling edge
	EXTI_voidEnable(&EXTI_PushButton); // Initialize the External Interrupt
	EXTI_voidSetCALLBACK(LINE0, EXTI_LINE0_CallBack); // Set the callback of the External interrupt Line0
	BUTTON_voidInit();
	while(1)
	{
		APP_enumStart(); // Run Application Function
	}

	return 0;
}

