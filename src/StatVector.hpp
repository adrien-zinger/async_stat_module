#pragma once
#include <vector>

/**
 * Pair of symetrics vectors time / value
 **/
class StatVector {
    public:
    std::vector<int> val;
    std::vector<int> time_us;
};
