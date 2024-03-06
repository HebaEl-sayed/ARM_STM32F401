/*
 * LED_CFG.C
 *
 *  Created on: Feb 21, 2024
 *      Author: LEGION
 */


#include "GPIO.h"
#include "LED.h"
#include "LED_CFG.h"



const LED_CFG_t LEDS[_LED_NUM] = {
    [LED_1] = {
        .port = GPIOA,
        .pin = GPIO_PIN0,
		.connection = LED_CONNECTION_FORWARD,
		.default_state = LED_STATE_OFF
    },
    [LED_2] = {
        .port = GPIOA,
        .pin = GPIO_PIN1,
        .connection = LED_CONNECTION_FORWARD,
        .default_state = LED_STATE_OFF
    }
};
