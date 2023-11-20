#include <iostream>
#include "red_black_tree.h"

using namespace std;

struct coordinates {
    float x;
    float y;
};

int main() {
    const int MAX_ORDER = 4;

    red_black_tree<coordinates, int> rbt = * new red_black_tree<coordinates, int>();

    double sum_time = 0;
    int sum_n = 0;

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);

        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            coordinates tmp_coord = * new coordinates();
            tmp_coord.x = ::rand() % 1000;
            tmp_coord.y = ::rand() % 1000 + (-1000);
            rbt.insert(tmp_coord, ::rand() % 1000000 + (-1000000));
        }
        clock_t t2 = clock();
        cout << n << "\t objects added in\t" << 1000.0 * (t2 - t1) / CLOCKS_PER_SEC << "ms\n";
        sum_time += 1000.0 * (t2 - t1) / CLOCKS_PER_SEC;
        sum_n += n;
    }

    cout <<"When using the red-black tree algorithm, it takes ~"<< (sum_time / sum_n) * 1000 << "ms on average to add 1000 elements to the tree";

//    rbt.get_string();
    return 0;
}
