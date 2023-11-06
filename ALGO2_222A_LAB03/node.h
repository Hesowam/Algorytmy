//
// Created by Владимир Марянчук on 25/10/2023.
//

#ifndef ALGO_222A_LAB03_NODE_H
#define ALGO_222A_LAB03_NODE_H

#endif //ALGO_222A_LAB03_NODE_H

#include <iostream>


template<class T, class K>

class node {
private:
    node<T, K> * left_node;
    node<T, K> * right_node;
    node<T, K> * parent_node;
    T value;
    K key;

public:
    node(T data, K key){
        this->key = key;
        this->value = data;
        this->left_node = nullptr;
        this->right_node = nullptr;
        this->parent_node = nullptr;
    }

    void update(T data){
        this->value = data;
    }

    node<T, K> * get_left_node() {return left_node;}
    node<T, K> * get_right_node() {return right_node;}
    node<T, K> * get_parent_node() {return parent_node;}

    K get_key(){return key;}
    T get_data(){return value;}

    void set_left_node(node<T, K> * node) {left_node = node;}
    void set_right_node(node<T, K> * node) {right_node = node;}
    void set_parent_node(node<T, K> * node) {parent_node = node;}
    void set_value(T value) { this->value = value;}
    void set_key(K key) { this->key = key;}

    bool have_parent() { if (this->parent_node != nullptr) return true; return false; }
    bool have_left() { if (this->left_node != nullptr) return true; return false; }
    bool have_right() { if (this->right_node != nullptr) return true; return false; }

};
