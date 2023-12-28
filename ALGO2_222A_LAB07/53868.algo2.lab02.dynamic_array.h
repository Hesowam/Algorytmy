//
// Created by Владимир Марянчук on 23/10/2023.
//

#ifndef UNTITLED6_DYNAMIC_ARRAY_H
#define UNTITLED6_DYNAMIC_ARRAY_H

#endif //UNTITLED6_DYNAMIC_ARRAY_H

#define START_LENGTH 10
#define GROW 2.0

#include <iostream>
#include <type_traits>

using namespace std;


template<typename T>
concept Comparable = requires(T a, T b) {
    { a == b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
    { a < b }  -> std::convertible_to<bool>;
    { a > b }  -> std::convertible_to<bool>;
    { a <= b } -> std::convertible_to<bool>;
    { a >= b } -> std::convertible_to<bool>;
};

template<class T>

class dynamic_array {
private:
    T *array;
    int allocated_memory = START_LENGTH;
    int size = 0;
    double grow = GROW;

    bool isFull() {
        if (size < allocated_memory) return false;
        return true;
    }

    void expand() {
        allocated_memory = grow * allocated_memory;
        auto *tmp_array = new T[allocated_memory];

        for (int i = 0; i < size; ++i) {
            tmp_array[i] = array[i];
        }

        array = tmp_array;
    }

    void quick_sort(int left, int right) {
        if (left >= right) return;
        int i = partition(left, right);
        quick_sort(left, i - 1);
        quick_sort(i + 1, right);
    }

    int partition(int left, int right) {
        T x = array[right];
        int leftIndex = left - 1;
        for (int j = left; j <= right - 1; j++) {
            if (array[j] <= x) {
                leftIndex++;
                swap(leftIndex, j);
            }
        }
        swap(leftIndex + 1, right);
        return leftIndex + 1;
    }

    void swap(int left_index, int right_index) {
        T tmp = array[left_index];
        array[left_index] = array[right_index];
        array[right_index] = tmp;
    }

public:
    dynamic_array() {
        this->array = new T[10];
    }

    dynamic_array(int n) {
        this->array = new T[n];
        this->allocated_memory = n;
    }

    int get_size() {
        return this->size;
    }


    void sort() {
        if (Comparable<T> == false) {
            cerr << "This array cannot be sorted.";
        }
        if (size > 1) quick_sort(0, size - 1);
    }

    void push(T data) {
        if (isFull()) expand();
        array[size] = data;
        size++;
    }

    void remove_last() {
        array[this->size - 1] = 0;
        size--;
    }

    void toString() {
        std::cout << "\nThe array consists of " << size << " elements\nMaximum array length " << allocated_memory
                  << " elements\nArray pointer (" << array << ")" << endl;
        for (int i = 0; i < size; ++i) {
            cout << array[i] << " ";
        }
    }

    T &operator[](int index) {
        if (index < 0 || index >= allocated_memory) {
            throw std::out_of_range("Index out of bounds");
        }
        return array[index];
    }

    void clear() {
        delete[] array;
        array = new T[START_LENGTH];
        allocated_memory = START_LENGTH;
        size = 0;
    }

    ~dynamic_array() {
        delete[] array;
    }

};