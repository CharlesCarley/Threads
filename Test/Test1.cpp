#include "gtest/gtest.h"


GTEST_TEST(Test1, AlwaysTrue)
{
    EXPECT_EQ(1, 1);
}

GTEST_TEST(Test1, AlwaysFalse)
{
    EXPECT_NE(1, 0);
}
