/*
 * RCC.h
 *
 *  Created on: Feb 15, 2024
 *      Author: LEGION
 */

#ifndef RCC_H_
#define RCC_H_


typedef unsigned int u32 ;


#define RCC_HSE_CRYSTAL     0x00010000
#define RCC_HSE_RC          0x00050000
#define RCC_HSI             0x00000081
#define RCC_PLL             0x01000000

#define RCC_SYSCLK_HSE      0x00000001
#define RCC_SYSCLK_HSI      0x00000000
#define RCC_SYSCLK_PLL      0x00000002

#define RCC_PLL_HSE         0x00400000
#define RCC_PLL_HSI         0x00000000

#define RCC_AHB1  0
#define RCC_AHB2  1
#define RCC_APB1  2
#define RCC_APB2  3


/******************************** AHB1 PERI **********************************************/
#define  GPIOAEN   0x00000001
#define  GPIOBEN   0x00000002
#define  GPIOCEN   0x00000004
#define  GPIODEN   0x00000008
#define  GPIOEEN   0x00000010
#define  GPIOHEN   0x00000080
#define  CRCEN     0x00001000
#define  DMA1EN    0x00200000
#define  DMA2EN    0x00400000

/******************************** AHB2 PERI **********************************************/
#define OTGFSEN  0x00000080

/******************************** APB1 PERI **********************************************/
#define  TIM2EN   0x00000001
#define  TIM3EN   0x00000002
#define  TIM4EN   0x00000004
#define  TIM5EN   0x00000008
#define  WWDGEN   0x00000800
#define  SPI2EN   0x00004000
#define  SPI3EN   0x00008000
#define  USART2EN 0x00020000
#define  I2C1EN   0x00200000
#define  I2C2EN   0x00400000
#define  I2C3EN   0x00800000
#define  PWREN    0x10000000

/******************************** APB2 PERI **********************************************/
#define  TIM1EN    0x00000001
#define  USART1EN  0x00000010
#define  USART6EN  0x00000020
#define  ADC1EN    0x00000100
#define  SDIOEN    0x00000800
#define  SPI1EN    0x00001000
#define  SP45EN    0x00002000
#define  SYSCFGEN  0x00004000
#define  TIM9EN    0x00010000
#define  TIM10EN   0x00020000
#define  TIM11EN   0x00040000

/*********************APB1 PRESCALER ********************************************/

#define PRE1_AHB_NOTDIVIDED        0x00000000
#define PRE1_AHB_DIVIDED_BY_2      0x00001000
#define PRE1_AHB_DIVIDED_BY_4      0x00001400
#define PRE1_AHB_DIVIDED_BY_8      0x00001800
#define PRE1_AHB_DIVIDED_BY_16     0x00001C00


/********************* APB2 PRESCALER *******************************************/

#define PRE2_AHB_NOTDIVIDED      0x00000000
#define PRE2_AHB_DIVIDED_BY_2    0x00008000
#define PRE2_AHB_DIVIDED_BY_4    0x0000A000
#define PRE2_AHB_DIVIDED_BY_8    0x0000C000
#define PRE2_AHB_DIVIDED_BY_16   0x0000E000


/**********************AHB PRESCALER ********************************************/

#define SYSTEM_CLOCK_NOTDIVIDED         0x00000000
#define SYSTEM_CLOCK_DIVIDED_BY_2       0x00000080
#define SYSTEM_CLOCK_DIVIDED_BY_4       0x00000090
#define SYSTEM_CLOCK_DIVIDED_BY_8       0x000000A0
#define SYSTEM_CLOCK_DIVIDED_BY_16      0x000000B0
#define SYSTEM_CLOCK_DIVIDED_BY_64      0x000000C0
#define SYSTEM_CLOCK_DIVIDED_BY_128     0x000000D0
#define SYSTEM_CLOCK_DIVIDED_BY_256     0x000000E0
#define SYSTEM_CLOCK_DIVIDED_BY_512     0x000000F0









typedef enum
{
	RCC_enuOK ,
	RCC_enuNOK ,
	RCC_enuInvalidConfigurationForClock ,
	RCC_enuClockNotReady ,
	RCC_enuInvalidPLLClockOption,
	RCC_enuInvalidConfigurationForPLL ,

} RCC_enuErrorStatus_t ;




RCC_enuErrorStatus_t RCC_Clock_ON (u32 RCC_clock );
RCC_enuErrorStatus_t RCC_Clock_OFF (u32 RCC_clock );
RCC_enuErrorStatus_t RCC_SelectClock (u32 system_clock );
RCC_enuErrorStatus_t RCC_Select_PLLClock (u32 PLL_clock);
RCC_enuErrorStatus_t RCC_CFG_PLLClock (u32 PLL_NValue , u32 PLL_MValue ,u32 PLL_PValue ,u32 PLL_QValue );
RCC_enuErrorStatus_t RCC_EnablePeri (u32 Copy_BUS , u32 Copy_Peri  );
RCC_enuErrorStatus_t RCC_DisablePeri (u32 Copy_BUS , u32 Copy_Peri  );
RCC_enuErrorStatus_t CFG_RCC_AHB_PRESCALER (u32 AHB_PRESCALER ) ;
RCC_enuErrorStatus_t CFG_RCC_APB1_PRESCALER (u32 APB1_PRESCALER ) ;
RCC_enuErrorStatus_t CFG_RCC_APB2_PRESCALER (u32 APB2_PRESCALER ) ;
#endif /* RCC_H_ */
