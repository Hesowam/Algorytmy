// ALGO2 IS1 222A LAB06
// Volodymyr Marianchuk
// mv53868@zut.edu.pl

#include <iostream>
#include "binary_heap.h"

int main() {
    const int MAX_ORDER = 7;
    binary_heap<int> *bh = new binary_heap<int>();

    double sum_time = 0;
    int sum_n = 0;

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);

        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            int val = ::rand() % n + 1;
            bh->insert(val, bh->greaterThan);
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        cout << n << " objects were added to the binary heap in " << std::chrono::duration<double, std::milli>(t2 - t1).count() << "ms\n";
        sum_time += std::chrono::duration<double, std::milli>(t2 - t1).count();
        sum_n += n;
    }

    cout << "\nOn average it takes ~" << (sum_time / sum_n) * 1000
         << "ms to add 1000 items" << endl;

    sum_time = 0;
    sum_n = 0;

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);

        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            bh->pop(bh->greaterThan);
        }
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << n << " objects were removed from the binary heap in "
                  << std::chrono::duration<double, std::milli>(t2 - t1).count() << "ms.\n";
        sum_time += std::chrono::duration<double, std::milli>(t2 - t1).count();
        sum_n += n;
    }

    cout << "\nOn average it takes ~" << (sum_time / sum_n) * 1000
         << "ms to delete 1000 items" << endl;
    delete bh;
    return 0;
}
