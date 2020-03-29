#pragma once

#include <ArduinoV2.h>

// ...
struct LogicSpeeds
{
private:
    static const float LIMIT_LOW_SPEED;
    static const float INIT_BURST_SPEED;

public:
    float r; // logicka brzina desnog motora [-1, 1]
    float l; // logicka brzina levog motora [-1, 1]

    // Da li je bar jednom od motora potreban burst start.
    bool HasLowSpeed();
    // Vraca LogicSpeeds za jak start oba motora.
    LogicSpeeds GetBurstLS();

};