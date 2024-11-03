#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include "vector.hpp"

template <typename T>
void merge(typename Vector<T>::Iterator left, typename Vector<T>::Iterator mid, typename Vector<T>::Iterator right) {
    Vector<T> temp;

    auto start1 = left;
    auto start2 = mid + 1;

    while (start1 <= mid && start2 <= right) {
        if (*start1 <= *start2) {
            temp.push_back(*start1);
            ++start1;
        } else {
            temp.push_back(*start2);
            ++start2;
        }
    }

    while (start1 <= mid) {
        temp.push_back(*start1);
        ++start1;
    }

    while (start2 <= right) {
        temp.push_back(*start2);
        ++start2;
    }

    for (auto it = temp.begin(); it != temp.end(); ++it) {
        *left = *it;
        ++left;
    }
}

template <typename T>
void merge_sort(typename Vector<T>::Iterator left, typename Vector<T>::Iterator right) {
    if (left < right) {
        auto mid = left + (right - left) / 2;

        merge_sort<T>(left, mid);
        merge_sort<T>(mid + 1, right);

        merge<T>(left, mid, right);
    }
}

#endif // MERGE_SORT_HPP