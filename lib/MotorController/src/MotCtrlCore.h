#pragma once

#include <LogicSpeeds.h>
#include <MotCmd.h>
#include <PWMs.h>

// Bazna klasa za MotorController. Ovde ce biti sve sto moze da se testira na racunaru, tj. nema veze sa Arduino.h
class MotCtrlCore
{
protected:
    int speedMax = 750; // 2 18650 baterije daju max 8.2V, a motori rade na max 6V. Otuda je najveci PWM 750, ne 1023
    int speedMin = 200; // ispod ove PWM vrednosti motori ne rade
    static float leftCoef;

    static short rightPWMs[];
    static short leftPWMs[];

public:
    LogicSpeeds MotCmdToLogicSpeed(MotCmd &cmd);
    PWMs LogicSpeedToPWM(LogicSpeeds ls);

    static void SetLeftCoef(float coef) { leftCoef = coef; }
};
