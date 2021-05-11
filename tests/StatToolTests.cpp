#include "../src/StatTool.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(StatToolTests, mandatory) {
    StatTool statTool;
    for (int i = 0; i < 10; ++i) {
        statTool.MesurePositionReady(i, 0.5e6 * i);
        statTool.MesureDensityReady(i, 0.5e6 * i);
    }
    int mean = 0;
    int min = 0;
    int median = 0;
    statTool.Elaboration(6, 9, &mean, &min, &median);
    EXPECT_EQ(7, mean);
    EXPECT_EQ(6, min);
    EXPECT_EQ(7, median);
};
