#include "MotorController.h"

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
    analogWrite(pinMotorRight1, pwm.r1);
    analogWrite(pinMotorRight2, pwm.r2);
    analogWrite(pinMotorLeft1, pwm.l1);
    analogWrite(pinMotorLeft2, pwm.l2);
}

void MotorController::Refresh(unsigned long ms)
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
        if (ms >= currCmdStarted + currCmd->GetT()) // ako je vreme izvrsavanja tekuce komande isteklo
        {
            PWMs pwm;
            //* ako je flag za kocenje ukljucen uraditi SetBrake umesto SetStandBy
            pwm.SetStandby(); //* verovatno moze i bez ovog
            ApplyPWM(pwm);
            currCmd = NULL;
            if (!commands.isEmpty())
                Refresh(ms); // da bi se odmah pokrenula sledeca komanda
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
