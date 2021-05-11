#include "StatTool.hpp"
#include <mutex>
#include <algorithm>

#define TRIM 5e6

std::mutex mtx_density;
std::mutex mtx_position;

void StatTool::MesureDensityReady(int density, int time_us) {
    std::lock_guard<std::mutex> lock(mtx_density);
    impl.Push(TRIM, time_us, density, time_density, total_density);
}

void StatTool::MesurePositionReady(int position_mm, int time_us) {
    std::lock_guard<std::mutex> lock(mtx_position);
    int i = -1;
    impl.Push(TRIM, time_us, position_mm, time_pos, i);
}

void StatTool::Elaboration(int min_pos_mm, int max_pos_mm,
        int *mean_density, int *min_density, int *median) {
    std::unique_lock<std::mutex> pos_lock(mtx_position);
    int min_index, max_index;
    bool success = impl.FindIndex(time_pos.val, min_pos_mm, false, min_index)
        && impl.FindIndex(time_pos.val, max_pos_mm, true, max_index);
    if (!success) return; // should throw an error or signal that's return

    // I suppose that's included in the 5 previous seconds
    const int time_min = time_pos.time_us[min_index];
    const int time_max = time_pos.time_us[max_index];
    pos_lock.unlock();

    std::unique_lock<std::mutex> den_lock(mtx_density);
    success = impl.FindIndex(time_density.time_us, time_min, false, min_index)
        && impl.FindIndex(time_pos.time_us, time_max, true, max_index);
    if (!success) return; // should throw an error or signal that's return
    // Get subvector
    std::vector<int> subvec(time_density.val.begin() + min_index,
        time_density.val.begin() + max_index);
    den_lock.unlock();

    // Compute mean
    *mean_density = impl.Sum(subvec) / (max_index - min_index);
    // Compute min
    *min_density = *std::min_element(subvec.begin(), subvec.end());
    // Compute median
    // todo
}
