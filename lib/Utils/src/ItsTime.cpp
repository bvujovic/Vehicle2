#include <ItsTime.h>
#include <Sensors.h>

bool ItsTime::IsTick()
{
    if (Sensors::ms / msInterval > cnt)
    {
        cnt++;
        return true;
    }
    return false;
}
