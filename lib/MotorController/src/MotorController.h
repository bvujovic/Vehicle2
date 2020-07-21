#ifndef TESTV2
#pragma once

#include <ArduinoV2.h>
#include "MotCmd.h"
#include "LogicSpeeds.h"
#include "PWMs.h"
#include "SerialDisplay.h"
#include <CircularBuffer.h>
#include <MotCtrlCore.h>

// Neposredno upravljanje radom motora.
class MotorController : public MotCtrlCore
{
private:
    const int pinMotorLeft1 = D5;
    const int pinMotorLeft2 = D6;
    const int pinMotorRight1 = D7;
    const int pinMotorRight2 = D8;
    const int delayInit = 5; // vreme u ms za koje ce motor dobiti maksimalan impuls i to na pocetku kretanja
    //todo Trebace (verovatno posebno za L i R) vrednosti minimalnih brzina (PWM-ova).

    CircularBuffer<MotCmd *, 100> commands;
    unsigned long currCmdStarted = 0; // vreme pocetka (u ms) tekuce komande
    MotCmd *currCmd;                  // komanda u izvrsavanju
    void StartNextCmd();
    void ClearCommands();

public:
    MotorController();

    // Direktna kontrola motora slanjem PWM nivoa
    void ApplyPWM(PWMs pwm);
    void AddCmd(MotCmd *cmd);
    void Refresh();
    int GetCommandsCount() { return commands.size(); }
};

#endif