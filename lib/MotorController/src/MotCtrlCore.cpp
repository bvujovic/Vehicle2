#include "MotCtrlCore.h"
#include <Statuses.h>

// request (MotCmd) -> logic speed
LogicSpeeds MotCtrlCore::MotCmdToLogicSpeed(MotCmd &cmd)
{
    LogicSpeeds ls;
    // init brzine
    ls.r = ls.l = cmd.GetY();

    // spec. slucaj: okretanje vozila u mestu (y=0, x!=0)
    if (cmd.GetY() == 0)
    {
        ls.l = cmd.GetX();
        ls.r = -ls.l;
        return ls;
    }

    // izmena brzina motora u zavisnosti od smera
    ls.r *= 1 - cmd.GetX();
    ls.l *= 1 + cmd.GetX();

    // normalizacija na r, l = [-1, 1]
    float absr = _abs(ls.r);
    float absl = _abs(ls.l);
    float max = _max(absr, absl);
    if (max > 1) // normalizacija je potrebna
    {
        float k = 1 / max;
        ls.r *= k;
        ls.l *= k;
    }

    return ls;
}

short MotCtrlCore::rightPWMs[] = {139, 154, 198, 335, 600};
short MotCtrlCore::leftPWMs[] = {187, 194, 235, 390, 750};

// logic speed -> pwm
PWMs MotCtrlCore::LogicSpeedToPWM(LogicSpeeds ls)
{
    PWMs pwm;
    short lsr4 = ls.r * 4;
    if (lsr4 == ls.r * 4)
        pwm.r1 = rightPWMs[lsr4];
    else
    {
        short base = rightPWMs[lsr4];
        pwm.r1 = base + 4 * (rightPWMs[lsr4 + 1] - base) * (ls.r - lsr4 / 4.0);
    }
    pwm.r2 = 0;
    Statuses::Add(String(pwm.r1), "LogicSpeedToPWM R");

    short lsl4 = ls.l * 4;
    if (lsl4 == ls.l * 4)
        pwm.l1 = leftPWMs[lsl4];
    else
    {
        short base = leftPWMs[lsl4];
        pwm.l1 = base + 4 * (leftPWMs[lsl4 + 1] - base) * (ls.l - lsl4 / 4.0);
    }
    pwm.l2 = 0;
    Statuses::Add(String(pwm.l1), "LogicSpeedToPWM L");

    // pwm.r1 = ls.r == 0 ? 0 : (speedMax - speedMin) * _abs(ls.r) + speedMin;
    // pwm.r2 = 0;
    // pwm.l1 = ls.l == 0 ? 0 : (speedMax - speedMin) * _abs(ls.l) + speedMin;
    // pwm.l2 = 0;

    // if (ls.r < 0)
    //     pwm.ReverseR();
    // if (ls.l < 0)
    //     pwm.ReverseL();

    return pwm;
}