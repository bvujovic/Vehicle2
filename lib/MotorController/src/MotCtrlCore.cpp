#include "MotCtrlCore.h"

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
PWMs MotCtrlCore::LogicSpeedToPWM(LogicSpeeds ls)
{
    PWMs pwm;
    pwm.r1 = ls.r == 0 ? 0 : (speedMax - speedMin) * abs(ls.r) + speedMin;
    pwm.r2 = 0;
    pwm.l1 = ls.l == 0 ? 0 : (speedMax - speedMin) * abs(ls.l) + speedMin;
    pwm.l2 = 0;

    if (ls.r < 0)
        pwm.ReverseR();
    if (ls.l < 0)
        pwm.ReverseL();

    return pwm;
}