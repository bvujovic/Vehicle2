#include "MotorController.h"
#include "SerialDisplay.h"

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

// request (Vector) -> logic speed
LogicSpeeds MotorController::RequestToLogicSpeed(Vector v)
{
    LogicSpeeds ls;
    // init brzine
    ls.r = ls.l = v.GetY();
    // izmena brzina motora u zavisnosti od smera
    ls.r *= 1 - v.GetX();
    ls.l *= 1 + v.GetX();

    // normalizacija na r, l = [-1, 1]
    float absr = abs(ls.r);
    float absl = abs(ls.l);
    float max = _max(absr, absl);
    if (max > 1) // normalizacija je potrebna
    {
        float k = 1 / max;
        ls.r *= k;
        ls.l *= k;
    }

    return ls;
}

// logic speed -> pwm
PWMs MotorController::LogicSpeedToPWM(LogicSpeeds ls)
{
    PWMs pwm;
    pwm.r1 = ls.r == 0 ? 0 : (speedMax - speedMin) * fabs(ls.r) + speedMin;
    pwm.r2 = 0;
    pwm.l1 = ls.l == 0 ? 0 : (speedMax - speedMin) * fabs(ls.l) + speedMin;
    pwm.l2 = 0;

    if (ls.r < 0)
        pwm.ReverseR();
    if (ls.l < 0)
        pwm.ReverseL();

    return pwm;
}

// primena PWM signala na pinove odredjene za motor (drajver)
void MotorController::ApplyPWM(PWMs pwm)
{
    analogWrite(pinMotorRight1, pwm.r1);
    analogWrite(pinMotorRight2, pwm.r2);
    analogWrite(pinMotorLeft1, pwm.l1);
    analogWrite(pinMotorLeft2, pwm.l2);
}

void MotorController::Go(Vector v, int t, bool brake)
{
    LogicSpeeds ls = RequestToLogicSpeed(v);
    PWMs pwm = LogicSpeedToPWM(ls);

    if (v.IsZero())
    {
        Serial.println("Stop\n");
        if (brake)
        {
            //T Serial.println("Koci!\n");
            pwm.SetBrake();
            ApplyPWM(pwm);
            delay(200);
        }
        pwm.SetStandby();
    }
    else
    {
        SerialDisplay::Println("LS", ls);
        SerialDisplay::Println("PWM", pwm);
    }
    ApplyPWM(pwm);

    if (!v.IsZero())
    {
        delay(t);
        Vector stop;
        Go(stop, brake);
    }
}