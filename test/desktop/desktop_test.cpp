#include <MotCmd.h>
#include <LogicSpeeds.h>
#include <MotCtrlCore.h>
#include <CircularBuffer.h>
#include <unity.h>
#include <Enums.h>

// void setUp(void) {}

// void tearDown(void) {}

#pragma region MotCmd

void MotCmdFlags_test()
{
    MotCmdFlags f = (MotCmdFlags)0;
    TEST_ASSERT_FALSE(f & MotCmdFlags::Breaking);
    TEST_ASSERT_FALSE(f & MotCmdFlags::Brake);

    f = MotCmdFlags::Breaking;
    TEST_ASSERT_TRUE(f & MotCmdFlags::Breaking);
    TEST_ASSERT_FALSE(f & MotCmdFlags::Brake);

    f = (MotCmdFlags)3;
    TEST_ASSERT_TRUE(f & MotCmdFlags::Breaking);
    TEST_ASSERT_TRUE(f & MotCmdFlags::Brake);
}

void MotCmd_def_ctor(void)
{
    MotCmd cmd;
    TEST_ASSERT_EQUAL(0, cmd.GetX());
    TEST_ASSERT_EQUAL(0, cmd.GetY());
    TEST_ASSERT_EQUAL(0, cmd.GetT());
    TEST_ASSERT_FALSE(cmd.GetFlags() & MotCmdFlags::Breaking || cmd.GetFlags() & MotCmdFlags::Brake);
}

void MotCmd_ctor_bounds(void)
{
    MotCmd cmd(-5, 2, 1200, MotCmdFlags::Breaking);
    TEST_ASSERT_EQUAL(-1, cmd.GetX());
    TEST_ASSERT_EQUAL(1, cmd.GetY());
    TEST_ASSERT_EQUAL(1200, cmd.GetT());
    TEST_ASSERT_TRUE(cmd.GetFlags() & MotCmdFlags::Breaking);
    TEST_ASSERT_FALSE(cmd.GetFlags() & MotCmdFlags::Brake);
}

#pragma endregion

#pragma region MotCtrlCore

void MotCtrlCore_MotCmdToLogicSpeed()
{
    MotCtrlCore mc;
    MotCmd *cmd = new MotCmd(); // def konstruktor - mirovanje vozila
    LogicSpeeds ls = mc.MotCmdToLogicSpeed(*cmd);
    TEST_ASSERT_EQUAL(0, ls.l);
    TEST_ASSERT_EQUAL(0, ls.r);

    cmd = new MotCmd(0, 0.5, 1000); // srednja brzina, napred, bez skretanja
    ls = mc.MotCmdToLogicSpeed(*cmd);
    TEST_ASSERT_EQUAL(0.5, ls.l);
    TEST_ASSERT_EQUAL(0.5, ls.r);

    cmd = new MotCmd(0.1, 0.5, 1000); // srednja brzina, blago skretanje udesno
    ls = mc.MotCmdToLogicSpeed(*cmd);
    TEST_ASSERT_TRUE(ls.l > 0.5);
    TEST_ASSERT_TRUE(ls.r < 0.5);

    cmd = new MotCmd(-0.2, 1, 1000); // max brzina, blago skretanje ulevo
    ls = mc.MotCmdToLogicSpeed(*cmd);
    TEST_ASSERT_TRUE(ls.r == 1);
    TEST_ASSERT_TRUE(ls.l > 0.5);

    cmd = new MotCmd(0.3, 0, 1000); // okretanje vozila u mestu udesno
    ls = mc.MotCmdToLogicSpeed(*cmd);
    TEST_ASSERT_EQUAL(ls.r, -0.3);
    TEST_ASSERT_EQUAL(ls.l, 0.3);

    cmd = new MotCmd(-1, 0, 1000); // okretanje vozila u mestu ulevo, max brzina
    ls = mc.MotCmdToLogicSpeed(*cmd);
    TEST_ASSERT_EQUAL(ls.r, 1);
    TEST_ASSERT_EQUAL(ls.l, -1);
}

#pragma endregion

#pragma region CircularBuffer

void circ_buffer_init()
{
    CircularBuffer<MotCmd, 100> cmds;
    TEST_ASSERT_EQUAL(100, cmds.capacity);
    TEST_ASSERT_TRUE(cmds.isEmpty());
}

void circ_buffer_fifo()
{
    CircularBuffer<int, 10> ints;
    ints.unshift(1);
    ints.unshift(2);
    ints.unshift(3);
    TEST_ASSERT_EQUAL(1, ints.pop());
    TEST_ASSERT_EQUAL(2, ints.pop());
    ints.unshift(4);
    TEST_ASSERT_EQUAL(3, ints.pop());
    TEST_ASSERT_EQUAL(4, ints.pop());
    TEST_ASSERT_TRUE(ints.isEmpty());
}

void circ_buffer_nondestructive()
{
    CircularBuffer<int, 10> ints;
    ints.unshift(5);
    ints.unshift(6);
    TEST_ASSERT_EQUAL(5, ints.last()); //* ovo je glupo, 5 treba da je prvi
    TEST_ASSERT_EQUAL(6, ints[0]);
    TEST_ASSERT_EQUAL(2, ints.size());
}

#pragma endregion

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(MotCmdFlags_test);
    RUN_TEST(MotCmd_def_ctor);
    RUN_TEST(MotCmd_ctor_bounds);

    RUN_TEST(MotCtrlCore_MotCmdToLogicSpeed);

    RUN_TEST(circ_buffer_init);
    RUN_TEST(circ_buffer_fifo);
    RUN_TEST(circ_buffer_nondestructive);

    UNITY_END();
    return 0;
}
