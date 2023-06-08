/*
 * TIMER0_interface.h
 *
 *  Created on: Aug 12, 2021
 *      Author: ibrahim
 */

#ifndef MCAL_TIMER0_TIMER0_INTERFACE_H_
#define MCAL_TIMER0_TIMER0_INTERFACE_H_

/**
 *@Function Name		: 	TIM0_voidInit
 *@Function Description	:	This Function is used to initialize the Timer0 Clock and prescaller and the Mode
 *@Function param[in]	:	void
 *@Function param[out]	:	void
 *@see 					:	TIMER0_config.h
 */
void TIM0_voidInit(void);
/**
 *@Function Name	:	TIM0_u8Set_CompareRegister_Value
 *@description		: 	The Function is used to load the Compare register with a value
 *@param[in]		: 	Copy_u8Counts  -> the Value to be loaded
 *@param[out]		: 	void
 */
void TIM0_u8Set_CompareRegister_Value(u8 Copy_u8Counts);

/**
 *@Function Name	:	TIM0_voidSetCompareCallBack
 *@description		: 	The Function is used to save the call back function of the Timer0 Compare Interrupt
 *@param[in]		: 	void(*Copy_ptrCallBackFunc)(void)  -> pointer to function
 *@param[out]		: 	u8 -> Error State
 */
u8 TIM0_voidSetCompareCallBack(void(*Copy_ptrCallBackFunc)(void));

#endif /* MCAL_TIMER0_TIMER0_INTERFACE_H_ */
