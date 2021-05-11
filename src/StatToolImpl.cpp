#include "StatToolImpl.hpp"
#include <cmath>
#include <pthread.h>
#include <memory>
#include <iostream>

bool StatToolImpl::FindIndex(const std::vector<int> &vec, const int ref, const bool left, int &index) {
    int l = 0;
    int r = vec.size() - 1;
    if (vec[l] > ref || vec[r] < ref || vec[l] >= vec[r])
        return false;
    if (vec[l] == ref) {
        index = l;
        return true;
    }
    if (vec[r] == ref) {
        index = r;
        return true;
    }
    while (r - l > 1) {
        const int m = std::floor((l+r) / 2);
        if (vec[m] == ref) {
            index = m;
            return true;
        }
        if (vec[l] <= ref && ref < vec[m])
            r = m;
        else l = m;
    }
    index = left ? l : r;
    return true;
}

struct thread_data {
    int sum, size;
    std::vector<int>::iterator from;
    std::vector<int>::iterator end;
};

void *sum_array(void* arg) {
    struct thread_data *data;
    data = (struct thread_data *) arg;
    data->sum = 0;
    int i = 0;
    auto it = data->from;
    for (; it != data->end && i < data->size; ++it, ++i)
        data->sum += *it;
    return nullptr;
}

int StatToolImpl::Sum(const std::vector<int>::iterator &begin, const std::vector<int>::iterator &end, int size) {
    pthread_t threads[MAX_THREAD];
    struct thread_data data[MAX_THREAD];
    const auto cutsize = std::floor(size / MAX_THREAD);
    int sum = 0;
    auto from = begin;
    for (int i = 0; i < MAX_THREAD; ++i) {
        data[i].from = from;
        data[i].size = cutsize;
        data[i].end = end;
        data[i].sum = 0;
        from += cutsize;
        pthread_create(&threads[i], nullptr, sum_array, (void*)&data[i]);
    }
    for (int i = 0; i < MAX_THREAD; ++i) {
        pthread_join(threads[i], nullptr);
        sum += data[i].sum;
    }
    return sum;
}

int StatToolImpl::Median(const std::vector<int> &vec) {
    return 0;
}

void StatToolImpl::Push(const int time_trim, const int time_us, const int density, StatVector &vec, int &total_density) {
    total_density += density; // Push the new density
    const auto trim_ref = time_us - time_trim;
    int trim_index;
    if (total_density != -1 && FindIndex(vec.time_us, trim_ref, true, trim_index)) {
        total_density -= Sum(vec.val.begin(), vec.val.begin() + trim_index, trim_index); // Cut from the total density what has been sliced
        vec.val.erase(vec.val.begin() + trim_index);
        vec.time_us.erase(vec.time_us.begin() + trim_index);
    }
}
