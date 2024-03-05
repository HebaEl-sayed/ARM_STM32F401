/*
 * LED.C
 *
 *  Created on: Feb 21, 2024
 *      Author: LEGION
 */
#include <LED.h>
#include "GPIO.h"


extern const LED_CFG_t LEDS[_LED_NUM];

LED_ErrorStatus_t LED_Init()
{
	LED_ErrorStatus_t Error_Status = LED_OK;
	u8 iter ;
	GPIO_t LED ;
	LED.GPIO_MODE = GPIO_OUTPUT_PP ;
	LED.GPIO_SPEED = GPIO_HIGH_SPEED ;

	for( iter=0 ; iter<_LED_NUM; iter ++)
	{
		if(LEDS[iter].connection > LED_CONNECTION_REVERSE)
		{
			Error_Status =LED_Invalidconnection ;
		}
		else
		{
			LED.GPIO_PORT = LEDS[iter].port;
			LED.GPIO_PIN =LEDS[iter].pin ;
			GPIO_INITPIN (&LED);
		}
	}

	return Error_Status;
}





LED_ErrorStatus_t LED_SetState(u32 copy_led , u8 copy_state )
{

	LED_ErrorStatus_t Error_Status = LED_NOK;
	if(copy_led >_LED_NUM)
	{
		Error_Status = LED_InvalidLedName ;

	}
	else if(copy_state >LED_STATE_ON)
	{
		Error_Status = LED_InvalidState ;
	}
	else
	{
		Error_Status = LED_OK;
		GPIO_SET_PINVALUE(LEDS[copy_led].port, LEDS[copy_led].pin,(LEDS[copy_led].connection ^ copy_state));

	}

	 return Error_Status;
}




