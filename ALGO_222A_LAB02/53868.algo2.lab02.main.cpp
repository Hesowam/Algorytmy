#include <iostream>
#include "53868.algo2.lab02.dynamic_array.h"


using namespace std;

struct coordinates {
    int x;
    int y;
};

int main() {
    dynamic_array<coordinates> * array = new dynamic_array<coordinates>();

    const int order = 5;
    const int n = pow(10, order);

    clock_t t1 = clock();
    double max_time_per_element = 0.0;

    for (int i = 0; i < n; i++) {
        coordinates tmp_coordinates;
        tmp_coordinates.x =  rand() % 100 + (-1);
        tmp_coordinates.y =  rand() % 100 + (-1);

        clock_t t1_element = clock();
        array->push(tmp_coordinates);
        clock_t t2_element = clock();

        double time_per_element = t2_element - t1_element;

        if (time_per_element > max_time_per_element) {
            cout << "\nFound a new worst-case hour of execution of the algorithm for adding a new element. Index: " << i << " Time: " << 1000.0 * (time_per_element) / CLOCKS_PER_SEC << "ms";
            max_time_per_element = time_per_element;
        }

    }

    clock_t t2 = clock();

    array->toString();
    cout << "\n\nTotal code execution time for ["<<n<<"] elements: "<<1000.0 * (t2-t1) / CLOCKS_PER_SEC<<"ms";

    delete array;


    return 0;
}
