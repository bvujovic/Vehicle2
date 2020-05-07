#include <LogicSpeeds.h>

const float LogicSpeeds::LIMIT_LOW_SPEED = 0.51;
const float LogicSpeeds::INIT_BURST_SPEED = 1;

bool LogicSpeeds::HasLowSpeed()
{
    return _abs(l) < LIMIT_LOW_SPEED || _abs(r) < LIMIT_LOW_SPEED;
}

LogicSpeeds LogicSpeeds::GetBurstLS()
{
    LogicSpeeds ls = *this;
    if (_abs(ls.l) < LIMIT_LOW_SPEED)
        ls.l = INIT_BURST_SPEED * _sgn(ls.l);
    if (_abs(ls.r) < LIMIT_LOW_SPEED)
        ls.r = INIT_BURST_SPEED * _sgn(ls.r);
    return ls;
}