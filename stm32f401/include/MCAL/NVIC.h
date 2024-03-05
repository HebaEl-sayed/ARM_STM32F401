/*
 * NVIC.h
 *
 *  Created on: Mar 3, 2024
 *      Author: LEGION
 */

#ifndef MCAL_NVIC_H_
#define MCAL_NVIC_H_

typedef unsigned int u32 ;
typedef unsigned int u8 ;
#define NULL ((void*)0)


#define PRIGROUP1  0X05FA0300  /* 4 bits    Preempt group and none subgroup */
#define PRIGROUP2  0X05FA0400  /* 3 bits    preempt group and 1 bits for subgroup */
#define PRIGROUP3  0X05FA0500  /* 2 bits    preempt group and 2 bits for subgroup */
#define PRIGROUP4  0X05FA0600  /* 1 bits    preempt group and 3 bits for subgroup */
#define PRIGROUP5  0X05FA0700  /* none bits preempt group and 4 bits for subgroup */

typedef enum
{
	NVIC_enuOK ,
	NVIC_enuNOK

}NVIC_enuErrorStatus_t ;


NVIC_enuErrorStatus_t NVIC_CTRL_EnableIRQ(IRQn_t IRQn);
NVIC_enuErrorStatus_t NVIC_CTR_DisableIRQ(IRQn_t IRQn);
NVIC_enuErrorStatus_t NVIC_CTR_SetPendingIRQ(IRQn_t IRQn);
NVIC_enuErrorStatus_t NVIC_CTR_ClearPendingIRQ(IRQn_t IRQn);
NVIC_enuErrorStatus_t NVIC_GetActivestate (IRQn_t IRQn,u32 *copy_status);
NVIC_enuErrorStatus_t NVIC_generate_SWInterrupt (IRQn_t IRQn);
NVIC_enuErrorStatus_t NVIC_SetSubGroup(u32 SubGroupPriority) ;
NVIC_enuErrorStatus_t NVIC_SetPriority(IRQn_t IRQn, u8 PreemptPriority ,  u8 SubGroupPriority , u32 GroupPR) ;






#endif /* MCAL_NVIC_H_ */
