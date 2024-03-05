/*
 * RCC1.c
 *
 *  Created on: Feb 21, 2024
 *      Author: LEGION
 */
#include <RCC.h>


#define RCC_BASE_ADDRESS         0x40023800
#define RCC_HSE_RDY              0x00020000
#define RCC_HSI_RDY              0x00000002
#define RCC_PLL_RDY              0x02000000
#define SYSCLOCK_MASK            0x00000003
#define RCC_PLL_M_PRESCALE_MASK  0x0000003F
#define RCC_PLL_N_PRESCALE_MASK	 0x00007FC0
#define RCC_PLL_P_PRESCALE_MASK  0x00030000
#define RCC_PLL_Q_PRESCALE_MASK  0x0F000000
#define AHB_PRESCALER_MASK       0x000000F0
#define APB1_PRESCALER_MASK      0x00001C00
#define APB2_PRESCALER_MASK      0x0000E000
#define RCC_PLLN                 6
#define RCC_PLLM                 0
#define RCC_PLLP                 16
#define RCC_PLLQ                 24

typedef struct{
	volatile u32 RCC_CR;
	volatile u32 RCC_PLLCFGR;
	volatile u32 RCC_CFGR;
	volatile u32 RCC_CIR;
	volatile u32 RCC_AHB1RSTR;
	volatile u32 RCC_AHB2RSTR;
	volatile u32 RESERVED;
	volatile u32 RESERVED2;
	volatile u32 RCC_APB1RSTR;
	volatile u32 RCC_APB2RSTR;
	volatile u32 RESERVED3;
	volatile u32 RESERVED4;
	volatile u32 RCC_AHB1ENR;
	volatile u32 RCC_AHB2ENR;
	volatile u32 RESERVED5;
	volatile u32 RESERVED6;
	volatile u32 RCC_APB1ENR;
	volatile u32 RCC_APB2ENR;
	volatile u32 RESERVED7;
	volatile u32 RESERVED8;
	volatile u32 RCC_AHB1LPENR;
	volatile u32 RCC_AHB2LPENR;
	volatile u32 RESERVED9;
	volatile u32 RESERVED10;
	volatile u32 RCC_APB1LPENR;
	volatile u32 RCC_APB2LPENR;
	volatile u32 RESERVED11;
	volatile u32 RESERVED12;
	volatile u32 RCC_BDCR;
	volatile u32 RCC_CSR;
	volatile u32 RESERVED13;
	volatile u32 RESERVED14;
	volatile u32 RCC_SSCGR;
	volatile u32 RCC_PLLI2SCFGR;
	volatile u32 RESERVED15;
	volatile u32 RCC_DCKCFGR;
}RCC_PERI_t;


volatile RCC_PERI_t *const RCC =(RCC_PERI_t*)RCC_BASE_ADDRESS ;





RCC_enuErrorStatus_t RCC_Clock_ON (u32 RCC_clock )
{
	RCC_enuErrorStatus_t loc_RCC_ErrorStatus = RCC_enuNOK ;

	if(RCC_clock!=RCC_HSE_CRYSTAL && RCC_clock!=RCC_HSE_RC && RCC_clock!=RCC_HSI && RCC_clock!= RCC_PLL)
	{
		loc_RCC_ErrorStatus = RCC_enuInvalidConfigurationForClock ;
	}
	else
	{
		loc_RCC_ErrorStatus = RCC_enuOK ;
		u32 time_out = 10000 ;
		RCC->RCC_CR |= RCC_clock ;

		switch (RCC_clock)
		{
		case RCC_HSE_CRYSTAL :

			while (!(RCC->RCC_CR & RCC_HSE_RDY ) && time_out)
			{
				time_out-- ;
			}
			break ;
		case RCC_HSE_RC :

			while (!(RCC->RCC_CR & RCC_HSE_RDY ) && time_out)
			{
				time_out-- ;
			}
			break ;
		case RCC_HSI :

			while (!(RCC->RCC_CR & RCC_HSI_RDY )&& time_out)
			{
				time_out-- ;
			}
			break ;
		case RCC_PLL :

			while (!(RCC->RCC_CR & RCC_PLL_RDY )&& time_out)
			{
				time_out-- ;
			}
			break ;
		default :
			loc_RCC_ErrorStatus = RCC_enuClockNotReady ;
			break ;
		}

	}
	return loc_RCC_ErrorStatus ;
}



RCC_enuErrorStatus_t RCC_Clock_OFF (u32 RCC_clock )
{
	RCC_enuErrorStatus_t loc_RCC_ErrorStatus = RCC_enuNOK;
	if(RCC_clock!=RCC_HSE_CRYSTAL && RCC_clock!=RCC_HSE_RC && RCC_clock!=RCC_HSI && RCC_clock!= RCC_PLL)
	{
		loc_RCC_ErrorStatus = RCC_enuInvalidConfigurationForClock ;
	}
	else
	{
		loc_RCC_ErrorStatus = RCC_enuOK ;
		RCC->RCC_CR &=~ RCC_clock ;
	}
	return loc_RCC_ErrorStatus ;
}




RCC_enuErrorStatus_t RCC_SelectClock (u32 system_clock )
{
	RCC_enuErrorStatus_t loc_RCC_ErrorStatus = RCC_enuNOK;
	u32 Temp ;

	if ((system_clock!=RCC_SYSCLK_HSE) && (system_clock!=RCC_SYSCLK_HSI )&&(system_clock!= RCC_SYSCLK_PLL))
	{
		loc_RCC_ErrorStatus = RCC_enuNOK;
	}
	else
	{
		loc_RCC_ErrorStatus = RCC_enuOK ;

		Temp=RCC->RCC_CFGR ;
		Temp &=~ SYSCLOCK_MASK;
		Temp |=system_clock ;
		RCC->RCC_CFGR= Temp ;

	}
	return loc_RCC_ErrorStatus ;
}



RCC_enuErrorStatus_t RCC_Select_PLLClock (u32 PLL_clock)
{
	RCC_enuErrorStatus_t loc_RCC_ErrorStatus = RCC_enuNOK;
	if(PLL_clock!=RCC_PLL_HSE && PLL_clock!= RCC_PLL_HSI)
	{
		loc_RCC_ErrorStatus = RCC_enuInvalidPLLClockOption  ;
	}
	else
	{
		loc_RCC_ErrorStatus = RCC_enuOK ;
		RCC->RCC_PLLCFGR |=PLL_clock ;
	}

	return loc_RCC_ErrorStatus ;
}

RCC_enuErrorStatus_t RCC_CFG_PLLClock (u32 PLL_NValue , u32 PLL_MValue ,u32 PLL_PValue ,u32 PLL_QValue )
{
	RCC_enuErrorStatus_t loc_RCC_ErrorStatus = RCC_enuNOK;
	u32 Temp ;
	if (PLL_NValue <192 || PLL_NValue > 432)
	{
		loc_RCC_ErrorStatus = RCC_enuInvalidConfigurationForPLL  ;
	}
	else if (PLL_MValue <2 || PLL_MValue > 63)
	{
		loc_RCC_ErrorStatus = RCC_enuInvalidConfigurationForPLL  ;
	}
	else if(PLL_PValue != 2 && PLL_PValue != 4 && PLL_PValue != 6 && PLL_PValue != 8)
	{
		loc_RCC_ErrorStatus = RCC_enuInvalidConfigurationForPLL  ;
	}
	else if(PLL_QValue < 2 || PLL_QValue > 15)
	{
		loc_RCC_ErrorStatus = RCC_enuInvalidConfigurationForPLL  ;
	}
	else
	{
		loc_RCC_ErrorStatus = RCC_enuOK ;
		Temp = RCC->RCC_PLLCFGR ;
		Temp &=~ RCC_PLL_M_PRESCALE_MASK  ;
		Temp &=~ RCC_PLL_N_PRESCALE_MASK	 ;
		Temp &=~ RCC_PLL_P_PRESCALE_MASK  ;
		Temp &=~ RCC_PLL_Q_PRESCALE_MASK   ;
		Temp |= (PLL_NValue<< RCC_PLLN) | (PLL_MValue<< RCC_PLLM ) |(PLL_PValue<< RCC_PLLP) |(PLL_QValue<< RCC_PLLQ)    ;
		RCC->RCC_PLLCFGR = Temp ;
	}
	return loc_RCC_ErrorStatus ;
}


RCC_enuErrorStatus_t RCC_EnablePeri (u32 Copy_BUS , u32 Copy_Peri  )
{
	RCC_enuErrorStatus_t loc_RCC_ErrorStatus = RCC_enuOK;
	switch (Copy_BUS)
	{
	case RCC_AHB1 :
		RCC-> RCC_AHB1ENR|= Copy_Peri;
		break ;
	case RCC_AHB2 :
		RCC-> RCC_AHB2ENR|= Copy_Peri ;
		break ;
	case RCC_APB1 :
		RCC-> RCC_APB1ENR|= Copy_Peri ;
		break ;
	case RCC_APB2 :
		RCC-> RCC_APB2ENR|= Copy_Peri;
		break ;
	default :
		loc_RCC_ErrorStatus = RCC_enuNOK ;
		break ;

	}
	return loc_RCC_ErrorStatus ;
}

RCC_enuErrorStatus_t RCC_DisablePeri (u32 Copy_BUS , u32 Copy_Peri  )
{
	RCC_enuErrorStatus_t loc_RCC_ErrorStatus = RCC_enuOK;
	switch (Copy_BUS)
	{
	case RCC_AHB1 :
		RCC-> RCC_AHB1ENR &=~ Copy_Peri;
		break ;
	case RCC_AHB2 :
		RCC-> RCC_AHB2ENR &=~ Copy_Peri ;
		break ;
	case RCC_APB1 :
		RCC-> RCC_APB1ENR &=~ Copy_Peri ;
		break ;
	case RCC_APB2 :
		RCC-> RCC_APB2ENR &=~ Copy_Peri;
		break ;
	default :
		loc_RCC_ErrorStatus = RCC_enuNOK ;
		break ;

	}
	return loc_RCC_ErrorStatus ;
}


RCC_enuErrorStatus_t CFG_RCC_AHB_PRESCALER (u32 AHB_PRESCALER )
{
	RCC_enuErrorStatus_t loc_RCC_ErrorStatus = RCC_enuNOK;
	u32 Temp ;

	if (AHB_PRESCALER != SYSTEM_CLOCK_DIVIDED_BY_2 && AHB_PRESCALER!= SYSTEM_CLOCK_DIVIDED_BY_4 &&
			AHB_PRESCALER != SYSTEM_CLOCK_DIVIDED_BY_8&&AHB_PRESCALER != SYSTEM_CLOCK_DIVIDED_BY_16&&
			AHB_PRESCALER != SYSTEM_CLOCK_DIVIDED_BY_64&&AHB_PRESCALER != SYSTEM_CLOCK_DIVIDED_BY_128&&
			AHB_PRESCALER != SYSTEM_CLOCK_DIVIDED_BY_256 && AHB_PRESCALER!= SYSTEM_CLOCK_DIVIDED_BY_512 )
	{
		loc_RCC_ErrorStatus = RCC_enuNOK;
	}
	else
	{
		loc_RCC_ErrorStatus = RCC_enuOK ;
		Temp=RCC->RCC_CFGR ;
		Temp &=~ AHB_PRESCALER_MASK;
		Temp |=AHB_PRESCALER ;
		RCC->RCC_CFGR= Temp ;
	}
	return loc_RCC_ErrorStatus ;
}




RCC_enuErrorStatus_t CFG_RCC_APB1_PRESCALER (u32 APB1_PRESCALER )
{
	RCC_enuErrorStatus_t loc_RCC_ErrorStatus = RCC_enuNOK;
	u32 Temp ;

	if (APB1_PRESCALER != PRE1_AHB_DIVIDED_BY_2 && APB1_PRESCALER!= PRE1_AHB_DIVIDED_BY_4 &&
			APB1_PRESCALER != PRE1_AHB_DIVIDED_BY_8&&APB1_PRESCALER != PRE1_AHB_DIVIDED_BY_16)
	{
		loc_RCC_ErrorStatus = RCC_enuNOK;
	}
	else
	{
		loc_RCC_ErrorStatus = RCC_enuOK ;
		Temp=RCC->RCC_CFGR ;
		Temp &=~ APB1_PRESCALER_MASK;
		Temp |=APB1_PRESCALER ;
		RCC->RCC_CFGR= Temp ;
	}
	return loc_RCC_ErrorStatus ;
}





RCC_enuErrorStatus_t CFG_RCC_APB2_PRESCALER (u32 APB2_PRESCALER )
{
	RCC_enuErrorStatus_t loc_RCC_ErrorStatus = RCC_enuNOK;
	u32 Temp ;

	if (APB2_PRESCALER != PRE2_AHB_DIVIDED_BY_2 && APB2_PRESCALER!= PRE2_AHB_DIVIDED_BY_4 &&
			APB2_PRESCALER != PRE2_AHB_DIVIDED_BY_8&&APB2_PRESCALER != PRE2_AHB_DIVIDED_BY_16)
	{
		loc_RCC_ErrorStatus = RCC_enuNOK;
	}
	else
	{
		loc_RCC_ErrorStatus = RCC_enuOK ;
		Temp=RCC->RCC_CFGR ;
		Temp &=~ APB2_PRESCALER_MASK;
		Temp |=APB2_PRESCALER ;
		RCC->RCC_CFGR= Temp ;
	}
	return loc_RCC_ErrorStatus ;
}


