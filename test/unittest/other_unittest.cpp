#include "gtest/gtest.h"
#include "../../../include/ney/ney.hpp"

#include <unistd.h>

#define ERROR 0.000001

#define ONE_SECOND 1000000.0
#define ONE_MS 1000.0

TEST(Other, Config)
{
    // Check defaults

    EXPECT_EQ(ney::config.target, ney::Intel);
    EXPECT_EQ(ney::config.threads, ney::config.max_threads());
    EXPECT_TRUE(ney::config.use_offloading);
    EXPECT_GT(ney::config.max_threads(), 0);
    EXPECT_NE(ney::config.compiler(), "");
}

TEST(Other, TimerAndClock)
{
    ney::clock::get().start();
    ney::clock* c1 = &ney::clock::get();
    ney::timer t1, t2;

    t1.start();
    usleep(10 * ONE_MS);
    EXPECT_GT(t1.end().time(), 9 * ONE_MS / ONE_SECOND);

    t1.start();
    usleep(25 * ONE_MS);
    t1.end();
    EXPECT_GT(t1.time(), 24 * ONE_MS / ONE_SECOND);
    EXPECT_LT(t1.time(), 26 * ONE_MS / ONE_SECOND);

    // Confirm any two timer objects are different

    EXPECT_NE(&t1, &t2);

    // Clock is always the same

    ney::clock* c2 = &ney::clock::get();

    EXPECT_EQ(c1, c2);

    EXPECT_GT(ney::clock::get().end().time(), 34 * ONE_MS / ONE_SECOND);

    // clock can be started again

    ney::clock::get().start();
    usleep(5 * ONE_MS);
    EXPECT_GT(ney::clock::get().end().time(), 4 * ONE_MS / ONE_SECOND);

    // precision

    ney::clock::get().precision(5);
    EXPECT_EQ(ney::clock::get().precision(), 5);

    t1.precision(10);
    EXPECT_EQ(t1.precision(), 10);

}

TEST(Other, StatusTimer)
{
    // TODO: test in-function timers
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
