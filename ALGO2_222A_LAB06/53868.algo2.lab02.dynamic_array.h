//
// Created by Владимир Марянчук on 23/10/2023.
//

#ifndef UNTITLED6_DYNAMIC_ARRAY_H
#define UNTITLED6_DYNAMIC_ARRAY_H

#endif //UNTITLED6_DYNAMIC_ARRAY_H

#define START_LENGTH 10
#define GROW 2.0

#include <iostream>

using namespace std;

template<class T>

class dynamic_array {
private:
    T * array;
    int allocated_memory = START_LENGTH;
    int size = 0;
    double grow = GROW;

    bool isFull() {
        if (size < allocated_memory) return false;
        return true;
    }

    void expand() {
        allocated_memory = grow * allocated_memory;
        auto * tmp_array =  new T[allocated_memory];

        for (int i = 0; i < size; ++i) {
            tmp_array[i] = array[i];
        }

        array = tmp_array;
    }

public:
    dynamic_array() {
        this->array = new T[10];
    }

    int get_size(){
        return this->size;
    }

    void push(T data) {
        if (isFull()) expand();
        array[size] = data;
        size++;
    }

    void remove_last(){
        array[this->size - 1] = 0;
        size--;
    }

    void toString(){
        std::cout << "\nThe array consists of "<<size<<" elements\nMaximum array length "<<allocated_memory<<" elements\nArray pointer (" << array << ")";
    }

    T& operator[] (int index) {
        if (index < 0 || index >= size) {
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

    ~dynamic_array(){
        delete[] array;
    }

};