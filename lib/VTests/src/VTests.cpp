#include "VTests.h"
#include <Statuses.h>
#include <Sensors.h>

MotorController *VTests::motors;
ulong VTests::msTestStart;
VTestsEnum VTests::testKind = VTestsEnum::BalanceMotorsFwd;

void VTests::BalanceMotors(float cmdY)
{
    if (motors->GetCommandsCount() > 0)
    {
        Statuses::Add("Motors cmd collection not empty", "VTests/BalanceMotors");
        return;
    }

    MotCmd *cmd = new MotCmd(0, cmdY, 1000);
    motors->AddCmd(cmd);
    msTestStart = millis();
    testKind = VTestsEnum::BalanceMotorsFwd;
}

void VTests::Refresh()
{
    if (testKind == VTestsEnum::None)
        return;

    ulong msDur = Sensors::ms - msTestStart;
    if (msDur > 2000)
        testKind = VTestsEnum::None;
    if (msDur % 250 < 10)
        Statuses::Add(String("test: ") + testKind + ", ms dur: " + msDur, "VTests/Refresh");
}