/*
 * GPIO.h
 *
 *  Created on: Feb 19, 2024
 *      Author: LEGION
 */

#ifndef GPIO_H_
#define GPIO_H_

typedef unsigned int u32 ;
//#define NULL ((void*)0)

#define GPIOA             (void*)0x40020000
#define GPIOB             (void*)0x40020400
#define GPIOC             (void*)0x40020800
#define GPIOD             (void*)0x40020C00
#define GPIOE             (void*)0x40021000
#define GPIOH             (void*)0x40021C00

#define GPIO_PIN0                0x00000000
#define GPIO_PIN1                0x00000001
#define GPIO_PIN2                0x00000002
#define GPIO_PIN3                0x00000003
#define GPIO_PIN4                0x00000004
#define GPIO_PIN5                0x00000005
#define GPIO_PIN6                0x00000006
#define GPIO_PIN7                0x00000007
#define GPIO_PIN8                0x00000008
#define GPIO_PIN9 	      	     0x00000009
#define GPIO_PIN10               0x0000000A
#define GPIO_PIN11               0x0000000B
#define GPIO_PIN12               0x0000000C
#define GPIO_PIN13               0x0000000D
#define GPIO_PIN14               0x0000000E
#define GPIO_PIN15               0x0000000F

#define GPIO_OUTPUT              0x00000001
#define GPIO_OUTPUT_PP           0x00000001
#define GPIO_OUTPUT_PP_PU        0x00000009
#define GPIO_OUTPUT_PP_PD        0x00000011
#define GPIO_OUTPUT_OD           0x00000005
#define GPIO_OUTPUT_OD_PU        0x0000000D
#define GPIO_OUTPUT_OD_PD        0x00000015

#define GPIO_AF                  0x00000002
#define GPIO_AF_PP               0x00000002
#define GPIO_AF_PP_PU            0x0000000A
#define GPIO_AF_PP_PD            0x00000012
#define GPIO_AF_OD               0x00000006
#define GPIO_AF_OD_PU            0x0000000E
#define GPIO_AF_OD_PD            0x00000016

#define GPIO_INPUT               0x00000000
#define GPIO_INPUT_FLOATING      0x00000000
#define GPIO_INPUT_PU            0x00000008
#define GPIO_INPUT_PD            0x00000010

#define GPIO_IOPUT_ANALOG        0x00000003

#define GPIO_LOW_SPEED           0x00000000
#define GPIO_MEDIUM_SPEED        0x00000001
#define GPIO_HIGH_SPEED          0x00000002
#define GPIO_VERYHIGH_SPEED      0x00000003


#define GPIO_AF0_SYSTEM          0x00000000
#define GPIO_AF1_TIM1_2          0x00000001
#define GPIO_AF2_TIM3_5          0x00000002
#define GPIO_AF3_TIM9_11         0x00000003
#define GPIO_AF4_I2C2_3          0x00000004
#define GPIO_AF5_SPI1_4          0x00000005
#define GPIO_AF6_SPI3            0x00000006
#define GPIO_AF7_USART1_2        0x00000007
#define GPIO_AF8_USART6          0x00000008
#define GPIO_AF9_I2C2_3          0x00000009
#define GPIO_AF10_OTG_FS         0x0000000A
#define GPIO_AF11                0x0000000B
#define GPIO_AF12_SDIO           0x0000000C
#define GPIO_AF13                0x0000000D
#define GPIOL_AF14               0x0000000E
#define GPIO_AF15_EVENTOUT       0x0000000F

#define GPIO_RESET               0x00000000
#define GPIO_SET                 0x00000001

typedef struct{

	void *GPIO_PORT  ;
	u32 GPIO_PIN     ;
	u32 GPIO_MODE    ;
	u32 GPIO_SPEED   ;
}GPIO_t;


typedef enum
{
	GPIO_enuOK ,
	GPIO_enuNullpointer,
	GPIO_enuunvalidpin,
	GPIO_enuunvalidParameter ,
	GPIO_enuunvalidstate ,
	GPIO_enuunvalidport ,
	GPIO_enuunvalidmode,
	GPIO_enuNOK

} GPIO_enuErrorStatus_t ;

GPIO_enuErrorStatus_t GPIO_INITPIN (GPIO_t * GPIO_CFG);
GPIO_enuErrorStatus_t GPIO_SET_PINVALUE (void * GPIO_PORT ,u32 GPIO_PIN , u32 GPIO_STATE  );
GPIO_enuErrorStatus_t GPIO_GET_PINVALUE (void * GPIO_PORT ,u32 GPIO_PIN , u32 * GPIO_STATE);
GPIO_enuErrorStatus_t GPIO_AF_CFG (void * GPIO_PORT ,u32 GPIO_PIN , u32 GPIO_Func);
#endif /* GPIO_H_ */
