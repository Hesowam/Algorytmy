//
// Created by Владимир Марянчук on 25/10/2023.
//

#ifndef ALGO_222A_LAB03_BINARY_SEARCH_TREE_H
#define ALGO_222A_LAB03_BINARY_SEARCH_TREE_H

#endif //ALGO_222A_LAB03_BINARY_SEARCH_TREE_H

#include "node.h"
#include <iostream>

#define TREE_IS_EMPTY "\nThe tree is empty"
#define NODE_NOT_FOUNDED "\nNode with the specified key is not found"

using namespace std;

template<class T, typename K = T> requires equality_comparable<K> || integral<K> || same_as<K, string> ||
                                           floating_point<K>

class binary_search_tree {
private:
    node<T, K> *root_node;
    int size;
    int height = 0;

//    typedef void (binary_search_tree<T, K>::* callback)(node<T, K> *);
    using frame_callback = std::function<void(::node<T, K> * )>;


    void recursive_insert(node<T, K> *node, T data, K key) {
        bool left = node->have_left();
        bool right = node->have_right();

        K node_key = node->get_key();

        if (key > node_key) {
            if (right) recursive_insert(node->get_right_node(), data, key);
            else insert_node(node, data, key);
        } else if (key < node_key) {
            if (left) recursive_insert(node->get_left_node(), data, key);
            else insert_node(node, data, key);
        } else if (node_key == key) {
            insert_node(node, data, key);
        }
    }

    void infix_transverse(node<T, K> *node, frame_callback callback_fn) {
        if (node->have_left()) infix_transverse(node->get_left_node(), callback_fn);
        if (node->have_right()) infix_transverse(node->get_right_node(), callback_fn);
        callback_fn(node);
    }

    void insert_node(node<T, K> *p_node, T data, K key) {
        node<T, K> *new_node = new node(data, key);

        new_node->set_parent_node(p_node);
        new_node->set_left_node(nullptr);
        new_node->set_right_node(nullptr);

        if (key > p_node->get_key()) {
            p_node->set_right_node(new_node);
            size++;
        } else if (key < p_node->get_key()) {
            p_node->set_left_node(new_node);
            size++;
        } else if (p_node->get_key() == key) p_node->update(data);
    }

    void find_height(node<T, K> *node, int tmp_height) {
        if (node->have_left()) find_height(node->get_left_node(), tmp_height + 1);
        if (node->have_right()) find_height(node->get_right_node(), tmp_height + 1);
        if ((node->have_left() && node->have_right()) == false) {
            if (tmp_height > height) height = tmp_height;
        }
    }

    node<T, K> *find_node(node<T, K> *node, K key) {
        if (node->get_key() < key && node->have_right()) return find_node(node->get_right_node(), key);
        if (node->get_key() > key && node->have_left()) return find_node(node->get_left_node(), key);
        if (node->get_key() == key) return node;
        else return nullptr;
    }

    node<T, K> *get_last_right_node(node<T, K> *node) {
        if (node->have_right()) return get_last_right_node(node->get_right_node());
        else return node;
    }

    void delete_node(node<T, K> *node) {
        if (node->have_left()) {
            auto tmp_node = get_last_right_node(node->get_left_node());
            node->set_key(tmp_node->get_key());
            node->set_value(tmp_node->get_data());
            delete tmp_node;
            size--;
        } else if (node->have_right()) {
            auto tmp_node = node->get_right_node();
            node->set_key(tmp_node->get_key());
            node->set_value(tmp_node->get_data());
            node->set_right_node(tmp_node->get_right_node());
            node->set_left_node(tmp_node->get_left_node());
            delete tmp_node;
            size--;
        } else {
            if (root_node == node) root_node = nullptr;
            if (node->get_parent_node()->get_key() > node->get_key()) node->get_parent_node()->set_left_node(nullptr);
            else if (node->get_parent_node()->get_key() < node->get_key()) node->get_parent_node()->set_right_node(nullptr);
            delete node;
            size--;
        }
    }

public:
    binary_search_tree() {
        root_node = nullptr;
        size = 0;
    }

    binary_search_tree(T data, K key) {
        root_node = new node<T, K>(data, key);
        size++;
    }

    void insert(T data, K key) { // if we have key definition
        if (size == 0) {
            root_node = new node<T, K>(data, key);
            size++;
        } else recursive_insert(root_node, data, key);
    }

    void insert(T data) { // if key without definition
        if (size == 0) {
            root_node = new node<T, K>(data, data);
            size++;
        } else recursive_insert(root_node, data, data);
    }

    void get_string() {
        if (size <= 0) {
            cout << TREE_IS_EMPTY;
            return;
        }
        cout << "\n{\n\theight: " << get_height() << ";\n\tsize: " << size << ";\n\tnodes: [";

        auto print_fnc = [&](node <T, K> *node) {
            string parent = (node->have_parent()) ? to_string(node->get_parent_node()->get_key()) : "NULL";
            string left = (node->have_left()) ? to_string(node->get_left_node()->get_key()) : "NULL";
            string right = (node->have_right()) ? to_string(node->get_right_node()->get_key()) : "NULL";

            if constexpr (is_same_v<T, int> || is_same_v<T, double> || is_same_v<T, string> || is_same_v<T, char *> ||
                          is_same_v<T, float>) {
                cout << "\n\t\t(" << node->get_key() << ": [p: " << parent << ", l: " << left << ", r: " << right
                     << "], data: " << node->get_data() << ")";
            } else {
                cout << "\n\t\t(" << node->get_key() << ": [p: " << parent << ", l: " << left << ", r: " << right
                     << "], node pointer: " << &node << ")";
            }
        };

        infix_transverse(root_node, print_fnc);
        cout << "\n\t]\n}";
    }

    int get_height() {
        find_height(root_node, 1);
        return height;
    }

    node<T, K> * find(K key) {
        try {
            if (size == 0) throw (TREE_IS_EMPTY);
            node<T, K> *node = find_node(root_node, key);
            if (node != nullptr) {
                return node;
            }
            cerr << NODE_NOT_FOUNDED;
            return nullptr;
        } catch (string error) {
            cerr << error;
            ::exit(-1);
        }
    }

    void remove(K key) {
        try {
            if (size == 0) throw (TREE_IS_EMPTY);
            node<T, K> *node = find_node(root_node, key);
            if (node) {
                delete_node(node);
            } else cerr << NODE_NOT_FOUNDED;
        } catch (string error) {
            cerr << error;
            ::exit(-1);
        }
    }

    void clear() {
        auto delete_callback_fnc = [&](node <T, K> *node) {
            delete node;
            size--;
        };
        infix_transverse(root_node, delete_callback_fnc);
        root_node = nullptr;
        height = 0;
    }

    ~binary_search_tree() {
        clear();
    }
};
