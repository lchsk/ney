#include "gtest/gtest.h"
#include "../../../include/ney/ney.hpp"

#include <unistd.h>

#define ERROR 0.000001

/*
    Tests of basic operations.
*/

TEST(BasicOperations, Fill)
{
    ney::config.target = ney::GPU;

    ney::vector<int> v = ney::new_vector().size(11);
    ney::status s;

    // Check default settings of a status object
    EXPECT_FALSE(s.success());
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
        EXPECT_LE(v[i], 10);
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

    v2.set(0, 2.5);
    v2.set(1, -923.55);
    v2.set(2, 2.5);
    v2.set(3, 0.1244);
    v2.set(4, -923.55);

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
//
TEST(BasicOperations, Replace)
{
    ney::status s;

    ney::vector<int> v1 = ney::new_vector().size(5);
    ney::vector<double> v2 = ney::new_vector().size(5);

    v1.set(0, 1);
    v1.set(1, 10);
    v1.set(2, 50);
    v1.set(3, 10);
    v1.set(4, 50);

    v2.set(0, 0.1);
    v2.set(1, 0.1);
    v2.set(2, 0.3);
    v2.set(3, 5.1);
    v2.set(4, 0.3);

    // Expect errors in status object

    s = ney::replace<double>(2.5);

    EXPECT_FALSE(s.success());

    // TODO: that should also cause an error
    // s = ney::replace<double>(2.5).in(v2);

    // EXPECT_FALSE(s.success());

    s = ney::replace<double>(2.5).with(2.1);

    EXPECT_FALSE(s.success());

    // It should be correct, but no values will be replaced

    s = ney::replace<double>(2.5).with(1.2).in(v2);

    EXPECT_TRUE(s.success());

    int count;
    s = ney::count<double>(2.5).in(v2).output(count);

    EXPECT_EQ(count, 0);

    // That should work

    s = ney::replace<double>(0.3).with(-0.3).in(v2);

    EXPECT_TRUE(s.success());

    s = ney::count<double>(-0.3).in(v2).output(count);

    EXPECT_EQ(count, 2);

    // Replacing integers

    s = ney::replace<int>(10).with(100).in(v1);

    EXPECT_TRUE(s.success());

    s = ney::count<int>(100).in(v1).output(count);

    EXPECT_EQ(count, 2);

    // Replacing doubles with changed precision

    s = ney::replace<double>(0.1).with(0.01).in(v2).precision(0.0001);

    EXPECT_TRUE(s.success());

    s = ney::count<double>(0.01).in(v2).output(count);

    EXPECT_EQ(count, 2);
}
//
// TEST(BasicOperations, Swap)
// {
//     ney::status s;
//
//     ney::vector<double> v1 = ney::new_vector().size(5);
//     ney::vector<double> v2 = ney::new_vector().size(6);
//
//     v1 << 2.1 << 5.2 << 6.6 << -0.01 << 30.5;
//     v2 << 0.2 << 0.5 << 0.2 << 0.67 << 0.23 << 0.21;
//
//     // test swapping values inside a single vector
//
//     s = ney::swap<double>().vector1(v1);
//
//     EXPECT_TRUE(s.success());
//
//     EXPECT_DOUBLE_EQ(v1[0], 6.6);
//     EXPECT_DOUBLE_EQ(v1[1], -0.01);
//     EXPECT_DOUBLE_EQ(v1[2], 2.1);
//     EXPECT_DOUBLE_EQ(v1[3], 5.2);
//     EXPECT_DOUBLE_EQ(v1[4], 30.5);
//
//     s = ney::swap<double>().vector1(v2);
//
//     EXPECT_TRUE(s.success());
//
//     EXPECT_DOUBLE_EQ(v2[0], 0.67);
//     EXPECT_DOUBLE_EQ(v2[1], 0.23);
//     EXPECT_DOUBLE_EQ(v2[2], 0.21);
//     EXPECT_DOUBLE_EQ(v2[3], 0.2);
//     EXPECT_DOUBLE_EQ(v2[4], 0.5);
//     EXPECT_DOUBLE_EQ(v2[5], 0.2);
//
//     // test swapping two vectors
//
//     v1.reset();
//     v2.reset();
//
//     // change size of v1
//
//     v1 = ney::new_vector().size(6);
//
//     EXPECT_EQ(v1.size(), 6);
//     EXPECT_EQ(v1.length(), 6);
//
//     v1 << 0.1 << 0.2 << 0.3 << 0.4 << 0.5 << 0.6;
//     v2 << 1.1 << 1.2 << 1.3 << 1.4 << 1.5 << 1.6;
//
//     s = ney::swap<double>().vector1(v1).vector2(v2);
//
//     EXPECT_DOUBLE_EQ(v1[0], 1.1);
//     EXPECT_DOUBLE_EQ(v1[1], 1.2);
//     EXPECT_DOUBLE_EQ(v1[2], 1.3);
//     EXPECT_DOUBLE_EQ(v1[3], 1.4);
//     EXPECT_DOUBLE_EQ(v1[4], 1.5);
//     EXPECT_DOUBLE_EQ(v1[5], 1.6);
//
//     EXPECT_DOUBLE_EQ(v2[0], 0.1);
//     EXPECT_DOUBLE_EQ(v2[1], 0.2);
//     EXPECT_DOUBLE_EQ(v2[2], 0.3);
//     EXPECT_DOUBLE_EQ(v2[3], 0.4);
//     EXPECT_DOUBLE_EQ(v2[4], 0.5);
//     EXPECT_DOUBLE_EQ(v2[5], 0.6);
//
//     // check swapping with a slice
//
//     v1.reset();
//     v2.reset();
//
//     v1 << 0.1 << 0.2 << 0.3 << 0.4 << 0.5 << 0.6;
//     v2 << 1.1 << 1.2 << 1.3 << 1.4 << 1.5 << 1.6;
//
//     s = ney::swap<double>().vector1(v1.stride(2)).vector2(v2.stride(2));
//
//     EXPECT_DOUBLE_EQ(v1[0], 1.1);
//     EXPECT_DOUBLE_EQ(v1[1], 0.2);
//     EXPECT_DOUBLE_EQ(v1[2], 1.3);
//     EXPECT_DOUBLE_EQ(v1[3], 0.4);
//     EXPECT_DOUBLE_EQ(v1[4], 1.5);
//     EXPECT_DOUBLE_EQ(v1[5], 0.6);
//
//     EXPECT_DOUBLE_EQ(v2[0], 0.1);
//     EXPECT_DOUBLE_EQ(v2[1], 1.2);
//     EXPECT_DOUBLE_EQ(v2[2], 0.3);
//     EXPECT_DOUBLE_EQ(v2[3], 1.4);
//     EXPECT_DOUBLE_EQ(v2[4], 0.5);
//     EXPECT_DOUBLE_EQ(v2[5], 1.6);
//
// }

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
