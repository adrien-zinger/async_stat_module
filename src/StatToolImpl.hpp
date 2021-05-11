#pragma once
#include "StatVector.hpp"

/**
 * Max number of threads used by the sum function
 **/
#define MAX_THREAD 4

/**
 * Implementation of StatTool sub tools
 **/

class StatToolImpl {
    public:
    /**
     * Get an index of a ref even if it's not exactly this.
     * Return the nearest left or right
     * vec is ordered
     **/
    bool FindIndex(const std::vector<int> &vec, const int ref, const bool left, int &index);
    /**
     * Sum the integers in current vector
     **/
    int Sum(const std::vector<int>::iterator &begin, const std::vector<int>::iterator &end, int size);
    /**
     * Push in the current vector "vec" the pair of values time_us and value and trim vec with the
     * time_trim value
     **/
    void Push(const int time_trim, const int time_us, const int density, StatVector &vec);
};
