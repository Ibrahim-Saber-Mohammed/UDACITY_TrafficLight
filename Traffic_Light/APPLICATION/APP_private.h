/*
 * APP_private.h
 *
 *  Created on: Aug 9, 2022
 *      Author: saber
 */

#ifndef APPLICATION_APP_PRIVATE_H_
#define APPLICATION_APP_PRIVATE_H_

/**
 * @name 			: APP_enumCarRedPedestriansGreen
 * @description		:
 * @param[in] 		: void
 * @param[out] 		: EN_ApplicationError_t
 */
static EN_ApplicationError_t APP_enumCarRedPedestriansGreen(void);

/**
 * @name 			: APP_enumCarGreenPedestriansRed
 * @description		:
 * @param[in] 		: void
 * @param[out] 		: EN_ApplicationError_t
 */
static EN_ApplicationError_t APP_enumCarGreenPedestriansRed(void);

/**
 * @name 			: APP_enumCarPedestriansYellow
 * @description		:
 * @param[in] 		: void
 * @param[out] 		: EN_ApplicationError_t
 */
static EN_ApplicationError_t APP_enumCarPedestriansYellow(void);


static EN_ApplicationError_t APP_enumPedestriansBlink(void);

#endif /* APPLICATION_APP_PRIVATE_H_ */
