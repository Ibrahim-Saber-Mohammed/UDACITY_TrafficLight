/********************************************************************************/
/* Author 		: Ibrahim saber													*/
/* Date 		: 10/11/2020													*/
/* Version		: V00															*/
/********************************************************************************/

#ifndef BUTTON_PRIVATE_H
#define BUTTON_PRIVATE_H

typedef enum{

	PULL_UP				,
	PULL_DOWN			,
	INPUT_FLOATING

}Switch_connection;

typedef struct {

	u8 Port 				;
	u8 Pin 					;
	Switch_connection Type	;

}ST_Switch_CONFIG_t;


#endif
