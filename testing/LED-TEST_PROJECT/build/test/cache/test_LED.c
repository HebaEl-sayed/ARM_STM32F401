#include "src/LED.h"
#include "build/test/mocks/mock_GPIO.h"
#include "C:/Ruby30/lib/ruby/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








LED_CFG_t LEDS[1];



void setUp(void)

{

}



void tearDown(void)

{

}





GPIO_enuErrorStatus_t GPIO_INITPIN_CallbackWithValidCfg(GPIO_t* gpioPin,int cmock_num_calls)

{

    UnityAssertEqualNumber((UNITY_INT)((LEDS[0].pin)), (UNITY_INT)((gpioPin->GPIO_PIN)), (

   ((void *)0)

   ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((LEDS[0].port)), (UNITY_INT)((gpioPin->GPIO_PORT)), (

   ((void *)0)

   ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x00000001)), (UNITY_INT)((gpioPin->GPIO_MODE)), (

   ((void *)0)

   ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x00000002)), (UNITY_INT)((gpioPin->GPIO_SPEED)), (

   ((void *)0)

   ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_INT);

    return GPIO_enuOK;

}

void test_LED_Init_ValidParameters(void)

{

   GPIO_t test_LED ;









   GPIO_INITPIN_Stub(GPIO_INITPIN_CallbackWithValidCfg);









   UnityAssertEqualNumber((UNITY_INT)((LED_OK)), (UNITY_INT)((LED_Init())), (

  ((void *)0)

  ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_INT);

}





void test_LED_Init_InvalidDirection(void)

{

  LEDS[0].connection=0x05;

  UnityAssertEqualNumber((UNITY_INT)((LED_Invalidconnection)), (UNITY_INT)((LED_Init())), (

 ((void *)0)

 ), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_INT);

  LEDS[0].connection=0;

}





void test_LED_SetState_validparameters(void)

{

    LEDS[0].connection=1;

    GPIO_SET_PINVALUE_CMockExpectAndReturn(54, LEDS[0].port, LEDS[0].pin, 0, GPIO_enuOK);

    UnityAssertEqualNumber((UNITY_INT)((LED_OK)), (UNITY_INT)((LED_SetState(0, 1))), (

   ((void *)0)

   ), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_INT);

   mock_GPIO_Verify();

}



void test_LED_SetState_InvalidName(void)

{

    UnityAssertEqualNumber((UNITY_INT)((LED_InvalidLedName)), (UNITY_INT)((LED_SetState((_LED_NUM+1),0))), (

   ((void *)0)

   ), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_INT);

}



void test_LED_SetState_Invalidstate(void)

{

    UnityAssertEqualNumber((UNITY_INT)((LED_InvalidState)), (UNITY_INT)((LED_SetState(0,0X05))), (

   ((void *)0)

   ), (UNITY_UINT)(66), UNITY_DISPLAY_STYLE_INT);

}
