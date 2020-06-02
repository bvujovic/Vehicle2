#include <Sensors.h>
#include <Statuses.h>

ulong Sensors::ms;

uint Sensors::pinIntR = D2;
uint Sensors::pinIntL = D1;

uint Sensors::cntR = 0;
uint Sensors::cntL = 0;
uint Sensors::cntRprev = 0;
uint Sensors::cntLprev = 0;
ItsTime Sensors::timStatus(1000, true);

void Sensors::Setup()
{
    pinMode(pinIntR, INPUT_PULLUP);
    pinMode(pinIntL, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pinIntR), handleIntR, FALLING);
    attachInterrupt(digitalPinToInterrupt(pinIntL), handleIntL, FALLING);
}

void Sensors::Refresh()
{
    if (timStatus.IsTick())
    {
        if (cntR != cntRprev)
        {
            Statuses::Add(String(cntR - cntRprev), "R motor encoder");
            cntRprev = cntR;
        }
        if (cntL != cntLprev)
        {
            Statuses::Add(String(cntL - cntLprev), "L motor encoder");
            cntLprev = cntL;
        }
    }
}

void Sensors::TimStatusStart(uint msInterval)
{
    if (msInterval != 0)
        timStatus.SetInterval(msInterval);
    timStatus.SetEnabled(true);
}