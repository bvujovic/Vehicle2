#include "VTests.h"
#include <Statuses.h>
#include <Sensors.h>

MotorController *VTests::motors;
ulong VTests::msTestStart;
VTestsEnum VTests::testKind = VTestsEnum::NoTests;
uint VTests::cntR;
uint VTests::cntL;

void VTests::StartTest(VTestsEnum testKind, uint y)
{
    VTests::testKind = testKind;
    if (testKind == VTestsEnum::BalanceMotorsMinSpeedFwd)
    {
        PWMs pwmBurst(0.8 * PWMRANGE, 0, 0.8 * PWMRANGE, 0);
        motors->ApplyPWM(pwmBurst);
        delay(5);

        PWMs pwm(y, 0, y, 0);
        motors->ApplyPWM(pwm);

        msTestStart = Sensors::ms;
        cntR = cntL = 0;
        AddStatus(0);
    }
}

void VTests::AddStatus(ulong msDur)
{
    Statuses::Add(new Status(String("cntR: ") + (Sensors::GetEncoderCntR() - cntR), "VTests", msDur));
    cntR = Sensors::GetEncoderCntR();
    Statuses::Add(new Status(String("cntL: ") + (Sensors::GetEncoderCntL() - cntL), "VTests", msDur));
    cntL = Sensors::GetEncoderCntL();
}

void VTests::Refresh()
{
    if (testKind == VTestsEnum::NoTests)
        return;

    ulong msDur = Sensors::ms - msTestStart;
    if (msDur > 2000) // zaustavljanje testa
    {
        Statuses::Add("Test stopped", "VTests");
        testKind = VTestsEnum::NoTests;
        PWMs pwm;
        motors->ApplyPWM(pwm);
    }
    if (msDur % 250 < 10) // zapisivanje medjurezultata
        AddStatus(msDur);
}
