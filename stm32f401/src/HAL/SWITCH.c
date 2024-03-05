/*
 * SWITCH.C
 *
 *  Created on: Feb 21, 2024
 *      Author: LEGION
 */
#include "SWITCH.h"
#include "GPIO.h"

#define SHIFT      0x00000003
extern const SWITCH_CFG_t SWITCHES[_SWITCH_NUM];

SWITCH_ErrorStatus_t SWITCH_Init()
{
	SWITCH_ErrorStatus_t Error_Status = SWITCH_OK;
	u8 iter ;
	GPIO_t SWITCH ;
	SWITCH.GPIO_SPEED = GPIO_HIGH_SPEED ;

	for( iter=0 ; iter<_SWITCH_NUM; iter ++)
	{
		if(SWITCHES[iter].connection !=SWITCH_CONNECTION_PU && SWITCHES[iter].connection !=SWITCH_CONNECTION_PD)
		{
			Error_Status = SWITCH_Invalidconnection ;
		}
		else
		{
			SWITCH.GPIO_PORT = SWITCHES[iter].port;
			SWITCH.GPIO_PIN =SWITCHES[iter].pin ;
			SWITCH.GPIO_MODE = SWITCHES[iter].connection ;
			GPIO_INITPIN (&SWITCH);
		}
	}
	return Error_Status;

}

SWITCH_ErrorStatus_t SWITCH_GETState(u32 copy_switch , u8* copy_state )
{
	SWITCH_ErrorStatus_t Error_Status = SWITCH_NOK;
	u8 Loc_State =0 ;

	if(copy_switch >_SWITCH_NUM)
	{
		Error_Status = SWITCH_InvalidLedName ;

	}
	else if(copy_state == NULL)
	{
		Error_Status = SWITCH_NullPtr ;
	}
	else
	{
		Error_Status = SWITCH_OK;
		GPIO_GET_PINVALUE (SWITCHES[copy_switch].port, SWITCHES[copy_switch].pin ,&Loc_State);
		* copy_state = Loc_State ^ (SWITCHES[copy_switch].connection >> SHIFT);
	}

	 return Error_Status;
}



