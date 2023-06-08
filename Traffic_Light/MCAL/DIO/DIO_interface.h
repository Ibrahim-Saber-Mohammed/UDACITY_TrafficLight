
#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

// Enum contains the Possible Error from the DIO
typedef enum{

	DIO_WRONG_PORT,
	DIO_WRONG_PIN_NUBER,
	DIO_WRONG_PIN_DIRECTION,
	DIO_WRONG_PIN_VALUE,
	DIO_NULL_POINTER,
	DIO_OK
}EN_DioErrorStatus_t;




/* Port Defines */
#define PORTA    0
#define PORTB    1
#define PORTC    2
#define PORTD    3

/* PIN Defines */
#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7

/* PIN Directions */
#define INPUT  0
#define OUTPUT 1

/* PIN Value Options */
#define HIGH   1
#define LOW    0
/**
 * @Function Name 	:	DIO_SetPinValue
 * @description		:	This Function is used to write a value to a bit in I/O Registers
 * @param[in]		: 	u8PortIdCopy , u8PinIdCopy , u8PinValCopy
 * @param[out]		:	EN_DioErrorStatus_t
 */
EN_DioErrorStatus_t DIO_SetPinValue(u8 u8PortIdCopy , u8 u8PinIdCopy, u8 u8PinValCopy);

/**
 * @Function Name 	:	DIO_GetPinValue
 * @description		:	This Function is used to read a bit from I/O Registers
 * @param[in]		: 	u8PortIdCopy , u8PinIdCopy , *u8PinValCopy--> Pointer to u8
 * @param[out]		:	EN_DioErrorStatus_t
 */
EN_DioErrorStatus_t DIO_GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy, u8 *u8PinVal);

/**
 * @Function Name 	:	DIO_SetPinDirection
 * @description		:	This Function is used to set the direction of a bit in I/O Registers
 * @param[in]		: 	u8PortIdCopy , u8PinIdCopy , u8PinDirCopy
 * @param[out]		:	EN_DioErrorStatus_t
 */
EN_DioErrorStatus_t DIO_SetPinDirection (u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinDirCopy);


#endif
