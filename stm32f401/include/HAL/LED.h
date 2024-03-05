/*
 * LED.h
 *
 *  Created on: Feb 21, 2024
 *      Author: LEGION
 */

#ifndef HAL_LED_H_
#define HAL_LED_H_
#include "LED_CFG.h"
typedef unsigned int u32 ;
typedef unsigned int u8 ;

#define LED_CONNECTION_FORWARD  0
#define LED_CONNECTION_REVERSE  1
#define LED_STATE_OFF           0
#define LED_STATE_ON            1


typedef struct
{
void * port ;
u32 pin ;
u32 connection ;
u8  default_state ;

}LED_CFG_t ;

typedef enum{
    LED_OK,
	LED_NOK ,
	LED_Invalidconnection,
    LED_InvalidLedName,
    LED_InvalidState
}LED_ErrorStatus_t;

LED_ErrorStatus_t LED_Init() ;

LED_ErrorStatus_t LED_SetState(u32 copy_led , u8 copy_state );

#endif /* HAL_LED_H_ */
