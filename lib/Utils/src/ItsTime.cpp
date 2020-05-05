#include <ItsTime.h>
#include <Sensors.h>

bool ItsTime::IsTick()
{
    if (enabled && Sensors::ms / msInterval > cnt)
    {
        cnt++;
        return true;
    }
    return false;
}
