#include"../../LIB/STD_TYPES/STD_TYPES.h"
#include"../../LIB/BIT_MATH/BIT_MATH.h"
#include"DIO_interface.h"
#include"DIO_private.h"
#include "DIO_config.h"


EN_DioErrorStatus_t DIO_SetPinValue(u8 u8PortIdCopy , u8 u8PinIdCopy, u8 u8PinValCopy)
{
	EN_DioErrorStatus_t LOC_enumState = DIO_OK ;
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ( (u8PortIdCopy >= 0) && (u8PortIdCopy <= PORTD) )
	{
		// make sure the pin is in valid range
		if (u8PinIdCopy >= 0 && u8PinIdCopy <= PIN7)
		{
			if (u8PinValCopy == HIGH)
			{
				/* Check on the Required PORT Number */
				switch (u8PortIdCopy)
				{
				case PORTA: SET_BIT(PORTA_REG,u8PinIdCopy); break;
				case PORTB: SET_BIT(PORTB_REG,u8PinIdCopy); break;
				case PORTC: SET_BIT(PORTC_REG,u8PinIdCopy); break;
				case PORTD: SET_BIT(PORTD_REG,u8PinIdCopy); break;
				}

			}
			else if (u8PinValCopy == LOW)
			{
				/* Check on the Required PORT Number */
				switch (u8PortIdCopy)
				{
				case PORTA: CLR_BIT(PORTA_REG,u8PinIdCopy); break;
				case PORTB: CLR_BIT(PORTB_REG,u8PinIdCopy); break;
				case PORTC: CLR_BIT(PORTC_REG,u8PinIdCopy); break;
				case PORTD: CLR_BIT(PORTD_REG,u8PinIdCopy); break;
				}
			}
			else
			{
				LOC_enumState = DIO_WRONG_PIN_VALUE ;
			}
		}
		else
		{
			LOC_enumState = DIO_WRONG_PIN_NUBER;
		}
	}
	else
	{
		LOC_enumState = DIO_WRONG_PORT ;
	}
	return LOC_enumState;
}

EN_DioErrorStatus_t DIO_GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy,  u8 *u8PinVal)
{
	EN_DioErrorStatus_t LOC_enumState = DIO_OK ;
	if (u8PinVal != NULL)
	{
		/* Make sure that the Port ID and Pin ID are in the valid range */
		if ( (u8PortIdCopy >= 0) && (u8PortIdCopy <= PORTD) )
		{
			// make sure the pin is in valid range
			if (u8PinIdCopy >= 0 && u8PinIdCopy <= PIN7)
			{
				/* Check on the Required PORT Number */
				switch (u8PortIdCopy)
				{
				case PORTA:*u8PinVal= GET_BIT(PINA_REG,u8PinIdCopy); break;
				case PORTB:*u8PinVal= GET_BIT(PINB_REG,u8PinIdCopy); break;
				case PORTC:*u8PinVal= GET_BIT(PINC_REG,u8PinIdCopy); break;
				case PORTD:*u8PinVal= GET_BIT(PIND_REG,u8PinIdCopy); break;
				}
			}
			else
			{
				LOC_enumState = DIO_WRONG_PIN_NUBER;
			}
		}
		else
		{
			LOC_enumState = DIO_WRONG_PORT;
		}
	}
	else
	{
		LOC_enumState = DIO_NULL_POINTER;
	}
	return LOC_enumState;
}

EN_DioErrorStatus_t DIO_SetPinDirection (u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinDirCopy)
{
	EN_DioErrorStatus_t LOC_enumState = DIO_OK ;
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ( (u8PortIdCopy >= 0) && (u8PortIdCopy <= PORTD) )
	{
		// make sure the pin is in valid range
		if (u8PinIdCopy >= 0 && u8PinIdCopy <= PIN7)
		{
			if (u8PinDirCopy == OUTPUT)
			{
				/* Check on the Required PORT Number */
				switch (u8PortIdCopy)
				{
				case PORTA: SET_BIT(DDRA_REG,u8PinIdCopy); break;
				case PORTB: SET_BIT(DDRB_REG,u8PinIdCopy); break;
				case PORTC: SET_BIT(DDRC_REG,u8PinIdCopy); break;
				case PORTD: SET_BIT(DDRD_REG,u8PinIdCopy); break;
				}
			}
			else if ( u8PinDirCopy == INPUT )
			{
				/* Check on the Required PORT Number */
				switch (u8PortIdCopy)
				{
				case PORTA: CLR_BIT(DDRA_REG,u8PinIdCopy); break;
				case PORTB: CLR_BIT(DDRB_REG,u8PinIdCopy); break;
				case PORTC: CLR_BIT(DDRC_REG,u8PinIdCopy); break;
				case PORTD: CLR_BIT(DDRD_REG,u8PinIdCopy); break;
				}
			}
			else
			{
				LOC_enumState = DIO_WRONG_PIN_DIRECTION ;
			}
		}
		else
		{
			LOC_enumState = DIO_WRONG_PIN_NUBER ;
		}
	}
	else
	{
		LOC_enumState = DIO_WRONG_PORT;
	}
	return LOC_enumState;
}
