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

    s = ney::count<int>(5).in(v1).output(ci);

    EXPECT_FALSE(s.offloaded());

    s = ney::count<int>(5).in(v1).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 2);

    s = ney::count<int>(5).in(v1.from(1)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 1);

    s = ney::count<int>(5).in(v1.from(1).to(1)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 0);

    v1.reset();
    s = ney::count<int>(5).in(v1.stride(2)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 1);

    v1.reset();
    s = ney::count<int>(5).in(v1.stride(3)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 2);

    v1.reset();
    s = ney::count<int>(0).in(v1.stride(6)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 1);

    v1.reset();
    s = ney::count<int>(9).in(v1.from(2).stride(3)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 2);

    v1.reset();
    s = ney::count<int>(9).in(v1.from(1).stride(4)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 1);

    v1.reset();
    s = ney::count<int>(0).in(v1.from(1).stride(2)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 0);

    v1.reset();
    s = ney::count<int>(0).in(v1.from(2).stride(2)).output(ci).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(ci, 1);
}

TEST(Offloading, CountDouble)
{
    // Check defaults

    ney::status s;
    ney::vector<double> v1 = ney::new_vector().size(7);
    v1 << 5.2 << 1.1 << 9.9 << 5.2 << 2.1 << 9.0 << 0.5;

    int c = 0;

    s = ney::count<double>(5.2).in(v1).output(c).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(c, 2);
}

TEST(Offloading, Reduce)
{
    // Check defaults

    ney::status s;
    ney::vector<int> v1 = ney::new_vector().size(7);
    v1 << 2 << 3 << 7 << 0 << 2 << 1 << 2;

    int r = 0;

    s = ney::reduce<int>(v1).use(ney::operation::add).output(r).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(r, 17);

    s = ney::reduce<int>(v1.from(1).stride(2)).use(ney::operation::add).output(r).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(r, 4);

    s = ney::reduce<int>(v1.reset().to(5).stride(2)).use(ney::operation::add).init(5).output(r).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(r, 16);

    s = ney::reduce<int>(v1.reset().to(3)).use(ney::operation::mul).init(1).output(r).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(r, 42);

    v1.reset();
    v1 << 1 << 2 << 3 << 4 << 5 << 6 << 7;

    s = ney::reduce<int>(v1.reset().stride(3)).use(ney::operation::mul).init(1).output(r).force_offloading();

    EXPECT_TRUE(s.offloaded());
    EXPECT_TRUE(s.success());
    EXPECT_EQ(s.error(), "");
    EXPECT_EQ(r, 28);
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
