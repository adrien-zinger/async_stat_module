#include "../src/StatTool.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(StatToolTests, mandatory) {
    StatTool statTool;
    for (int i = 0; i < 10; ++i) {
        statTool.MesurePositionReady(i, 0.5e6 * i);
        statTool.MesureDensityReady(i, 0.5e6 * i);
    }
    EXPECT_TRUE(false);
    int mean;
    int min;
    int median;
    statTool.Elaboration(7, 10, &mean, &min, &median);
    std::cout << mean << " " << min << " " << median << "\n";
    EXPECT_TRUE(false);
};
