#include "../src/StatToolImpl.hpp"
#include <gtest/gtest.h>

TEST(StatToolImplTest, FindIndexExact) {
    StatToolImpl tool;
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};
    int index;
    EXPECT_TRUE(tool.FindIndex(vec, 3, true, index));
    EXPECT_EQ(2, index);
    EXPECT_TRUE(tool.FindIndex(vec, 3, false, index));
    EXPECT_EQ(2, index);
    EXPECT_TRUE(tool.FindIndex(vec, 9, true, index));
    EXPECT_EQ(8, index);
    EXPECT_TRUE(tool.FindIndex(vec, 9, false, index));
    EXPECT_EQ(8, index);
}

TEST(StatToolImplTest, FindIndexExactExtremities) {
    StatToolImpl tool;
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};
    int index;
    EXPECT_TRUE(tool.FindIndex(vec, 1, false, index));
    EXPECT_EQ(0, index);
    EXPECT_TRUE(tool.FindIndex(vec, 10, false, index));
    EXPECT_EQ(9, index);
}

TEST(StatToolImplTest, FindInBetween) {
    StatToolImpl tool;
    std::vector<int> vec{1,3,5,6,8,9,11,15,17,18};
    int index;
    EXPECT_TRUE(tool.FindIndex(vec, 10, true, index));
    EXPECT_EQ(5, index);
    EXPECT_TRUE(tool.FindIndex(vec, 10, false, index));
    EXPECT_EQ(6, index);
}