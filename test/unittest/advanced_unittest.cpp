#include "gtest/gtest.h"
#include "../../../include/ney/ney.hpp"

#include <unistd.h>

#define ERROR 0.000001

/*
    Tests of basic operations.
*/

TEST(AdvanedOperations, Reduce)
{
    // Set up everything

    ney::status s;
    ney::vector<int> v1 = ney::new_vector().size(7);
    ney::vector<double> v2 = ney::new_vector().size(7);

    v1 << 1 << 2 << 3 << 4 << 5 << 6 << 7;
    v2 << 0.1 << 0.2 << 0.3 << 0.4 << 0.5 << 0.6 << 0.7;

    int result_i;
    double result_d;

    // Check if validation works

    s = ney::reduce<int>(v1).use(ney::operation::add);

    EXPECT_FALSE(s.success());

    s = ney::reduce<int>(v1);

    EXPECT_FALSE(s.success());

    s = ney::reduce<int>(v1).output(result_i);

    EXPECT_FALSE(s.success());

    // Addition

    s = ney::reduce<int>(v1).output(result_i).use(ney::operation::add);

    EXPECT_EQ(result_i, 28);

    // Multiplication needs a call to init() function to set a initialisation value

    s = ney::reduce<int>(v1).init(1).output(result_i).use(ney::operation::mul);

    EXPECT_EQ(result_i, 5040);

    // Addition of doubles

    s = ney::reduce<double>(v2).output(result_d).use(ney::operation::add);

    EXPECT_NEAR(result_d, 2.8, ERROR);

    // Multiplication of doubles

    s = ney::reduce<double>(v2).init(1).output(result_d).use(ney::operation::mul);

    EXPECT_NEAR(result_d, 0.0005040, ERROR);

    // use vector slice

    s = ney::reduce<int>(v1.stride(2)).output(result_i).use(ney::operation::add);

    EXPECT_EQ(result_i, 16);
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
