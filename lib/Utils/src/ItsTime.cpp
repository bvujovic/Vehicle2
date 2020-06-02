#include <ItsTime.h>
#include <Sensors.h>
#include <Statuses.h>

ItsTime::ItsTime(uint msInterval, bool enabled)
{
    SetInterval(msInterval);
    SetEnabled(enabled);
}

void ItsTime::SetEnabled(bool enabled)
{
    this->enabled = enabled;
    if (enabled)
    {
        msStarted = Sensors::ms;
        cnt = 0;
    }
}

bool ItsTime::IsTick()
{
    if (enabled && (Sensors::ms - msStarted) / msInterval > cnt)
    {
        cnt++;
        return true;
    }
    return false;
}
