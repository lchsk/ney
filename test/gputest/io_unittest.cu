#include "gtest/gtest.h"
#include "../../../include/ney/ney.hpp"

#include <unistd.h>

#define ERROR 0.000001

/*
    Tests of sort-based operations
*/

TEST(IO, OpenText)
{
    // Set up everything
    ney::config.target = ney::GPU;

    ney::status s;

    ney::vector<char> o;

    // check if flags are set

    s = ney::open<char>("../unittest/examples/chars1.txt");

    EXPECT_FALSE(s.success());
    EXPECT_NE(s.error(), "");

    // open as text

    s = ney::open<char>("../unittest/examples/chars1.txt").output(o).as_text();

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_EQ(o.size(), 22);
    EXPECT_EQ(o.length(), 22);

    EXPECT_EQ(o[0], 'a');
    EXPECT_EQ(o[1], 'b');
    EXPECT_EQ(o[2], 'c');
    EXPECT_EQ(o[3], '\n');
    EXPECT_EQ(o[4], 'a');
    EXPECT_EQ(o[5], 'b');
    EXPECT_EQ(o[6], ' ');
    EXPECT_EQ(o[7], 'b');
    EXPECT_EQ(o[8], 'a');
    EXPECT_EQ(o[9], '\n');
    EXPECT_EQ(o[10], 'c');
    EXPECT_EQ(o[11], ' ');
    EXPECT_EQ(o[12], 'a');
    EXPECT_EQ(o[13], ' ');
    EXPECT_EQ(o[14], 'c');
    EXPECT_EQ(o[15], '\n');
    EXPECT_EQ(o[16], '\n');
    EXPECT_EQ(o[17], 'd');
    EXPECT_EQ(o[18], ' ');
    EXPECT_EQ(o[19], 'b');
    EXPECT_EQ(o[20], ' ');
    EXPECT_EQ(o[21], 'a');
}

TEST(IO, OpenNumbers)
{
    // Set up everything
    ney::config.target = ney::GPU;

    ney::status s;

    ney::vector<int> o;
    ney::vector<double> od;

    // open ints

    s = ney::open<int>("../unittest/examples/ints1.txt").output(o);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_EQ(o.size(), 10);
    EXPECT_EQ(o.length(), 10);

    EXPECT_EQ(o[0], 1);
    EXPECT_EQ(o[1], 2);
    EXPECT_EQ(o[2], 3);
    EXPECT_EQ(o[3], 4);
    EXPECT_EQ(o[4], 5);
    EXPECT_EQ(o[5], 10);
    EXPECT_EQ(o[6], 20);
    EXPECT_EQ(o[7], 30);
    EXPECT_EQ(o[8], 40);
    EXPECT_EQ(o[9], 50);

    // open doubles

    s = ney::open<double>("../unittest/examples/doubles1.txt").output(od);

    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");

    EXPECT_EQ(od.size(), 7);
    EXPECT_EQ(od.length(), 7);

    // EXPECT_NEAR(od[0], 4.2, ERROR);
    // EXPECT_NEAR(od[1], -0.9, ERROR);
    // EXPECT_NEAR(od[2], 23.4, ERROR);
    // EXPECT_NEAR(od[3], 44, ERROR);
    // EXPECT_NEAR(od[4], 22.4, ERROR);
    // EXPECT_NEAR(od[5], 1.2, ERROR);
    // EXPECT_NEAR(od[6], 0.894, ERROR);

    EXPECT_DOUBLE_EQ(od[0], 4.2);
    EXPECT_DOUBLE_EQ(od[1], -0.9);
    EXPECT_DOUBLE_EQ(od[2], 23.4);
    EXPECT_DOUBLE_EQ(od[3], 44);
    EXPECT_DOUBLE_EQ(od[4], 22.4);
    EXPECT_DOUBLE_EQ(od[5], 1.2);
    EXPECT_DOUBLE_EQ(od[6], 0.894);

}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
