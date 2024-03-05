/*
 * SWITCH.h
 *
 *  Created on: Feb 21, 2024
 *      Author: LEGION
 */

#ifndef HAL_SWITCH_H_
#define HAL_SWITCH_H_

#include "SWITCH_CFG.h"

typedef unsigned int u32 ;
typedef unsigned int u8 ;
#define NULL ((void*)0)

#define SWITCH_STATE_RELEASED   0
#define SWITCH_STATE_PRESSED    1
#define SWITCH_CONNECTION_PU    0x00000008
#define SWITCH_CONNECTION_PD    0x00000010

typedef struct
{
void * port ;
u32 pin ;
u32 connection ;

}SWITCH_CFG_t ;

typedef enum{
	SWITCH_OK,
	SWITCH_NOK ,
	SWITCH_Invalidconnection,
	SWITCH_InvalidLedName,
	SWITCH_NullPtr
}SWITCH_ErrorStatus_t;



SWITCH_ErrorStatus_t SWITCH_Init() ;

SWITCH_ErrorStatus_t SWITCH_GETState(u32 copy_switch , u8* copy_state );




#endif /* HAL_SWITCH_H_ */
