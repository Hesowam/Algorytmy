#include <iomanip>
#include <iostream>
#include <cstring>
#include "53868.algo2.lab02.dynamic_array.h"
#include "binary_heap.h"

static bool greaterThan(int a, int b) {
    return a > b;
}

static bool lessThan(int a, int b) {
    return a < b;
}

void counting_sort(int *array, int n, int m) {
    int *tmp_arr = new int[m]();
    memset(tmp_arr, 0, m * sizeof(*tmp_arr));

    for (int i = 0; i < n; i++) {
        tmp_arr[array[i]]++;
    }

    for (int i = 0, k = 0; i < m; i++) {
        while (tmp_arr[i] > 0) {
            array[k] = i;
            tmp_arr[i]--;
            k++;
        }
    }
    delete[] tmp_arr;
}

void bucket_sort(int *array, int n, int m) {
    dynamic_array<dynamic_array<int>> tmp_arr = *new dynamic_array<dynamic_array<int>>((m /10) + 1);

    for (int i = 0; i < n; i++) {
        int array_index = ::floor(array[i] / 10);
        tmp_arr[array_index].push(array[i]);
    }

    for (int i = 0, k = 0; i < m / 10 ; ++i) {
        if (tmp_arr[i].get_size() > 0) {
            tmp_arr[i].sort();
            for (int j = 0; j < tmp_arr[i].get_size(); ++j) {
                array[k] = tmp_arr[i][j];
                k++;
            }
        }
    }
}

int main() {
    srand(0);

    const int MAX_ORDER = 5;
    const int m = (int) pow(10, 5);
    comparison<int> cmp = *new comparison<int>;

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = (int) pow(10, o);

        int *array1 = new int[n];
        for (int i = 0; i < n; i++) {
            int rand_val = rand() % m + 1;
            array1[i] = rand_val;
        }

        int *array2 = new int[n];
        int *array3 = new int[n];
        memcpy(array2, array1, n * sizeof(int));
        memcpy(array3, array1, n * sizeof(int));

        auto t1 = std::chrono::high_resolution_clock::now();
        counting_sort(array1, n, m);
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << "Using sorting by counting an array of " << std::setw(8) << n << " elements is sorted in "
                  << std::setw(9) << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms\n";


        t1 = std::chrono::high_resolution_clock::now();
        bucket_sort(array2, n, m);
        t2 = std::chrono::high_resolution_clock::now();

        std::cout << "Using bucket sort an array of " << std::setw(8) << n << " elements is sorted in "
                  << std::setw(9) << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms\n";

        t1 = std::chrono::high_resolution_clock::now();
        binary_heap<int> heap = *new binary_heap<int>(array1, n, cmp.lessThan);
        heap.sort();
        t2 = std::chrono::high_resolution_clock::now();

        std::cout << "Using heap sort an array of " << std::setw(8) << n << " elements is sorted in "
                  << std::setw(9) << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms\n";
    }
    return 0;
}