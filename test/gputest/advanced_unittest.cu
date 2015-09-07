#include "gtest/gtest.h"
#include "../../../include/ney/ney.hpp"

#include <unistd.h>

#define ERROR 0.000001

/*
    Tests of basic operations.
*/

TEST(AdvancedOperations, Reduce)
{
    // Set up everything;
    ney::config.target = ney::GPU;

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

    // EXPECT_EQ(result_i, 5040);

    // Addition of doubles

    s = ney::reduce<double>(v2).output(result_d).use(ney::operation::add);

    EXPECT_NEAR(result_d, 2.8, ERROR);

    // Multiplication of doubles

    s = ney::reduce<double>(v2).init(1).output(result_d).use(ney::operation::mul);

    // EXPECT_NEAR(result_d, 0.0005040, ERROR);

    // use vector slice

    s = ney::reduce<int>(v1.stride(2)).output(result_i).use(ney::operation::add);

    EXPECT_EQ(result_i, 16);
}

// TEST(AdvancedOperations, Compare)
// {
//     // Set up everything
//
//     ney::status s;
//
//     ney::vector<int> v1 = ney::new_vector().size(5);
//     ney::vector<int> v2 = ney::new_vector().size(5);
//     ney::vector<double> v3 = ney::new_vector().size(5);
//     ney::vector<double> v4 = ney::new_vector().size(5);
//
//     ney::vector<bool> o = ney::new_vector().size(5);
//
//     v1 << 3 << 6 << 2 << 7 << 2;
//     v2 << 2 << 6 << 3 << 7 << 2;
//
//     v3 << 0.3 << 0.6 << 0.2 << 0.64 << 0.2;
//     v4 << 0.1 << 0.2 << 0.2 << 0.64 << 0.1;
//
//     // Check if validation works
//
//     s = ney::compare<int>().vector1(v1).vector2(v2);
//
//     EXPECT_FALSE(s.success());
//
//     // Integer comparison
//
//     s = ney::compare<int>().vector1(v1).vector2(v2).output(o);
//
//     EXPECT_TRUE(s.success());
//
//     EXPECT_FALSE(o[0]);
//     EXPECT_TRUE(o[1]);
//     EXPECT_FALSE(o[2]);
//     EXPECT_TRUE(o[3]);
//     EXPECT_TRUE(o[4]);
//
//     // Floating point numbers comparison
//
//     s = ney::compare<double>().vector1(v3).vector2(v4).output(o);
//
//     EXPECT_TRUE(s.success());
//
//     EXPECT_FALSE(o[0]);
//     EXPECT_FALSE(o[1]);
//     EXPECT_TRUE(o[2]);
//     EXPECT_TRUE(o[3]);
//     EXPECT_FALSE(o[4]);
//
//     // Floating point numbers comparison (with precision)
//
//     s = ney::compare<double>().vector1(v3).vector2(v4).output(o).precision(0.15);
//
//     EXPECT_TRUE(s.success());
//
//     EXPECT_FALSE(o[0]);
//     EXPECT_FALSE(o[1]);
//     EXPECT_TRUE(o[2]);
//     EXPECT_TRUE(o[3]);
//     EXPECT_TRUE(o[4]);
// }

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
