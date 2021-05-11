#include "StatToolImpl.hpp"
#include <cmath>
#include <pthread.h>
#include <memory>
#include <iostream>

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

struct thread_data {
    int sum, from, to;
    std::shared_ptr<std::vector<int>> vec;
};

void *sum_array(void* arg) {
    struct thread_data *data;
    data = (struct thread_data *) arg;
    for (int i = data->from; i <= data->to; ++i)
        data->sum += data->vec->at(i);
    return nullptr;
}

bool StatToolImpl::Sum(const std::vector<int> &vec, int &sum) {
    pthread_t threads[MAX_THREAD];
    struct thread_data data[MAX_THREAD];
    auto vec_ptr = std::make_shared<std::vector<int>>(vec);
    const auto cutsize = std::floor(vec.size() / MAX_THREAD);
    sum = 0;
    for (int i = 0; i < MAX_THREAD; ++i) {
        data[i].from = i * cutsize;
        data[i].to = i == MAX_THREAD - 1 ? vec.size() - 1 : ((i + 1) * cutsize) - 1;
        data[i].vec = vec_ptr;
        data[i].sum = 0;
        pthread_create(&threads[i], nullptr, sum_array, (void*)&data[i]);
    }
    for (int i = 0; i < MAX_THREAD; ++i) {
        pthread_join(threads[i], nullptr);
        sum += data[i].sum;
    }
    return true;
}

bool StatToolImpl::Push(const int time_trim, const int time_us, const int density, StatVector &vec, int &total_density) {
    total_density += density; // Push the new density
    const auto trim_ref = time_us - time_trim;
    int trim_index;
    if (FindIndex(vec.time_us, trim_ref, true, trim_index)) {
        const auto sliced = std::vector<int>(vec.val.begin(), vec.val.begin() + trim_index);
        int sum = 0;
        vec.val.erase(vec.val.begin() + trim_index);
        vec.time_us.erase(vec.time_us.begin() + trim_index);
        Sum(sliced, sum);
        total_density -= sum; // Cut from the total density what has been sliced
    }
    return true;
}
