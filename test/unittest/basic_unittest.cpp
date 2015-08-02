#include "gtest/gtest.h"
#include "../../../include/ney/ney.hpp"

#include <unistd.h>

#define ERROR 0.000001

/*
    Tests of basic operations.
*/

TEST(BasicOperations, Fill)
{
    // Make sure default target is Intel

    EXPECT_EQ(ney::config.target, ney::Intel);

    ney::vector<int> v = ney::new_vector().size(11);
    ney::status s;

    // Check default settings of a status object
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    // fill
    s = ney::fill<int>(v).value(2);

    for (int i = 0; i < 11; i++)
        EXPECT_EQ(v[i], 2);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    // use slicing when filling
    s =  ney::fill<int>(v.from(1).to(5).stride(2)).value(5).time();

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[1], 5);
    EXPECT_EQ(v[2], 2);
    EXPECT_EQ(v[3], 5);
    EXPECT_EQ(v[4], 2);
    EXPECT_EQ(v[5], 2);
    EXPECT_EQ(v[6], 2);

    // it should be possible to call a function without a status object with run() function
    // but without status it is not possible to check if parameters are correct
    ney::fill<int>(v.reset()).value(10).run();

    for (int i = 0; i < 11; i++)
        EXPECT_EQ(v[i], 10);
}

TEST(BasicOperations, Random)
{
    ney::vector<int> v = ney::new_vector().size(5);
    ney::status s;

    // Expect an error

    s = ney::random<int>(v).min(10).max(5);

    EXPECT_FALSE(s.success());
    EXPECT_NE(s.error(), "");

    // That should be ok
    s = ney::random<int>(v).min(5).max(10);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    for (int i = 0; i < 5; i++)
    {
        EXPECT_LT(v[i], 10);
        EXPECT_GE(v[i], 5);
    }
}

TEST(BasicOperations, Count)
{
    ney::vector<int> v = ney::new_vector().size(7);
    ney::status s;

    // Expect an error

    s = ney::fill<int>(v).value(5);

    // Check if vector is initialised correctly

    for (int i = 0; i < 7; i++)
        EXPECT_EQ(v[i], 5);

    // Expect it to work ok

    int count;
    s = ney::count<int>(5).in(v).output(count);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_EQ(count, 7);

    s = ney::count<int>(5).in(v).output(count);

    // Expect 0 as a result

    s = ney::count<int>(6).in(v).output(count);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_EQ(count, 0);

    // Count values in a vector slice

    s = ney::count<int>(5).in(v.stride(2).from(1)).output(count);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_EQ(count, 3);

    // Count floating point values

    ney::vector<double> v2 = ney::new_vector().size(5);

    v2[0] = 2.5;
    v2[1] = -923.55;
    v2[2] = 2.5;
    v2[3] = 0.1244;
    v2[4] = -923.55;

    s = ney::count<double>(2.5).in(v2).output(count);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_EQ(count, 2);

    // Expect errors in status object

    s = ney::count<double>(2.5).output(count);

    EXPECT_FALSE(s.success());

    s = ney::count<double>(2.5);

    EXPECT_FALSE(s.success());

    s = ney::count<double>(2.5).in(v2);

    EXPECT_FALSE(s.success());
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
