#ifdef TEST

#include "unity.h"
#include "mock_GPIO.h"
#include "LED.h"


LED_CFG_t LEDS[1];

void setUp(void)
{
}

void tearDown(void)
{
}


GPIO_enuErrorStatus_t GPIO_INITPIN_CallbackWithValidCfg(GPIO_t* gpioPin,int cmock_num_calls)
{
    TEST_ASSERT_EQUAL(LEDS[0].pin,gpioPin->GPIO_PIN);
    TEST_ASSERT_EQUAL(LEDS[0].port,gpioPin->GPIO_PORT);
    TEST_ASSERT_EQUAL(GPIO_OUTPUT_PP,gpioPin->GPIO_MODE);
    TEST_ASSERT_EQUAL(GPIO_HIGH_SPEED,gpioPin->GPIO_SPEED);
    return GPIO_enuOK;
}
void test_LED_Init_ValidParameters(void)
{
   GPIO_t test_LED ;
   /*test_LED.GPIO_MODE = GPIO_OUTPUT_PP ;
   test_LED.GPIO_SPEED = GPIO_HIGH_SPEED ;*/
   /*TEST_ASSERT_EQUAL(test_LED.GPIO_MODE,GPIO_OUTPUT_PP);
   TEST_ASSERT_EQUAL(test_LED.GPIO_SPEED,GPIO_HIGH_SPEED);*/
   GPIO_INITPIN_StubWithCallback(GPIO_INITPIN_CallbackWithValidCfg);
   
   /*test_LED.GPIO_PIN = LEDS[0].pin ;
   test_LED.GPIO_PORT = LEDS[0].port;
   GPIO_INITPIN_ExpectAndReturn(&test_LED,GPIO_enuOK);*/
   TEST_ASSERT_EQUAL(LED_OK,LED_Init());
}


void test_LED_Init_InvalidDirection(void)
{
  LEDS[0].connection=0x05;
  TEST_ASSERT_EQUAL(LED_Invalidconnection,LED_Init());
  LEDS[0].connection=LED_CONNECTION_FORWARD;
}


void test_LED_SetState_validparameters(void)
{
    LEDS[0].connection=LED_CONNECTION_REVERSE;
    GPIO_SET_PINVALUE_ExpectAndReturn(LEDS[0].port, LEDS[0].pin,0, GPIO_enuOK);
    TEST_ASSERT_EQUAL(LED_OK, LED_SetState(0, LED_STATE_ON)); 
   mock_GPIO_Verify();  
}

void test_LED_SetState_InvalidName(void)
{
    TEST_ASSERT_EQUAL(LED_InvalidLedName,LED_SetState((_LED_NUM+1),LED_STATE_OFF));
}

void test_LED_SetState_Invalidstate(void)
{
    TEST_ASSERT_EQUAL(LED_InvalidState,LED_SetState(0,0X05));
}

#endif // TEST
