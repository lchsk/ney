#include "gtest/gtest.h"
#include "../../../include/ney/ney.hpp"

#include <unistd.h>

#define ERROR 0.000001

/*
    Tests of basic operations.
*/

TEST(Apply, ApplyInt)
{
    // Set up everything

    ney::config.target = ney::GPU;

    ney::status s;

    ney::vector<int> v1 = ney::new_vector().size(5);
    ney::vector<int> v2 = ney::new_vector().size(5);

    ney::vector<int> oi = ney::new_vector().size(5);

    v1 << 3 << 6 << 2 << 7 << 2;
    v2 << 2 << 6 << 3 << 7 << 2;

    // check for validation errors

    // missing vector1()

    s = ney::apply<int>(ney::function::sine);

    EXPECT_FALSE(s.success());
    EXPECT_NE(s.error(), "");

    // missing vector2() or value()

    s = ney::apply<int>(ney::operation::add).vector1(v1);

    EXPECT_FALSE(s.success());
    EXPECT_NE(s.error(), "");

    // redirect output to another vector

    s = ney::apply<int>(ney::function::cosine).vector1(v2).output(oi);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    for (int i = 0; i < 5 ; i ++)
    {
        EXPECT_GE(oi[i], -1);
        EXPECT_LE(oi[i], 1);
    }

    // check that original values remained the same

    EXPECT_EQ(v2[0], 2);
    EXPECT_EQ(v2[1], 6);
    EXPECT_EQ(v2[2], 3);
    EXPECT_EQ(v2[3], 7);
    EXPECT_EQ(v2[4], 2);

    // add two vectors together

    v1.reset();
    v1 << 5 << 3 << 5 << 1 << 0;

    v2.reset();
    v2 << 2 << 5 << 1  << 6 << 2;

    s = ney::apply<int>(ney::operation::add).vector1(v1).vector2(v2);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    // results are in v1

    EXPECT_EQ(v1[0], 7);
    EXPECT_EQ(v1[1], 8);
    EXPECT_EQ(v1[2], 6);
    EXPECT_EQ(v1[3], 7);
    EXPECT_EQ(v1[4], 2);

    // adding two vectors with output in third

    v1.reset();
    v1 << 5 << 3 << 5 << 1 << 0;

    v2.reset();
    v2 << 2 << 5 << 1  << 6 << 2;

    s = ney::apply<int>(ney::operation::add).vector1(v1).vector2(v2).output(oi);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    // results are in oi

    EXPECT_EQ(v1[0], 5);
    EXPECT_EQ(v1[1], 3);
    EXPECT_EQ(v1[2], 5);
    EXPECT_EQ(v1[3], 1);
    EXPECT_EQ(v1[4], 0);

    EXPECT_EQ(v2[0], 2);
    EXPECT_EQ(v2[1], 5);
    EXPECT_EQ(v2[2], 1);
    EXPECT_EQ(v2[3], 6);
    EXPECT_EQ(v2[4], 2);

    for (int i = 0; i < 5; i++)
        EXPECT_EQ(oi[i], v1[i] + v2[i]);

    // multiply

    s = ney::apply<int>(ney::operation::mul).vector1(v1).vector2(v2).output(oi);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    for (int i = 0; i < 5; i++)
        EXPECT_EQ(oi[i], v1[i] * v2[i]);

    // vector by a scalar

    v1.reset();

    v1 << 5 << 5 << 2  << 1 << 2;

    s = ney::apply<int>(ney::operation::add).vector1(v1).value(10).output(oi);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 5; i++)
        EXPECT_EQ(oi[i], v1[i] + 10);

    s = ney::apply<int>(ney::operation::mul).vector1(v1).value(10).output(oi);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 5; i++)
        EXPECT_EQ(oi[i], v1[i] * 10);

    // vector, vector, scalar

    v1.reset();
    v2.reset();

    v1 << 5 << 5 << 2 << 1 << 2;
    v2 << 0 << 1 << 2 << 3 << 4;

    s = ney::apply<int>(ney::operation::add).vector1(v1).vector2(v2).value(10).output(oi);

    EXPECT_TRUE(s.success());

    EXPECT_EQ(oi[0], 15);
    EXPECT_EQ(oi[1], 16);
    EXPECT_EQ(oi[2], 14);
    EXPECT_EQ(oi[3], 14);
    EXPECT_EQ(oi[4], 16);

    s = ney::apply<int>(ney::operation::mul).vector1(v1).vector2(v2).value(10).output(oi);

    EXPECT_TRUE(s.success());

    EXPECT_EQ(oi[0], 10);
    EXPECT_EQ(oi[1], 15);
    EXPECT_EQ(oi[2], 14);
    EXPECT_EQ(oi[3], 13);
    EXPECT_EQ(oi[4], 18);
}

TEST(Apply, ApplyOnText)
{
    ney::config.target = ney::GPU;
    ney::status s;

    ney::vector<char> text = ney::new_vector().size(6);

    text << 'a' << 'B' << 'z' << 'X' << 'y' << 'F';

    s = ney::apply<char>(ney::function::lower).vector1(text);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_EQ(text[0], 'a');
    EXPECT_EQ(text[1], 'b');
    EXPECT_EQ(text[2], 'z');
    EXPECT_EQ(text[3], 'x');
    EXPECT_EQ(text[4], 'y');
    EXPECT_EQ(text[5], 'f');

    text.reset();

    text << 'a' << 'B' << 'z' << 'X' << 'y' << 'F';

    s = ney::apply<char>(ney::function::upper).vector1(text);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_EQ(text[0], 'A');
    EXPECT_EQ(text[1], 'B');
    EXPECT_EQ(text[2], 'Z');
    EXPECT_EQ(text[3], 'X');
    EXPECT_EQ(text[4], 'Y');
    EXPECT_EQ(text[5], 'F');
}

TEST(Apply, ApplyDouble)
{
    // Set up everything
    ney::config.target = ney::GPU;

    ney::status s;

    ney::vector<double> v1 = ney::new_vector().size(5);
    ney::vector<double> v2 = ney::new_vector().size(5);

    ney::vector<double> oi = ney::new_vector().size(5);

    v1 << 3.1 << 6.4 << 2.2 << 7.6 << 2.3;
    v2 << 2.12 << 6.6 << -3.1 << -7.5 << 2.1;

    // check for validation errors

    // missing vector1()

    s = ney::apply<double>(ney::function::sine);

    EXPECT_FALSE(s.success());
    EXPECT_NE(s.error(), "");

    // missing vector2() or value()

    s = ney::apply<double>(ney::operation::add).vector1(v1);

    EXPECT_FALSE(s.success());
    EXPECT_NE(s.error(), "");

    // apply a function to the whole vector (int)

    s = ney::apply<double>(ney::function::sine).vector1(v2);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    for (int i = 0; i < 5 ; i ++)
    {
        EXPECT_GE(v2[i], -1);
        EXPECT_LE(v2[i], 1);
    }

    // redirect output to another vector

    v2.reset();
    v2 << 2.12 << 6.6 << -3.1 << -7.5 << 2.1;

    s = ney::apply<double>(ney::function::cosine).vector1(v2).output(oi);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    for (int i = 0; i < 5 ; i ++)
    {
        EXPECT_GE(oi[i], -1);
        EXPECT_LE(oi[i], 1);
    }

    // check that original values remained the same

    EXPECT_NEAR(v2[0], 2.12, ERROR);
    EXPECT_NEAR(v2[1], 6.6, ERROR);
    EXPECT_NEAR(v2[2], -3.1, ERROR);
    EXPECT_NEAR(v2[3], -7.5, ERROR);
    EXPECT_NEAR(v2[4], 2.1, ERROR);

    // add two vectors together

    v1.reset();
    v1 << 5.5 << 3.2 << 5.5 << 1.2 << 0.5;

    v2.reset();
    v2 << 2.15 << 5.4 << 1.2 << 6.4 << 2.1;

    s = ney::apply<double>(ney::operation::add).vector1(v1).vector2(v2);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    // results are in v1

    EXPECT_NEAR(v1[0], 7.65, ERROR);
    EXPECT_NEAR(v1[1], 8.6, ERROR);
    EXPECT_NEAR(v1[2], 6.7, ERROR);
    EXPECT_NEAR(v1[3], 7.6, ERROR);
    EXPECT_NEAR(v1[4], 2.6, ERROR);

    // adding two vectors with output in third

    v1.reset();
    v1 << 5.0 << 3.3 << 5.1 << 1.3 << 0.3;

    v2.reset();
    v2 << 2.1 << 5.2 << 1.1  << 6.2 << 2.5;

    s = ney::apply<double>(ney::operation::add).vector1(v1).vector2(v2).output(oi);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    // results are in oi

    EXPECT_NEAR(v1[0], 5.0, ERROR);
    EXPECT_NEAR(v1[1], 3.3, ERROR);
    EXPECT_NEAR(v1[2], 5.1, ERROR);
    EXPECT_NEAR(v1[3], 1.3, ERROR);
    EXPECT_NEAR(v1[4], 0.3, ERROR);

    EXPECT_NEAR(v2[0], 2.1, ERROR);
    EXPECT_NEAR(v2[1], 5.2, ERROR);
    EXPECT_NEAR(v2[2], 1.1, ERROR);
    EXPECT_NEAR(v2[3], 6.2, ERROR);
    EXPECT_NEAR(v2[4], 2.5, ERROR);

    for (int i = 0; i < 5; i++)
        EXPECT_NEAR(oi[i], v1[i] + v2[i], ERROR);

    // multiply

    s = ney::apply<double>(ney::operation::mul).vector1(v1).vector2(v2).output(oi);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    for (int i = 0; i < 5; i++)
        EXPECT_NEAR(oi[i], v1[i] * v2[i], ERROR);

    // vector by a scalar

    v1.reset();

    v1 << 5.2 << 5.1 << 2.3 << 1.5 << 2.2;

    s = ney::apply<double>(ney::operation::add).vector1(v1).value(0.5).output(oi);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 5; i++)
        EXPECT_NEAR(oi[i], v1[i] + 0.5, ERROR);

    s = ney::apply<double>(ney::operation::mul).vector1(v1).value(2.5).output(oi);

    EXPECT_TRUE(s.success());

    for (int i = 0; i < 5; i++)
        EXPECT_NEAR(oi[i], v1[i] * 2.5, ERROR);

    // vector, vector, scalar

    v1.reset();
    v2.reset();

    v1 << 5.3 << 5.5 << 2.1  << 1.5 << 2.2;
    v2 << 0.8 << 1.4 << 2.2 << 3.4 << 4.7;

    s = ney::apply<double>(ney::operation::add).vector1(v1).vector2(v2).value(2.5).output(oi);

    EXPECT_TRUE(s.success());

    EXPECT_NEAR(oi[0], 8.6, ERROR);
    EXPECT_NEAR(oi[1], 9.4, ERROR);
    EXPECT_NEAR(oi[2], 6.8, ERROR);
    EXPECT_NEAR(oi[3], 7.4, ERROR);
    EXPECT_NEAR(oi[4], 9.4, ERROR);
    
    s = ney::apply<double>(ney::operation::mul).vector1(v1).vector2(v2).value(0.5).output(oi);

    EXPECT_TRUE(s.success());

    EXPECT_NEAR(oi[0], 4.74, ERROR);
    EXPECT_NEAR(oi[1], 8.2, ERROR);
    EXPECT_NEAR(oi[2], 5.12, ERROR);
    EXPECT_NEAR(oi[3], 5.6, ERROR);
    EXPECT_NEAR(oi[4], 10.84, ERROR);

    // using d_value()

    ney::vector<int> v_int = ney::new_vector().size(5);
    v_int << 3 << 5 << 1 << 2 << 7;

    s = ney::apply<int>(ney::operation::mul).vector1(v_int).d_value(1.5);

    EXPECT_TRUE(s.success());

    EXPECT_GE(v_int[0], 3);
    EXPECT_GE(v_int[1], 5);
    EXPECT_GE(v_int[2], 1);
    EXPECT_GE(v_int[3], 2);
    EXPECT_GE(v_int[4], 7);

    v_int.reset();
    v_int << 3 << 5 << 1 << 2 << 7;

    s = ney::apply<int>(ney::operation::add).vector1(v_int).d_value(1.3);

    EXPECT_TRUE(s.success());

    EXPECT_EQ(v_int[0], 4);
    EXPECT_EQ(v_int[1], 6);
    EXPECT_EQ(v_int[2], 2);
    EXPECT_EQ(v_int[3], 3);
    EXPECT_EQ(v_int[4], 8);
}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
