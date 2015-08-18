#include "gtest/gtest.h"
#include "../../../include/ney/ney.hpp"

#include <unistd.h>

#define ERROR 0.000001

/*
    Tests of sort-based operations
*/

TEST(Sort, MergeSort)
{
    // Set up everything

    ney::status s;
    ney::vector<int> v1 = ney::new_vector().size(7);
    ney::vector<double> v2 = ney::new_vector().size(7);
    ney::vector<int> v3 = ney::new_vector().size(6);
    ney::vector<double> v4 = ney::new_vector().size(6);

    // Check for already sorted array

    v1 << 1 << 2 << 3 << 4 << 5 << 6 << 7;
    v2 << 0.1 << 0.2 << 0.3 << 0.4 << 0.5 << 0.6 << 0.7;
    v3 << 10 << 20 << 30 << 40 << 50 << 60;
    v4 << 1.1 << 1.2 << 1.3 << 1.4 << 1.5 << 1.6;

    s = ney::sort<int>(v1);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 6; i++)
        EXPECT_LE(v1[i], v1[i + 1]);

    s = ney::sort<double>(v2);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 6; i++)
        EXPECT_LE(v2[i], v2[i + 1]);

    s = ney::sort<int>(v3);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 5; i++)
        EXPECT_LE(v3[i], v3[i + 1]);

    s = ney::sort<double>(v4);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 5; i++)
        EXPECT_LE(v4[i], v4[i + 1]);

    // Check if sorting is correct if given a vector sorted in descending order

    v1.reset();
    v2.reset();
    v3.reset();
    v4.reset();

    v1 << 100 << 90 << 80 << 70 << 60 << 50 << 40;
    v2 << -1.1 << -1.0 << -0.9 << -0.8 << -0.7 << -0.6 << -0.5;
    v3 << 66 << 55 << 44 << 33 << 22 << 11;
    v4 << 6.6 << 5.5 << 4.4 << 3.3 << 2.2 << 1.1;

    s = ney::sort<int>(v1);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 6; i++)
        EXPECT_LE(v1[i], v1[i + 1]);

    s = ney::sort<double>(v2);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 6; i++)
        EXPECT_LE(v2[i], v2[i + 1]);

    s = ney::sort<int>(v3);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 5; i++)
        EXPECT_LE(v3[i], v3[i + 1]);

    s = ney::sort<double>(v4);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 5; i++)
        EXPECT_LE(v4[i], v4[i + 1]);

    // Sorting random vectors

    v1.reset();
    v2.reset();
    v3.reset();
    v4.reset();

    s = ney::random<int>(v1).min(-100).max(500);
    s = ney::random<double>(v2).min(0.0).max(1.0);
    s = ney::random<int>(v3).min(600).max(612);
    s = ney::random<double>(v4).min(-0.9).max(1.5);

    s = ney::sort<int>(v1);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 6; i++)
        EXPECT_LE(v1[i], v1[i + 1]);

    s = ney::sort<double>(v2);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 6; i++)
        EXPECT_LE(v2[i], v2[i + 1]);

    s = ney::sort<int>(v3);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 5; i++)
        EXPECT_LE(v3[i], v3[i + 1]);

    s = ney::sort<double>(v4);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 5; i++)
        EXPECT_LE(v4[i], v4[i + 1]);
}

TEST(Sort, Unique)
{
    // Set up everything

    ney::status s;

    ney::vector<int> v1 = ney::new_vector().size(7);
    ney::vector<int> v2 = ney::new_vector().size(6);
    ney::vector<double> v3 = ney::new_vector().size(7);
    ney::vector<double> v4 = ney::new_vector().size(6);

    v1 << 3 << 6 << 2 << 7 << 2 << 3 << 6;
    v2 << 2 << 6 << 3 << 5 << 5 << 2;

    v3 << 0.3 << 0.6 << 0.2 << 0.6 << 0.2 << 0.3 << 0.424;
    v4 << 0.1 << 0.2 << 0.2 << 0.64 << 0.1 << 0.5;

    // typical examples

    // int, 7

    s = ney::unique<int>(v1);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    // length of the output vector

    EXPECT_EQ(v1.length(), 4);

    // values in the output vector should be sorted
    // because current implementation uses ney::sort

    EXPECT_EQ(v1[0], 2);
    EXPECT_EQ(v1[1], 3);
    EXPECT_EQ(v1[2], 6);
    EXPECT_EQ(v1[3], 7);

    // int, 6

    s = ney::unique<int>(v2);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    // length of the output vector

    EXPECT_EQ(v2.length(), 4);

    // values in the output vector should be sorted
    // because current implementation uses ney::sort

    EXPECT_EQ(v2[0], 2);
    EXPECT_EQ(v2[1], 3);
    EXPECT_EQ(v2[2], 5);
    EXPECT_EQ(v2[3], 6);

    // double, 7

    s = ney::unique<double>(v3);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    // length of the output vector

    EXPECT_EQ(v3.length(), 4);

    // values in the output vector should be sorted
    // because current implementation uses ney::sort

    EXPECT_NEAR(v3[0], 0.2, ERROR);
    EXPECT_NEAR(v3[1], 0.3, ERROR);
    EXPECT_NEAR(v3[2], 0.424, ERROR);
    EXPECT_NEAR(v3[3], 0.6, ERROR);

    // double, 6

    s = ney::unique<double>(v4);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    // length of the output vector

    EXPECT_EQ(v4.length(), 4);

    // values in the output vector should be sorted
    // because current implementation uses ney::sort

    EXPECT_NEAR(v4[0], 0.1, ERROR);
    EXPECT_NEAR(v4[1], 0.2, ERROR);
    EXPECT_NEAR(v4[2], 0.5, ERROR);
    EXPECT_NEAR(v4[3], 0.64, ERROR);

}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
