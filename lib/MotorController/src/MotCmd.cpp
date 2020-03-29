#include "MotCmd.h"

const float MotCmd::MIN = -1;
const float MotCmd::MAX = 1;

MotCmd::MotCmd()
{
    x = y = t = 0;
    flags = (MotCmdFlags)0;
}

MotCmd::MotCmd(float x, float y, int t, MotCmdFlags flags)
{
    SetX(x);
    SetY(y);
    SetT(t);
    SetFlags(flags);
}
