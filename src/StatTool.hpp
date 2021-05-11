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

    // Tool methods declaration
    void MesureDensityReady(int density, int time_us);
    void MesurePositionReady(int position_mm, int time_us);
    void Elaboration(int min_pos_mm, int max_pos_mm, int *mean_density, int *min_density, int *median);

    private:
    StatVector time_pos; //< Pair of vector with time/position relation
    StatVector time_density; //< Pair of vector with time/density relation
    StatToolImpl impl; //< Tool helper implementation (can be reused)
    // multithread access protection
    std::mutex mtx_density;
    std::mutex mtx_position;
};