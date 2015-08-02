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

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
