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
    v1[0] = 2.5;
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

    v2[0] = 500;
    v2[1] = 400;
    v2[2] = 300;

    // Invoke copy-constructor
    // Data from v2 should be in v3

    ney::vector<int> v3(v2);
    EXPECT_EQ(v3[0], 500);
    EXPECT_EQ(v3[1], 400);
    EXPECT_EQ(v3[2], 300);

    // Copy-constructor does not copy slice information, but instead
    // resets it to default values.
    
    EXPECT_EQ(v2.reset().length(), v3.length());

    v2.stride(2);
    v3[0] = 1000;

    // Invoke assignment operator
    // v2 and v3 should have the same data and the same information on slicing
    v2 = v3;
    EXPECT_EQ(v2.length(), v3.length());
    EXPECT_EQ(v2.size(), v3.size());
    EXPECT_EQ(v2[0], 1000);
    EXPECT_EQ(v3[0], 1000);
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
