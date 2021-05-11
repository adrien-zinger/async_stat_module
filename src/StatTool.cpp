#include "StatTool.hpp"
#include <algorithm>
#include <math.h>
#include <iostream>

#define TRIM 5e6

std::mutex mtx_density;
std::mutex mtx_position;

StatTool::~StatTool() {
    time_pos.val.clear();
    time_pos.time_us.clear();
    time_density.val.clear();
    time_density.time_us.clear();
}

void StatTool::MesureDensityReady(int density, int time_us) {
    mtx_density.lock();
    impl.Push(TRIM, time_us, density, time_density);
    mtx_density.unlock();
}

void StatTool::MesurePositionReady(int position_mm, int time_us) {
    mtx_position.lock();
    impl.Push(TRIM, time_us, position_mm, time_pos);
    mtx_position.unlock();
}

void dumpError(std::string msg, int min_pos_mm, int max_pos_mm,
        int min_time_val, int max_time_val) {
    std::cerr << msg.c_str() << "\n";
    std::cerr << "  " << min_pos_mm << ", "
        << max_pos_mm << ", "
        << min_time_val << ", "
        << min_time_val << "\n";
}

void StatTool::Elaboration(int min_pos_mm, int max_pos_mm,
        int *mean_density, int *min_density, int *median) {

    std::unique_lock<std::mutex> pos_lock(mtx_position);
    // Get time indexes from asked positions
    int min_index = -1, max_index = -1;
    bool success = impl.FindIndex(time_pos.val, min_pos_mm, false, min_index)
        && impl.FindIndex(time_pos.val, max_pos_mm, true, max_index);
    if (!success)
        return dumpError("Position loss",
            min_pos_mm, max_pos_mm, min_index, max_index);

    // I suppose that's included in the 5 previous seconds
    const int time_min = time_pos.time_us[min_index];
    const int time_max = time_pos.time_us[max_index];
    pos_lock.unlock();

    std::unique_lock<std::mutex> den_lock(mtx_density);
    // Get densities index from time_min and time_max
    success = impl.FindIndex(time_density.time_us, time_min, false, min_index)
        && impl.FindIndex(time_pos.time_us, time_max, true, max_index);
    if (!success)
        return dumpError("Density loss",
            min_pos_mm, max_pos_mm, min_index, max_index);

    // Get subvector
    const auto begin = time_density.val.begin() + min_index;
    const auto end = time_density.val.begin() + max_index;
    const int size = max_index - min_index;

    // Compute mean
    *mean_density = impl.Sum(begin, end, size) / size;
    // Compute min
    *min_density = *std::min_element(begin, end);
    // Compute median (Need a copy or we may loose information)
    std::vector<int> sorted(begin, end);
    std::sort(sorted.begin(), sorted.end());
    *median = sorted.size() % 2 != 0 ?
        std::floor(sorted[sorted.size() / 2])
        : (sorted[(sorted.size() - 1) / 2] + sorted[sorted.size() / 2]) / 2;

    den_lock.unlock();
}
