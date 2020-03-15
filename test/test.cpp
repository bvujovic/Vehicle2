#include <Arduino.h>
#include <unity.h>
#include "MotorController.h"
MotorController motors;

// https://github.com/platformio/platformio-examples/tree/develop/unit-testing
// https://docs.platformio.org/en/latest/plus/unit-testing.html#project-examples

// void setUp(void) {
// set stuff up here
// }

// void tearDown(void) {
// clean stuff up here
// }

#pragma region VariousTests

void BuiltinLedPin(void)
{
    TEST_ASSERT_EQUAL(2, LED_BUILTIN);
}

// da li se izbacuje exception pri konverziji stringa koji ne sadrzi validan broj
void TryCatch()
{
    try
    {
        String s = "nije broj";
        s.toFloat();
        TEST_PASS_MESSAGE("String je parsiran");
    }
    catch(const std::exception& e)
    {
        TEST_FAIL_MESSAGE("String nije parsiran");
        Serial.println(e.what());
    }
}

#pragma endregion

#pragma region MotorController

void RequestToLogicSpeed1(void)
{
    Vector v;
    LogicSpeeds res = motors.RequestToLogicSpeed(v);
    TEST_ASSERT_TRUE(res.r == 0 && res.l == 0);
}

#pragma endregion

void setup()
{
    Serial.begin(115200);
    // delay(2000);   // NOTE!!! Wait for >2 secs if board doesn't support software reset via Serial.DTR/RTS
    UNITY_BEGIN();

    RUN_TEST(TryCatch);
    
    RUN_TEST(RequestToLogicSpeed1);

    UNITY_END();
}

void loop()
{
    delay(1000);
}