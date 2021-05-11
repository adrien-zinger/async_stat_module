#include "StatToolImpl.hpp"
#include <cmath>
#include <pthread.h>
#include <memory>

bool StatToolImpl::FindIndex(const std::vector<int> &vec, const int ref, const bool left, int &index) {
    int l = 0;
    int r = vec.size() - 1;
    if (ref <= 0 || vec.size() < 1 || vec[l] > ref || vec[r] < ref || vec[l] >= vec[r])
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
    for (; it != data->end && i < data->size; data->sum += *it, ++it, ++i);
    return nullptr;
}

int StatToolImpl::Sum(const std::vector<int>::iterator &begin,
        const std::vector<int>::iterator &end, int size) {
    int sum = 0;
    auto from = begin;
    if (size <= MAX_THREAD) { // easy return
        for (auto it = begin; it != end;  sum += *it++);
        return sum;
    }
    // Else dividing
    pthread_t threads[MAX_THREAD];
    struct thread_data data[MAX_THREAD];
    const auto cutsize = std::floor(size / MAX_THREAD);
    const int remaining = (size % MAX_THREAD) == 0 ? cutsize :  size % MAX_THREAD + 1;
    for (int i = 0; i < MAX_THREAD; ++i, from += cutsize) {
        data[i].from = from;
        data[i].size = (i == MAX_THREAD - 1) ? remaining : cutsize;
        data[i].end = end;
        data[i].sum = 0;
        pthread_create(&threads[i], nullptr, sum_array, (void*)&data[i]);
    }
    for (int i = 0; i < MAX_THREAD; sum += data[i].sum, ++i)
        pthread_join(threads[i], nullptr);
    return sum;
}

void StatToolImpl::Push(const int time_trim, const int time_us, const int value, StatVector &vec) {
    const auto trim_ref = time_us - time_trim;
    vec.val.push_back(value);
    vec.time_us.push_back(time_us);
    int trim_index;
    if (FindIndex(vec.time_us, trim_ref, true, trim_index)) {
        vec.val.erase(vec.val.begin() + trim_index);
        vec.time_us.erase(vec.time_us.begin() + trim_index);
    }
}
