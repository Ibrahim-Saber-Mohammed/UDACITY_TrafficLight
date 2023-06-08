/*
 * GIE_interface.h
 *
 *  Created on: Aug 30, 2021
 *      Author: ibrahim
 */

#ifndef MCAL_INTERRUPT_GIE_INTERFACE_H_
#define MCAL_INTERRUPT_GIE_INTERFACE_H_

/**
 * @Function Name	:	GIE_voidEnable
 * @description 	: 	This Function is Used To enable the global Interrupt
 * @param[in]		: 	void
 * @param[out]		: 	void
 * */
void GIE_voidEnable(void);

/**
 * @Function Name	:	GIE_voidDisable
 * @description 	: 	This Function is Used To disable the global Interrupt
 * @param[in]		: 	void
 * @param[out]		: 	void
 * */
void GIE_voidDisable(void);

#endif /* MCAL_INTERRUPT_GIE_INTERFACE_H_ */
