// #include <Arduino.h>
#include <Vector.h>
#include <unity.h>

void setUp(void) {}

void tearDown(void) {}

void vector_def_ctor(void)
{
    Vector v;
    TEST_ASSERT_EQUAL(0, v.GetX());
    TEST_ASSERT_EQUAL(0, v.GetY());
}

void vector_ctor_bounds(void)
{
    Vector v(-5, 2);
    TEST_ASSERT_EQUAL(-1, v.GetX());
    TEST_ASSERT_EQUAL(1, v.GetY());
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(vector_def_ctor);
    RUN_TEST(vector_ctor_bounds);
    UNITY_END();
    return 0;
}
