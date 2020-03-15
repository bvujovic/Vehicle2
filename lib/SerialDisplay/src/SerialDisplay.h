#pragma once

#include "Arduino.h"
#include "LogicSpeeds.h"
#include "PWMs.h"

class SerialDisplay
{
public:
    static void Println(String caption, LogicSpeeds ls);
    static void Println(String caption, PWMs pwm);
};
