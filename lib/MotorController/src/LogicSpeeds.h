#pragma once

#include <ArduinoV2.h>

// Logicke brzine levog i desnog motora. 0 nema kretanja, 1 najbrze unapred, -1 najbrze unazad, 0.1 sporo unapred.
struct LogicSpeeds
{
private:
    static const float LIMIT_LOW_SPEED;
    static const float INIT_BURST_SPEED;

public:
    float r;// logicka brzina desnog motora [-1, 1]
    float l; // logicka brzina levog motora [-1, 1]

    // Da li je bar jednom od motora potreban burst start.
    bool HasLowSpeed();
    // Vraca LogicSpeeds za jak start oba motora.
    LogicSpeeds GetBurstLS();

};