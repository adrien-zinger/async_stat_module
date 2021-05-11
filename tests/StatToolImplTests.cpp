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
    EXPECT_EQ(78, tool.Sum(vec.begin(), vec.end(), vec.size()));
    EXPECT_EQ(26, tool.Sum(vec.begin() + 4, vec.begin() + 8, 4));
    EXPECT_EQ(2, tool.Sum(vec.begin() + 1, vec.begin() + 2, 1));
    EXPECT_EQ(5, tool.Sum(vec.begin() + 1, vec.begin() + 3, 2));
    EXPECT_EQ(12, tool.Sum(vec.end() - 1, vec.end(), 1));
    for (int i = 13; i < 101; ++i) vec.push_back(i);
    EXPECT_EQ(5050, tool.Sum(vec.begin(), vec.end(), vec.size()));
}
//*/

TEST(StatToolImplTest, testPush) {
    StatToolImpl tool;
    StatVector stats;
    tool.Push(5e6, 1.3e6, 1, stats);
    EXPECT_EQ(1, stats.val.size());
    tool.Push(5e6, 2.3e6, 2, stats);
    EXPECT_EQ(2, stats.val.size());
    tool.Push(5e6, 3.3e6, 3, stats);
    EXPECT_EQ(3, stats.val.size());
    tool.Push(5e6, 4.3e6, 4, stats);
    EXPECT_EQ(4, stats.val.size());
    tool.Push(5e6, 5.3e6, 5, stats);
    EXPECT_EQ(5, stats.val.size());
    tool.Push(5e6, 6.3e6, 6, stats);
    auto sum = tool.Sum(stats.val.begin(), stats.val.end(), stats.val.size());
    EXPECT_EQ(20, sum);
    EXPECT_EQ(5, stats.val.size());
    EXPECT_EQ(6, stats.val.back());
    EXPECT_EQ(2, stats.val.front());
}
//*/
