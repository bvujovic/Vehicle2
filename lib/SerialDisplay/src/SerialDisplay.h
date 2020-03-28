#pragma once

#include "ArduinoV2.h"
#include "LogicSpeeds.h"
#include "PWMs.h"
#include "MotCmd.h"

class SerialDisplay
{
public:
    static void Println(String caption, LogicSpeeds ls);
    static void Println(String caption, PWMs pwm);
    static void Println(String caption, MotCmd &cmd);
};
