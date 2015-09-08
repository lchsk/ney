#include "gtest/gtest.h"
// #include "../../../include/ney/vector.hpp"
#include "../../../include/ney/ney.hpp"

#define ERROR 0.000001

TEST(VectorTests, Basic)
{
    // 1 Check default vector size
    ney::vector<double> v1 = ney::new_vector();
    EXPECT_EQ(v1.size(), 10);

    // 2 Check that default values in a vector are zeroes
    for (int i = 0; i < 10; i++)
        // EXPECT_DOUBLE_EQ(v1[i], 0, ERROR);
        EXPECT_NEAR(v1[i], 0, ERROR);

    // 3 Check reading and assigning new single values
    v1.set(0, 2.5);
    EXPECT_NEAR(v1[0], 2.5, ERROR);

    // 4 Check if << operator is correctly overloaded
    v1 << 1 << 2 << 3 << 4;
    EXPECT_NEAR(v1[0], 1, ERROR);
    EXPECT_NEAR(v1[1], 2, ERROR);
    EXPECT_NEAR(v1[2], 3, ERROR);
    EXPECT_NEAR(v1[3], 4, ERROR);

    // 5 Check slicing

    EXPECT_EQ(v1.length(), 10);
    v1.stride(2);
    EXPECT_EQ(v1.length(), 5);
    v1.from(3);
    EXPECT_EQ(v1.length(), 4);
    v1.to(7);
    EXPECT_EQ(v1.length(), 2);

    // Make sure size stays the same despite slicing

    EXPECT_EQ(v1.size(), 10);

    // After resetting, length should be the same as size

    v1.reset();
    EXPECT_EQ(v1.length(), v1.size());

    // Test alternative way to define a slice

    EXPECT_EQ(v1.slice(3, 7, 2).length(), 2);
}

TEST(VectorTests, Advanced)
{
    // Define new larger vector

    ney::vector<int> v2 = ney::new_vector().size(13);
    EXPECT_EQ(v2.size(), 13);

    // Check if slicing works on a vector of weird size

    v2.slice(2, 10, 3);
    EXPECT_EQ(v2.length(), 3);

    v2.set(0, 500);
    v2.set(1, 400);
    v2.set(2, 300);

    // Invoke copy-constructor
    // Data from v2 should be in v3

    ney::vector<int> v3(v2.reset());

    EXPECT_EQ(v3[0], 500);
    EXPECT_EQ(v3[1], 400);
    EXPECT_EQ(v3[2], 300);

    // Copy-constructor does copy slice information

    EXPECT_EQ(v2.reset().length(), v3.length());

    v2.stride(2);
    v3.set(0, 1000);

    // Invoke assignment operator
    // v2 and v3 should have the same data and the same information on slicing
    v2 = v3;
    EXPECT_EQ(v2.length(), v3.length());
    EXPECT_EQ(v2.size(), v3.size());
    EXPECT_EQ(v2[0], 1000);
    EXPECT_EQ(v3[0], 1000);

    // Checks if concatenating two vectors works correctly

    ney::vector<int> v_add1 = ney::new_vector().size(5);
    ney::vector<int> v_add2 = ney::new_vector().size(6);

    ney::vector<int> v_out;

    v_add1 << 1 << 2 << 3 << 4 << 5;
    v_add2 << 6  << 7 << 8 << 9 << 10 << 11;

    v_out = v_add1 + v_add2;

    EXPECT_EQ(v_add1.length(), 5);
    EXPECT_EQ(v_add2.length(), 6);
    EXPECT_EQ(v_out.length(), 11);

    for (int i = 1; i <= 11; i++)
        EXPECT_EQ(v_out[i - 1], i);

    // two vectors added with slicing

    v_out = v_add1.stride(2) + v_add2.from(1).to(4);

    EXPECT_EQ(v_out[0], 1);
    EXPECT_EQ(v_out[1], 3);
    EXPECT_EQ(v_out[2], 5);
    EXPECT_EQ(v_out[3], 7);
    EXPECT_EQ(v_out[4], 8);
    EXPECT_EQ(v_out[5], 9);
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
