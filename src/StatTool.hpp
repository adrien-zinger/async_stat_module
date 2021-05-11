#pragma once
#include "StatToolImpl.hpp"
#include <memory>
#include <mutex>

/**
 * Solution for a real time problem
 * 
 * We got two related informations with differents timestamps.
 * We want an access to the median, the min, and the mean in an interval as explained in the README
 **/

class StatTool {
    public:
    ~StatTool();
    void MesureDensityReady(int density, int time_us);
    void MesurePositionReady(int position_mm, int time_us);
    void Elaboration(int min_pos_mm, int max_pos_mm, int *mean_density, int *min_density, int *median);

    private:
    std::mutex mtx_density;
    std::mutex mtx_position;
    int total_density = 0;
    StatVector time_pos;
    StatVector time_density;
    StatToolImpl impl;
};