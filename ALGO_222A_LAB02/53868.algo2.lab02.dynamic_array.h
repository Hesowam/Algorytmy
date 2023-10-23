//
// Created by Владимир Марянчук on 23/10/2023.
//

#ifndef UNTITLED6_DYNAMIC_ARRAY_H
#define UNTITLED6_DYNAMIC_ARRAY_H

#endif //UNTITLED6_DYNAMIC_ARRAY_H

#define START_LENGTH 1
#define GROW 2.0

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

    void push(T data) {
        if (isFull()) expand();
        array[size] = data;
        size++;
    }

    void toString(){
        cout << "\nThe array consists of "<<size<<" elements\nMaximum array length "<<allocated_memory<<" elements\nArray pointer (" << array << ")";
    }

    T& operator[] (int index) {
        return array[index];
    }

    void clear() {
        for (int i = 0; i <= size; i++) {
            array[i] = 0;
        }
        this->size = 0;
    }

    ~dynamic_array(){
        delete[] array;
    }

};