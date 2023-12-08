// ALGO2 IS1 222A LAB06
// Volodymyr Marianchuk
// mv53868@zut.edu.pl

#ifndef ALGO2_222A_LAB06_BINARY_HEAP_H
#define ALGO2_222A_LAB06_BINARY_HEAP_H

#endif //ALGO2_222A_LAB06_BINARY_HEAP_H

#include <iostream>

#include "53868.algo2.lab02.dynamic_array.h"


template<typename V> requires equality_comparable<V>
class binary_heap {
private:
    dynamic_array<V> *heap;

    int calculate_parent(int index) {
        return (index - 1) / 2;
    }

    int calculate_left(int index) {
        return index * 2 + 1;
    }

    int calculate_right(int index) {
        return index * 2 + 2;
    }

    void swap(int first_index, int second_index) {
        V first_v = heap->operator[](first_index);
        heap->operator[](first_index) = heap->operator[](second_index);
        heap->operator[](second_index) = first_v;
    }

public:
    binary_heap() {
        heap = new dynamic_array<V>;
    }

    static bool greaterThan(V a, V b) {
        return a > b;
    }

    static bool lessThan(V a, V b) {
        return a < b;
    }

    void heapify_up(int index, bool (*comparisonFunction)(V, V)) {
        if (index <= 0) return;
        if (comparisonFunction(heap->operator[](index), heap->operator[](calculate_parent(index)))) {
            swap(index, calculate_parent(index));
            heapify_up(calculate_parent(index), comparisonFunction);
        }
    }

    void heapify_down(int index, bool (*comparisonFunction)(V, V)){
        int left_child = calculate_left(index);
        int right_child = calculate_right(index);

        if (left_child > heap->get_size() - 1 || right_child > heap->get_size() - 1) return;

        if (comparisonFunction(heap->operator[](left_child), heap->operator[](right_child))) {
            swap(left_child, index);
            heapify_down(left_child, comparisonFunction);
        } else if (comparisonFunction(heap->operator[](right_child), heap->operator[](left_child))) {
            swap(right_child, index);
            heapify_down(right_child, comparisonFunction);
        }
    }

    void insert(V value, bool (*comparisonFunction)(V, V)) {
        heap->push(value);
        heapify_up(heap->get_size() - 1, comparisonFunction);
    }

    void to_string() {
        heap->toString();
        ::printf("[");
        for (int i = 0; i < heap->get_size(); ++i) {
            cout << "\t" << heap->operator[](i);
        }
        ::printf("\t]\n");
    }

    void pop( bool (*comparisonFunction)(V, V)){
        swap(0, heap->get_size() - 1);
        heap->remove_last();
        heapify_down(0, comparisonFunction);
    }

};