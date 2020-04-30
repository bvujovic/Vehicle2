#ifndef TESTV2

#include "MotorController.h"
#include <UtilsCommon.h>
#include <Sensors.h>

MotorController::MotorController()
{
    pinMode(pinMotorLeft1, OUTPUT);
    pinMode(pinMotorLeft2, OUTPUT);
    pinMode(pinMotorRight1, OUTPUT);
    pinMode(pinMotorRight2, OUTPUT);

    digitalWrite(pinMotorLeft1, false);
    digitalWrite(pinMotorLeft2, false);
    digitalWrite(pinMotorRight1, false);
    digitalWrite(pinMotorRight2, false);
}

// primena PWM signala na pinove odredjene za motor (drajver)
void MotorController::ApplyPWM(PWMs pwm)
{
    cprintln("R pwm 1", pwm.r1);
    cprintln("L pwm 1", pwm.l1);
    analogWrite(pinMotorRight1, pwm.r1);
    analogWrite(pinMotorRight2, pwm.r2);
    analogWrite(pinMotorLeft1, pwm.l1);
    analogWrite(pinMotorLeft2, pwm.l2);
}

void MotorController::Refresh()
{
    if (currCmd == NULL) // ako se trenutno ne izvrsava nijedna komanda
    {
        if (commands.isEmpty())
            return;
        else
            StartNextCmd();
    }
    else // trenutno se izvrsava currCmd
    {
        if (Sensors::ms >= currCmdStarted + currCmd->GetT()) // ako je vreme izvrsavanja tekuce komande isteklo
        {
            PWMs pwm;
            if (currCmd->GetFlags() & MotCmdFlags::Brake)
            {
                pwm.SetBrake();
                ApplyPWM(pwm);
                delay(250);
            }
            pwm.SetStandby();
            ApplyPWM(pwm);

            currCmd = NULL;
            if (!commands.isEmpty())
                Refresh(); // da bi se odmah pokrenula sledeca komanda
            else
                Serial.println("Kraj");
        }
    }
}

void MotorController::AddCmd(MotCmd *cmd)
{
    if (cmd->GetFlags() & MotCmdFlags::Breaking)
        ClearCommands();
    commands.unshift(cmd);
}

void MotorController::StartNextCmd()
{
    currCmd = commands.pop();
    currCmdStarted = millis();
    SerialDisplay::Println("curr cmd", *currCmd);

    LogicSpeeds ls = MotCmdToLogicSpeed(*currCmd);

    // kada se motor(i) pokrece sa jako malom brzinom, 
    // potreban mu je kratak impuls vece snage
    if (ls.HasLowSpeed())
    {
        LogicSpeeds lsBurst = ls.GetBurstLS();
        PWMs pwm = LogicSpeedToPWM(lsBurst);
        ApplyPWM(pwm);
        delay(delayInit);
    }

    PWMs pwm = LogicSpeedToPWM(ls);
    ApplyPWM(pwm);
}

void MotorController::ClearCommands()
{
    while (!commands.isEmpty())
    {
        MotCmd *cmd = commands.shift();
        delete cmd;
    }
    currCmd = NULL;
}

#endif