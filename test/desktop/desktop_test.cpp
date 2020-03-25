// #include <Arduino.h>
#include <MotCmd.h>
#include "CircularBuffer.h"
#include <unity.h>
#include "Enums.h"

// void setUp(void) {}

// void tearDown(void) {}

#pragma region MotCmd

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

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(MotCmd_def_ctor);
    RUN_TEST(MotCmd_ctor_bounds);
    
    RUN_TEST(circ_buffer_init);
    RUN_TEST(circ_buffer_fifo);
    RUN_TEST(circ_buffer_nondestructive);

    RUN_TEST(MotCmdFlags_test);

    UNITY_END();
    return 0;
}
