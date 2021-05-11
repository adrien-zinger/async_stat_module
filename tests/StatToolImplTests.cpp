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

TEST(StatToolImplTest, sum) {
    StatToolImpl tool;
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10,11,12};
    int sum;
    EXPECT_TRUE(tool.Sum(vec, sum));
    EXPECT_EQ(78, sum);
}

TEST(StatToolImplTest, testPush) {
    StatToolImpl tool;
    StatVector stats;
    int total = 0;
    tool.Push(5e6, 1.3e6, 1, stats, total);
    EXPECT_EQ(1, stats.val.size());
    tool.Push(5e6, 2.3e6, 2, stats, total);
    EXPECT_EQ(2, stats.val.size());
    tool.Push(5e6, 3.3e6, 3, stats, total);
    EXPECT_EQ(3, stats.val.size());
    tool.Push(5e6, 4.3e6, 4, stats, total);
    EXPECT_EQ(4, stats.val.size());
    tool.Push(5e6, 5.3e6, 5, stats, total);
    EXPECT_EQ(5, stats.val.size());
    tool.Push(5e6, 6.3e6, 6, stats, total);
    EXPECT_EQ(15, total);
    EXPECT_EQ(5, stats.val.size());
    EXPECT_EQ(6, stats.val.back());
    EXPECT_EQ(2, stats.val.front());
}
