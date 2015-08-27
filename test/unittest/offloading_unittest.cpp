#include "gtest/gtest.h"
#include "../../../include/ney/ney.hpp"

#include <unistd.h>

#define ERROR 0.000001

TEST(Offloading, Worksharing)
{
    // Check defaults

    ney::status s;
    ney::vector<int> v1 = ney::new_vector().size(7);
    v1 << 5 << 1 << 9 << 5 << 2 << 9 << 0;

    int ci = 0;

    std::cout << "1\n";
    s = ney::count<int>(5).in(v1).output(ci);

    EXPECT_FALSE(s.offloaded());

    std::cout << "2\n";
    s = ney::count<int>(5).in(v1).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 2);

    std::cout << "3\n";
    s = ney::count<int>(5).in(v1.from(1)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 1);

    std::cout << "4\n";
    s = ney::count<int>(5).in(v1.from(1).to(1)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 0);

    std::cout << "5\n";
    v1.reset();
    s = ney::count<int>(5).in(v1.stride(2)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 1);

    std::cout << "6\n";
    v1.reset();
    s = ney::count<int>(5).in(v1.stride(3)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 2);

    std::cout << "7\n";
    v1.reset();
    s = ney::count<int>(0).in(v1.stride(6)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 1);

    std::cout << "8\n";
    v1.reset();
    s = ney::count<int>(9).in(v1.from(2).stride(3)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 2);

    std::cout << "9\n";
    v1.reset();
    s = ney::count<int>(9).in(v1.from(1).stride(4)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 1);

    std::cout << "10\n";
    v1.reset();
    s = ney::count<int>(0).in(v1.from(1).stride(2)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 0);

    std::cout << "11\n";
    v1.reset();
    s = ney::count<int>(0).in(v1.from(2).stride(2)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 1);
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
