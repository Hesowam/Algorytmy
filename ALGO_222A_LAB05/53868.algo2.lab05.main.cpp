#include <iostream>
#include "53868.algo2.lab05.hash_table.h"

std::string random_string(int length) {
    const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::string random_string;

    for (int i = 0; i < length; ++i) {
        random_string += CHARACTERS[::rand() % 62];
    }

    return random_string;
}


int main() {
    const int MAX_ORDER = 6;

    hash_table table;

    double sum_time = 0;
    int sum_n = 0;

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);

        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            table.insert(random_string(i % 40 + 1), i);
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        cout << n << "\t objects added in\t" << std::chrono::duration<double, std::milli>(t2 - t1).count() << "ms\n";
        sum_time += std::chrono::duration<double, std::milli>(t2 - t1).count();
        sum_n += n;
    }

    cout << "When using the hash table, it takes ~" << (sum_time / sum_n) * 1000
         << "ms on average to add 1000 elements to the list" << endl;

    sum_time = 0;
    sum_n = 0;

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, 4);
        int hist = 0;

        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            int value = table.search(random_string(i % 10 + 1));
            if (value != -1) {
                hist++;
            }
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << std::endl << "Out of " << n << " attempts, " << hist << " objects were found in "
                  << std::chrono::duration<double, std::milli>(t2 - t1).count() << "ms.";
        sum_time += std::chrono::duration<double, std::milli>(t2 - t1).count();
        sum_n += n;
    }

    cout << endl << "When using a hash table, it takes an average ~" << (sum_time / sum_n) * 1000
         << "ms  to search for 1000 element";

    table.to_string();
    return 0;
}
