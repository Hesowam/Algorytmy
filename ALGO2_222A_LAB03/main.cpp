#include <iostream>
#include "binary_search_tree.h"

using namespace std;

struct coordinates {
    float x;
    float y;
};

int main() {
    const int MAX_ORDER = 4;

    binary_search_tree<int> *bst_default_types = new binary_search_tree<int>();
    binary_search_tree<coordinates, int> *bst = new binary_search_tree<coordinates, int>();


    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);

        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            coordinates tmp_coord = *new coordinates();
            int key = ::rand() % 10000 + 1;
            tmp_coord.x = ::rand() % 1000 + (-1000);
            tmp_coord.y = ::rand() % 1000 + (-1000);
            bst->insert(tmp_coord, key);
        }
        clock_t t2 = clock();
        cout << n << "\t objects added in\t" << 1000.0 * (t2 - t1) / CLOCKS_PER_SEC << "ms\n";
    }

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);
        int hits = 0;

        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            int key = ::rand() % 10000 + 1;
            auto tmp = bst->find(key);
            if (tmp != nullptr) hits++;
        }
        clock_t t2 = clock();
        cout << hits << "\t objects founded in\t" << 1000.0 * (t2 - t1) / CLOCKS_PER_SEC << "ms\n";
    }






    return 0;
}
