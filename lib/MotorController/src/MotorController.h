#pragma once

#include "Arduino.h"
#include "Vector.h"
#include "LogicSpeeds.h"
#include "PWMs.h"

// Neposredno upravljanje radom motora.
class MotorController
{
private:
    const int pinMotorLeft1 = D5;
    const int pinMotorLeft2 = D6;
    const int pinMotorRight1 = D7;
    const int pinMotorRight2 = D8;
    const int delayInit = 5;  // vreme u ms za koje ce motor dobiti maksimalan impuls i to na pocetku kretanja
    const int speedMax = 750; // 2 18650 baterije daju max 8.2V, a motori rade na max 6V. Otuda je najveci PWM 750, ne 1023
    const int speedMin = 200; // ispod ove PWM vrednosti motori ne rade
    //todo Trebace (verovatno posebno za L i R) vrednosti minimalnih brzina (PWM-ova).

public:
    MotorController();

    LogicSpeeds RequestToLogicSpeed(Vector v);
    PWMs LogicSpeedToPWM(LogicSpeeds ls);
    void ApplyPWM(PWMs pwm);
    
    void Go(Vector v, int t, bool brake = true);
};
