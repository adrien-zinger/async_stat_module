#include "StatToolImpl.hpp"
#include <cmath>

//#include <iostream>

bool StatToolImpl::FindIndex(const std::vector<int> &vec, const int time_ref, const bool left, int &index) {
    int l = 0;
    int r = vec.size() - 1;
    if (vec[l] > time_ref || vec[r] < time_ref || vec[l] >= vec[r])
        return false;
    if (vec[l] == time_ref) {
        index = l;
        return true;
    }
    if (vec[r] == time_ref) {
        index = r;
        return true;
    }
    while (r - l > 1) {
        const int m = std::floor((l+r) / 2);
        if (vec[m] == time_ref) {
            index = m;
            return true;
        }
        if (vec[l] <= time_ref && time_ref < vec[m])
            r = m;
        else l = m;
    }
    index = left ? l : r;
    return true;
}

bool StatToolImpl::Sum(const std::vector<int> &vec, int &sum) {
    return false;
}

bool StatToolImpl::Push(const int time_trim, const int time_us, const int val, StatVector &vec) {
    return false;
}
