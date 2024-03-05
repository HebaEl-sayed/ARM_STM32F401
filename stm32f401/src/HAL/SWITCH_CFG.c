/*
 * SWITCH_CFG.c
 *
 *  Created on: Feb 21, 2024
 *      Author: LEGION
 */


#include "GPIO.h"
#include "SWITCH.h"
#include "SWITCH_CFG.h"



const SWITCH_CFG_t SWITCHES[_SWITCH_NUM] = {
    [SWITCH_1] = {
        .port = GPIOA,
        .pin = GPIO_PIN0,
		.connection = SWITCH_CONNECTION_PU,

    },
    [SWITCH_2] = {
        .port = GPIOA,
        .pin = GPIO_PIN1,
        .connection = SWITCH_CONNECTION_PU,

    }
};
