#include <Sensors.h>
#include <Statuses.h>

ulong Sensors::ms;

int Sensors::pinIntR = D4;
int Sensors::pinIntL = D3;

int Sensors::cntR = 0;
int Sensors::cntL = 0;
int Sensors::cntRprev = 0;
int Sensors::cntLprev = 0;
//B ulong Sensors::secs = 0;
ItsTime Sensors::timStatus(1000);

void Sensors::Setup()
{
    pinMode(pinIntR, INPUT_PULLUP);
    pinMode(pinIntL, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pinIntR), handleIntR, FALLING);
    attachInterrupt(digitalPinToInterrupt(pinIntL), handleIntL, FALLING);
}

void Sensors::Refresh()
{
    //B if (ms / 1000 > secs)
    if (timStatus.IsTick())
    {
        if (cntR != cntRprev)
        {
            Statuses::Add(String("cnt R: ") + cntR, "motor hall sensor");
            cntRprev = cntR;
        }
        if (cntL != cntLprev)
        {
            Statuses::Add(String("cnt L: ") + cntL, "motor hall sensor");
            cntLprev = cntL;
        }
        //B secs++;
    }
}