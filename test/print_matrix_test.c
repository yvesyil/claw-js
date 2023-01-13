#include "unity/unity.h"
#include <stdio.h>

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test1()
{
    TEST_ASSERT(1<2);
}

void test2()
{
    TEST_ASSERT(10==10);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test1);
    RUN_TEST(test2);
    return UNITY_END();
}
