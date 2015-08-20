#include "gtest/gtest.h"
#include "../../../include/ney/ney.hpp"
#include <unistd.h>

#define ERROR 0.000001

/*
    Tests of operations involving a condition
*/

TEST(Condition, SingleVectorSwapCondition)
{
    ney::status s;

    ney::vector<double> v1 = ney::new_vector().size(7);
    ney::vector<int> v2 = ney::new_vector().size(7);

    v1 << 1.3 << -2.1 << 8.2 << 4.4 << 5.1 << 6.2 << 0.2;

    // GT

    s = ney::swap<double>().vector1(v1).condition(ney::condition::gt);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_DOUBLE_EQ(v1[0], 1.3);
    EXPECT_DOUBLE_EQ(v1[1], -2.1);
    EXPECT_DOUBLE_EQ(v1[2], 6.2);
    EXPECT_DOUBLE_EQ(v1[3], 4.4);
    EXPECT_DOUBLE_EQ(v1[4], 5.1);
    EXPECT_DOUBLE_EQ(v1[5], 8.2);
    EXPECT_DOUBLE_EQ(v1[6], 0.2);

    // LT

    v1.reset();
    v1 << 1.3 << -2.1 << 8.2 << 4.4 << 5.1 << 6.2 << 0.2;

    s = ney::swap<double>().vector1(v1).condition(ney::condition::lt);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_DOUBLE_EQ(v1[0], 4.4);
    EXPECT_DOUBLE_EQ(v1[1], 5.1);
    EXPECT_DOUBLE_EQ(v1[2], 8.2);
    EXPECT_DOUBLE_EQ(v1[3], 1.3);
    EXPECT_DOUBLE_EQ(v1[4], -2.1);
    EXPECT_DOUBLE_EQ(v1[5], 6.2);
    EXPECT_DOUBLE_EQ(v1[6], 0.2);

    // int LT

    v2 << 10 << 5 << 5 << 0 << 2 << 15 << 3;

    s = ney::swap<int>().vector1(v2).condition(ney::condition::lt);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_DOUBLE_EQ(v2[0], 10);
    EXPECT_DOUBLE_EQ(v2[1], 5);
    EXPECT_DOUBLE_EQ(v2[2], 15);
    EXPECT_DOUBLE_EQ(v2[3], 0);
    EXPECT_DOUBLE_EQ(v2[4], 2);
    EXPECT_DOUBLE_EQ(v2[5], 5);
    EXPECT_DOUBLE_EQ(v2[6], 3);

    // int GT

    v2.reset();
    v2 << 10 << 5 << 5 << 0 << 2 << 15 << 3;

    s = ney::swap<int>().vector1(v2).condition(ney::condition::gt);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_DOUBLE_EQ(v2[0], 0);
    EXPECT_DOUBLE_EQ(v2[1], 2);
    EXPECT_DOUBLE_EQ(v2[2], 5);
    EXPECT_DOUBLE_EQ(v2[3], 10);
    EXPECT_DOUBLE_EQ(v2[4], 5);
    EXPECT_DOUBLE_EQ(v2[5], 15);
    EXPECT_DOUBLE_EQ(v2[6], 3);

}

TEST(Condition, TwoVectorsSwapCondition)
{
    ney::status s;

    ney::vector<double> v1 = ney::new_vector().size(5);
    ney::vector<double> v2 = ney::new_vector().size(5);
    ney::vector<int> v3 = ney::new_vector().size(7);
    ney::vector<int> v4 = ney::new_vector().size(7);

    // ints first (gt)

    v3 << 5 << 2 << 7 << 2 << 44 << 1 << 0;
    v4 << 9 << 2 << 6 << 8 << 24 << 13 << -1;

    s = ney::swap<int>().vector1(v3).vector2(v4).condition(ney::condition::gt);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_EQ(v3[0], 5);
    EXPECT_EQ(v3[1], 2);
    EXPECT_EQ(v3[2], 6);
    EXPECT_EQ(v3[3], 2);
    EXPECT_EQ(v3[4], 24);
    EXPECT_EQ(v3[5], 1);
    EXPECT_EQ(v3[6], -1);

    EXPECT_EQ(v4[0], 9);
    EXPECT_EQ(v4[1], 2);
    EXPECT_EQ(v4[2], 7);
    EXPECT_EQ(v4[3], 8);
    EXPECT_EQ(v4[4], 44);
    EXPECT_EQ(v4[5], 13);
    EXPECT_EQ(v4[6], 0);

    // doubles (lt)

    v1 << 1.3 << 5.2 << -3.2 << 5.15 << 0.01;
    v2 << -1.3 << 2.2 << 3.2 << 5.5 << 1.01;

    s = ney::swap<double>().vector1(v1).vector2(v2).condition(ney::condition::lt);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_DOUBLE_EQ(v1[0], 1.3);
    EXPECT_DOUBLE_EQ(v1[1], 5.2);
    EXPECT_DOUBLE_EQ(v1[2], 3.2);
    EXPECT_DOUBLE_EQ(v1[3], 5.5);
    EXPECT_DOUBLE_EQ(v1[4], 1.01);

    EXPECT_DOUBLE_EQ(v2[0], -1.3);
    EXPECT_DOUBLE_EQ(v2[1], 2.2);
    EXPECT_DOUBLE_EQ(v2[2], -3.2);
    EXPECT_DOUBLE_EQ(v2[3], 5.15);
    EXPECT_DOUBLE_EQ(v2[4], 0.01);
}

// user's function

bool users_fun(const int* a, const int* b)
{
    if (*a + 3 > *b)
        return true;
    else
        return false;
}

TEST(Condition, UsersFunction)
{
    ney::status s;

    ney::vector<int> v1 = ney::new_vector().size(5);
    ney::vector<int> v2 = ney::new_vector().size(5);

    v1 << 7 << 2 << 7 << 2 << 44;
    v2 << 9 << 2 << 6 << 8 << 24;

    s = ney::swap<int>().vector1(v1).vector2(v2).condition(users_fun);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_EQ(v1[0], 9);
    EXPECT_EQ(v1[1], 2);
    EXPECT_EQ(v1[2], 6);
    EXPECT_EQ(v1[3], 2);
    EXPECT_EQ(v1[4], 24);

    EXPECT_EQ(v2[0], 7);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 7);
    EXPECT_EQ(v2[3], 8);
    EXPECT_EQ(v2[4], 44);
}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
