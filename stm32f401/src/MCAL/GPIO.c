/*
 * GPIO.C
 *
 *  Created on: Feb 19, 2024
 *      Author: LEGION
 */

#include <GPIO.h>

#define MODER_GETVALUE    0x00000003
#define OTYPER_GETVALUE   0x00000004
#define PUPDR_GETVALUE    0x00000018

#define OTYPER_SHIFT      0x00000002
#define PUPDR_SHIFT       0x00000003

#define CLEAR_ONEBIT_MASK   0x00000001
#define CLEAR_TWOBITS_MASK  0x00000003
#define CLEAR_FOURBITS_MASK 0x0000000F
#define TWO_BITS  2
#define FOUR_BITS 4
#define RESET_SHIFTING 16

#define GPIO_VALIDATE_PORT(PORT) ( PORT==GPIOA || PORT==GPIOB || PORT==GPIOC || PORT==GPIOD || PORT==GPIOE || PORT==GPIOH )

#define GPIO_VALIDATE_MODE(MODE) ( (MODE == GPIO_OUTPUT) ||         \
                                   (MODE == GPIO_OUTPUT_PP) ||      \
                                   (MODE == GPIO_OUTPUT_PP_PU) ||   \
                                   (MODE == GPIO_OUTPUT_PP_PD) ||   \
                                   (MODE == GPIO_OUTPUT_OD) ||      \
                                   (MODE == GPIO_OUTPUT_OD_PU) ||   \
                                   (MODE == GPIO_OUTPUT_OD_PD) ||   \
                                   (MODE == GPIO_AF) ||             \
                                   (MODE == GPIO_AF_PP) ||          \
                                   (MODE == GPIO_AF_PP_PU) ||       \
                                   (MODE == GPIO_AF_PP_PD) ||       \
                                   (MODE == GPIO_AF_OD) ||          \
                                   (MODE == GPIO_AF_OD_PU) ||       \
                                   (MODE == GPIO_AF_OD_PD) ||       \
                                   (MODE == GPIO_INPUT) ||          \
                                   (MODE == GPIO_INPUT_FLOATING) || \
                                   (MODE == GPIO_INPUT_PU) ||       \
                                   (MODE == GPIO_INPUT_PD) ||       \
                                   (MODE == GPIO_IOPUT_ANALOG))


typedef struct
{
  volatile u32 MODER;
  volatile u32 OTYPER;
  volatile u32 OSPEEDR;
  volatile u32 PUPDR;
  volatile u32 IDR;
  volatile u32 ODR;
  volatile u32 BSRR;
  volatile u32 LCKR;
  volatile u32 AFRL;
  volatile u32 AFRH;
} GPIO_Port_t;



GPIO_enuErrorStatus_t GPIO_INITPIN (GPIO_t * GPIO_CFG)
{
	GPIO_enuErrorStatus_t loc_GPIO_ErrorStatus = GPIO_enuNOK;
	u32 LOC_MODE    ;
	u32 LOC_OTYPER  ;
	u32 LOC_PUPDR   ;

	u32 LOC_TempMODE    ;
	u32 LOC_TempOTYPER  ;
	u32 LOC_TempOSPEEDR ;
	u32 LOC_TempPUPDR   ;

	if( GPIO_CFG == NULL )
	{
		loc_GPIO_ErrorStatus = GPIO_enuNullpointer;
	}
	else if(!(GPIO_VALIDATE_PORT((GPIO_Port_t*)GPIO_CFG->GPIO_PORT)))
	{
		loc_GPIO_ErrorStatus = GPIO_enuunvalidport;
	}
	else if((GPIO_CFG->GPIO_PIN)>GPIO_PIN15)
	{
		loc_GPIO_ErrorStatus = GPIO_enuunvalidpin;
	}
	else if(!(GPIO_VALIDATE_MODE(GPIO_CFG->GPIO_MODE)))
	{
		loc_GPIO_ErrorStatus = GPIO_enuunvalidmode;
	}
   else if((GPIO_CFG->GPIO_SPEED)>GPIO_VERYHIGH_SPEED)
	{
		loc_GPIO_ErrorStatus = GPIO_enuunvalidParameter;
	}
	else
	{
		loc_GPIO_ErrorStatus = GPIO_enuOK;

		LOC_MODE = ( GPIO_CFG->GPIO_MODE & MODER_GETVALUE ) ;
		LOC_OTYPER = ( GPIO_CFG->GPIO_MODE & OTYPER_GETVALUE )>>OTYPER_SHIFT ;
		LOC_PUPDR =( GPIO_CFG->GPIO_MODE & PUPDR_GETVALUE )>>PUPDR_SHIFT ;

		LOC_TempMODE = ((GPIO_Port_t*)GPIO_CFG->GPIO_PORT)->MODER ;
		LOC_TempMODE &=~ ( CLEAR_TWOBITS_MASK << ((GPIO_CFG->GPIO_PIN)*TWO_BITS)) ;
		LOC_TempMODE |=  (LOC_MODE << ((GPIO_CFG->GPIO_PIN)*TWO_BITS)) ;
		((GPIO_Port_t*)GPIO_CFG->GPIO_PORT)->MODER = LOC_TempMODE ;


		LOC_TempOTYPER = ((GPIO_Port_t*)GPIO_CFG->GPIO_PORT)->OTYPER ;
		LOC_TempOTYPER &=~ (CLEAR_ONEBIT_MASK << (GPIO_CFG->GPIO_PIN));
		LOC_TempOTYPER |=  (LOC_OTYPER << (GPIO_CFG->GPIO_PIN));
		((GPIO_Port_t*)GPIO_CFG->GPIO_PORT)->OTYPER = LOC_TempOTYPER ;


		LOC_TempPUPDR = ((GPIO_Port_t*)GPIO_CFG->GPIO_PORT)->PUPDR ;
		LOC_TempPUPDR &=~ (CLEAR_TWOBITS_MASK << ((GPIO_CFG->GPIO_PIN)*TWO_BITS));
		LOC_TempPUPDR |= ( LOC_PUPDR <<  ((GPIO_CFG->GPIO_PIN)*TWO_BITS)) ;
		((GPIO_Port_t*)GPIO_CFG->GPIO_PORT)->PUPDR = LOC_TempPUPDR ;


		LOC_TempOSPEEDR = ((GPIO_Port_t*)GPIO_CFG->GPIO_PORT)-> OSPEEDR ;
		LOC_TempOSPEEDR &=~ (CLEAR_TWOBITS_MASK << ((GPIO_CFG->GPIO_PIN)*TWO_BITS)) ;
		LOC_TempOSPEEDR |= ((GPIO_CFG->GPIO_SPEED)<<((GPIO_CFG->GPIO_PIN)*TWO_BITS))   ;
		((GPIO_Port_t*)GPIO_CFG->GPIO_PORT)-> OSPEEDR = LOC_TempOSPEEDR ;


	}

	return loc_GPIO_ErrorStatus;
}


GPIO_enuErrorStatus_t GPIO_SET_PINVALUE(void *GPIO_PORT, u32 GPIO_PIN, u32 GPIO_STATE)
{
    GPIO_enuErrorStatus_t loc_GPIO_ErrorStatus = GPIO_enuNOK;

    if (GPIO_PORT == NULL)
    {
        loc_GPIO_ErrorStatus = GPIO_enuNullpointer;
    }
    else if (!(GPIO_VALIDATE_PORT(GPIO_PORT)))
    {
        loc_GPIO_ErrorStatus = GPIO_enuunvalidport;
    }
    else if (GPIO_PIN > GPIO_PIN15)
    {
        loc_GPIO_ErrorStatus = GPIO_enuunvalidpin;
    }
    else
    {
        loc_GPIO_ErrorStatus = GPIO_enuOK;
        if (GPIO_STATE == GPIO_SET)
        {
            ((GPIO_Port_t *)GPIO_PORT)->BSRR |= (1 << GPIO_PIN);
        }
        else if (GPIO_STATE == GPIO_RESET)
        {
            ((GPIO_Port_t *)GPIO_PORT)->BSRR |= (1 << (GPIO_PIN + RESET_SHIFTING));
        }
        else
        {
            loc_GPIO_ErrorStatus = GPIO_enuunvalidstate;
        }
    }

    return loc_GPIO_ErrorStatus;
}

GPIO_enuErrorStatus_t GPIO_GET_PINVALUE (void * GPIO_PORT ,u32 GPIO_PIN , u32 * GPIO_STATE)
{

	GPIO_enuErrorStatus_t loc_GPIO_ErrorStatus = GPIO_enuNOK;
	if (GPIO_PORT == NULL || GPIO_STATE == NULL )
	{
		loc_GPIO_ErrorStatus = GPIO_enuNullpointer;
	}
    else if (!(GPIO_VALIDATE_PORT(GPIO_PORT)))
    {
        loc_GPIO_ErrorStatus = GPIO_enuunvalidport;
    }
	else if(GPIO_PIN>GPIO_PIN15)
	{
		loc_GPIO_ErrorStatus = GPIO_enuunvalidpin;
	}
	else
	{
		loc_GPIO_ErrorStatus = GPIO_enuOK;
		*GPIO_STATE = (((GPIO_Port_t*)GPIO_PORT)->IDR >> GPIO_PIN )& 1 ;

	}
	return loc_GPIO_ErrorStatus;
}


GPIO_enuErrorStatus_t GPIO_AF_CFG (void * GPIO_PORT ,u32 GPIO_PIN , u32 GPIO_Func)
{
	u32 TempLow ;
	u32 TempHigh ;
	GPIO_enuErrorStatus_t loc_GPIO_ErrorStatus = GPIO_enuNOK;
	if(GPIO_PORT == NULL )
	{
		loc_GPIO_ErrorStatus = GPIO_enuNullpointer;
	}
    else if (!(GPIO_VALIDATE_PORT(GPIO_PORT)))
    {
        loc_GPIO_ErrorStatus = GPIO_enuunvalidport;
    }
	else if(GPIO_PIN>GPIO_PIN15)
	{
		loc_GPIO_ErrorStatus = GPIO_enuunvalidpin;
	}
	else
	{
		loc_GPIO_ErrorStatus = GPIO_enuOK;

		if (GPIO_PIN == GPIO_PIN0 || GPIO_PIN == GPIO_PIN1 ||GPIO_PIN == GPIO_PIN2 ||GPIO_PIN == GPIO_PIN3 ||GPIO_PIN == GPIO_PIN4 ||GPIO_PIN == GPIO_PIN5 ||GPIO_PIN == GPIO_PIN6 || GPIO_PIN == GPIO_PIN7 )
		{
			TempLow = ((GPIO_Port_t*)GPIO_PORT) ->AFRL ;
			TempLow &=~(CLEAR_FOURBITS_MASK << (GPIO_PIN * FOUR_BITS));
			TempLow	|= (GPIO_Func << (GPIO_PIN * FOUR_BITS)) ;
			((GPIO_Port_t*)GPIO_PORT) ->AFRL = TempLow ;
		}

		else if (GPIO_PIN == GPIO_PIN8 || GPIO_PIN == GPIO_PIN9 ||GPIO_PIN == GPIO_PIN10 ||GPIO_PIN == GPIO_PIN11 ||GPIO_PIN == GPIO_PIN12 ||GPIO_PIN == GPIO_PIN13 ||GPIO_PIN == GPIO_PIN14 || GPIO_PIN == GPIO_PIN15 )
		{
			TempHigh = ((GPIO_Port_t*)GPIO_PORT) ->AFRH ;
			TempHigh &=~(CLEAR_FOURBITS_MASK <<(GPIO_PIN *FOUR_BITS));
			TempHigh|= (GPIO_Func << (GPIO_PIN *FOUR_BITS)) ;
			((GPIO_Port_t*)GPIO_PORT) ->AFRH = TempHigh ;

		}
	}
	return loc_GPIO_ErrorStatus;

}
