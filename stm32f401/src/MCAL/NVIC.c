/*
 * NVIC.c
 *
 *  Created on: Mar 3, 2024
 *      Author: LEGION
 */
#include "stm32f401cc.h"
#include "NVIC.h"

#define NVIC_BASE_ADDRESS         0xE000E100
#define SCB_BASE_ADDRESS          0xE000ED00
#define PRIGROUP_MASK             0X05FA0000
#define REFRENCEADDRESS_PRIGROUP  0X05FA0300
#define PRIGROUP_DIFFRENCE        0x100
#define IPR_MASK                  0x00000000
#define REGBITS_NUM                  32
#define IPR_HOLDS_INTNUM             4
#define IPR_INT_BITSNUM              8
#define FOURBIT_SHIFT                4

typedef struct
{
	volatile u32 ISER[8];
	volatile u32 RESERVED1[24];
	volatile u32 ICER[8];
	volatile u32 RESERVED2[24];
	volatile u32 ISPR[8];
	volatile u32 RESERVED3[24];
	volatile u32 ICPR[8];
	volatile u32 RESERVED4[24];
	volatile u32 IABR[8];
	volatile u32 RESERVED5[56];
	volatile u32 IPR[60];
	volatile u32 Reserved6[580];
	volatile u32 STIR;
} NVIC_t;



typedef struct{

	volatile u32 CPUID;
	volatile u32 ICSR;
	volatile u32 VTOR;
	volatile u32 AIRCR;
	volatile u32 SCR;
	volatile u32 CCR;
	volatile u32 SHPR1;
	volatile u32 SHPR2;
	volatile u32 SHPR3;
	volatile u32 SHCSR;
	volatile u32 CFSR;
	volatile u32 HFSR;
	volatile u32 RESERVED;
	volatile u32 MMAR;
	volatile u32 BFAR;
	volatile u32 AFSR;

}SCB_t;


volatile NVIC_t *const NVIC =(NVIC_t*)NVIC_BASE_ADDRESS ;
volatile SCB_t *const SCB =(SCB_t*)SCB_BASE_ADDRESS ;



NVIC_enuErrorStatus_t NVIC_CTRL_EnableIRQ(IRQn_t IRQn)
{
	NVIC_enuErrorStatus_t loc_NVIC_ErrorStatus = NVIC_enuNOK ;
	u32 Loc_index ;
	if(IRQn >= _NVIC_NUM)
	{
		loc_NVIC_ErrorStatus =NVIC_enuNOK ;
	}
	else
	{
		loc_NVIC_ErrorStatus =NVIC_enuOK ;
		Loc_index = IRQn/REGBITS_NUM;
		NVIC->ISER[Loc_index] = (1<<(IRQn % REGBITS_NUM)) ; 
	}
	return loc_NVIC_ErrorStatus;
}


NVIC_enuErrorStatus_t NVIC_CTR_DisableIRQ(IRQn_t IRQn)
{
	NVIC_enuErrorStatus_t loc_NVIC_ErrorStatus = NVIC_enuNOK ;
	u32 Loc_index ;
	if(IRQn >= _NVIC_NUM)
	{
		loc_NVIC_ErrorStatus =NVIC_enuNOK ;
	}
	else
	{
		loc_NVIC_ErrorStatus =NVIC_enuOK ;
		Loc_index = IRQn/REGBITS_NUM;
		NVIC->ICER[Loc_index] = (1<<(IRQn % REGBITS_NUM)) ;
	}
	return loc_NVIC_ErrorStatus;

}


NVIC_enuErrorStatus_t NVIC_CTR_SetPendingIRQ(IRQn_t IRQn)
{
	NVIC_enuErrorStatus_t loc_NVIC_ErrorStatus = NVIC_enuNOK ;
	u32 Loc_index ;
	if(IRQn >= _NVIC_NUM)
	{
		loc_NVIC_ErrorStatus =NVIC_enuNOK ;
	}
	else
	{
		loc_NVIC_ErrorStatus =NVIC_enuOK ;
		Loc_index = IRQn/REGBITS_NUM;
		NVIC->ISPR[Loc_index] = (1<<(IRQn % REGBITS_NUM)) ;
	}
	return loc_NVIC_ErrorStatus;

}


NVIC_enuErrorStatus_t NVIC_CTR_ClearPendingIRQ(IRQn_t IRQn)
{
	NVIC_enuErrorStatus_t loc_NVIC_ErrorStatus = NVIC_enuNOK ;
	u32 Loc_index ;
	if(IRQn >= _NVIC_NUM)
	{
		loc_NVIC_ErrorStatus =NVIC_enuNOK ;
	}
	else
	{
		loc_NVIC_ErrorStatus =NVIC_enuOK ;
		Loc_index = IRQn/REGBITS_NUM;
		NVIC->ICPR[Loc_index] = (1<<(IRQn % REGBITS_NUM)) ;
	}
	return loc_NVIC_ErrorStatus;
}



NVIC_enuErrorStatus_t NVIC_GetActivestatus (IRQn_t IRQn,u32 *copy_status)
{
	NVIC_enuErrorStatus_t loc_NVIC_ErrorStatus = NVIC_enuNOK ;
	u32 Loc_index ;
	if(IRQn >= _NVIC_NUM)
	{
		loc_NVIC_ErrorStatus =NVIC_enuNOK ;
	}
	else if(copy_status == NULL)
	{

		loc_NVIC_ErrorStatus =NVIC_enuNOK ;
	}
	else
	{
		loc_NVIC_ErrorStatus =NVIC_enuOK ;
		Loc_index = IRQn/REGBITS_NUM;
		*copy_status = (NVIC->IABR[Loc_index] >> (IRQn % REGBITS_NUM) )& 1 ;
	}
	return loc_NVIC_ErrorStatus;


}


NVIC_enuErrorStatus_t NVIC_generate_SWInterrupt (IRQn_t IRQn)
{
	NVIC_enuErrorStatus_t loc_NVIC_ErrorStatus = NVIC_enuNOK ;
	if(IRQn >= _NVIC_NUM)
	{
		loc_NVIC_ErrorStatus =NVIC_enuNOK ;
	}
	else
	{
		loc_NVIC_ErrorStatus =NVIC_enuOK ;

		NVIC->STIR= IRQn ;
	}
	return loc_NVIC_ErrorStatus;

}

NVIC_enuErrorStatus_t NVIC_SetSubGroup(u32 SubGroupPriority)
{
	NVIC_enuErrorStatus_t loc_NVIC_ErrorStatus = NVIC_enuNOK ;
	u32 LOC_Temp ;

	if( SubGroupPriority > PRIGROUP5 )
	{
		loc_NVIC_ErrorStatus =NVIC_enuNOK ;
	}
	else
	{
		loc_NVIC_ErrorStatus =NVIC_enuOK ;
		LOC_Temp = SCB->AIRCR ;
		LOC_Temp &=~ PRIGROUP_MASK ;
		LOC_Temp |= SubGroupPriority;
		SCB->AIRCR= LOC_Temp ;
	}
	return loc_NVIC_ErrorStatus;
}


NVIC_enuErrorStatus_t NVIC_SetPriority(IRQn_t IRQn, u8 PreemptPrriority ,  u8 SubGroupPrriority ,u32 GroupPR)
{
	NVIC_enuErrorStatus_t loc_NVIC_ErrorStatus = NVIC_enuNOK ;
    u32 LOC_Priority ;
    u32 LOC_index ;
    u32 LOC_TEMP ;
	if(IRQn >= _NVIC_NUM)
	{
		loc_NVIC_ErrorStatus =NVIC_enuNOK ;
	}
	else if( GroupPR > PRIGROUP5)
	{
		loc_NVIC_ErrorStatus =NVIC_enuNOK ;
	}
	else
	{
		loc_NVIC_ErrorStatus =NVIC_enuOK ;
		LOC_Priority = SubGroupPrriority |( PreemptPrriority << ((GroupPR - REFRENCEADDRESS_PRIGROUP )/PRIGROUP_DIFFRENCE));
		LOC_index = IRQn/IPR_HOLDS_INTNUM ;

		LOC_TEMP =NVIC->IPR[LOC_index];
		LOC_TEMP &=~ IPR_MASK;
		LOC_TEMP |= LOC_Priority << (((IRQn % IPR_HOLDS_INTNUM)*IPR_INT_BITSNUM)+FOURBIT_SHIFT);
        NVIC->IPR[LOC_index]=LOC_TEMP;

	}
	return loc_NVIC_ErrorStatus;


}











