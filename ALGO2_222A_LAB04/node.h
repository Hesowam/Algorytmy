//
// Created by Владимир Марянчук on 06/11/2023.
//

#ifndef ALGO2_222A_LAB03_NODE_H
#define ALGO2_222A_LAB03_NODE_H

#endif //ALGO2_222A_LAB03_NODE_H

#include <iostream>

// false - black, true - red
template<class T, typename K = T> requires std::equality_comparable<K> || std::integral<K> || std::same_as<K, std::string> ||
        std::floating_point<K>

class node {
private:
    bool flag;
    node<T, K> *parent_node;
    node<T, K> *left_node;
    node<T, K> *right_node;
    T data;
    K key;

public:
    node(T data, bool flag) {
        parent_node = nullptr;
        left_node = nullptr;
        right_node = nullptr;
        this->data = data;
        key = data;
        this->flag = flag;
    }

    node(T data, K key, bool flag) {
        parent_node = nullptr;
        left_node = nullptr;
        right_node = nullptr;
        this->data = data;
        this->key = key;
        this->flag = flag;
    }

    void set_flag(bool flag) { this->flag = flag; }
    void set_data(T data) { this->data = data; }
    void set_key(K key) { this->key = key; }
    void set_parent_node(node<T, K> * node){ parent_node = node; }
    void set_left_node(node<T, K> * node){ left_node = node; }
    void set_right_node(node<T, K> * node){ right_node = node; }

    bool get_flag(){ return flag; }
    T get_data(){ return data; }
    K get_key(){ return key; }
    node<T, K> * get_parent_node(){ return parent_node; }
    node<T, K> * get_left_node(){ return left_node; }
    node<T, K> * get_right_node(){ return right_node; }

    bool have_parent_node(){ return parent_node != nullptr ? true : false; }
    bool have_left_node(){ return left_node != nullptr ? true : false; }
    bool have_right_node(){ return right_node != nullptr ? true : false; }

    bool is_left_child(){
        if (this->parent_node->have_left_node() && this->parent_node->get_left_node() == this) return true;
        return false;
    }

    bool is_right_child(){
        if (this->parent_node->have_right_node() && this->parent_node->get_right_node() == this) return true;
        return false;
    }
};