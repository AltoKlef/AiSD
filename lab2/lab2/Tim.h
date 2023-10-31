#pragma once
#include "DinArr.h"
#include <algorithm>


int GetMinrun(int n) {
    // равно 1, если среди сдвинутых битов есть хотя бы один ненулевой
    int r = 0;
    while (n >= 64) {
        r |= (n & 1);
        n >>= 1;
    }
    return n + r;
}
template <typename T>
void insertion(DinArr<T>& arr, int size) {
    T value;
    int i;
    for (int j = 1; j < size; j++) {
        value = arr[j];
        i = j - 1;
        while (i >= 0 && arr[i] > value) {
            arr[i + 1] = arr[i];
            arr[i] = value;
            i = i - 1;
        }

    }
}
/*template <typename T>
void timSort(DinArr<T>& arr) {
    int n = arr.size();
    int MinRun = getMinrun(n);
    for (int i = 0; i < n; i += MinRun) {
        insertionSort(arr, i, std::min((i + MinRun - 1), (n - 1)));
    }

    for (int size = MinRun; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = std::min((left + size - 1), (n - 1));
            int right = std::min((left + 2 * size - 1), (n - 1));

            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}*/
