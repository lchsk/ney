#include "gtest/gtest.h"
#include "../../../include/ney/vector.hpp"

TEST(VectorTests, DefaultSettings)
{
    ney::vector<double> v = ney::new_vector();
    EXPECT_EQ(v.size(), 10);
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    returnValue =  RUN_ALL_TESTS();

    return returnValue;
}
