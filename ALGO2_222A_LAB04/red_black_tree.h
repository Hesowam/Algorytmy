//
// Created by Владимир Марянчук on 10/11/2023.
//

#ifndef ALGO2_222A_LAB03_RED_BLACK_TREE_H
#define ALGO2_222A_LAB03_RED_BLACK_TREE_H

#endif //ALGO2_222A_LAB03_RED_BLACK_TREE_H

#include <iostream>
#include "node.h"

#define TREE_IS_EMPTY "\nThe tree is empty"
#define NODE_NOT_FOUNDED "\nNode with the specified key is not found"

// false - black, true - red

template<class T, typename K = T> requires std::equality_comparable<K> || std::integral<K> || std::same_as<K, std::string> ||
        std::floating_point<K>
class red_black_tree {
private:
    node<T, K> *root_node;
    int size = 0;
    int height = 0;

    using frame_callback = std::function<void(::node<T, K> * )>;

    void infix_transverse(node<T, K> *node, frame_callback callback_fn) {
        if (node->have_left_node()) infix_transverse(node->get_left_node(), callback_fn);
        if (node->have_right_node()) infix_transverse(node->get_right_node(), callback_fn);
        callback_fn(node);
    }

    void recursive_insert(node<T, K> *node, T data, K key) {
        bool left = node->have_left_node();
        bool right = node->have_right_node();

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

    void insert_node(node<T, K> *p_node, T data, K key) {
        node<T, K>* new_node = new node(data, key, false);

        new_node->set_parent_node(p_node);
        new_node->set_left_node(nullptr);
        new_node->set_right_node(nullptr);

        if (key > p_node->get_key()) {
            p_node->set_right_node(new_node);
            size++;
        } else if (key < p_node->get_key()) {
            p_node->set_left_node(new_node);
            size++;
        } else if (p_node->get_key() == key) {
            p_node->set_data(data);
            return;
        }

        new_node->set_flag(true);
        fix(new_node);
    }

    void find_height(node<T, K> *node, int tmp_height) {
        if (node->have_left_node()) find_height(node->get_left_node(), tmp_height + 1);
        if (node->have_right_node()) find_height(node->get_right_node(), tmp_height + 1);
        if ((node->have_left_node() && node->have_right_node()) == false) {
            if (tmp_height > height) height = tmp_height;
        }
    }

    node<T, K> *find_node(node<T, K> *node, K key) {
        if (node->get_key() < key && node->have_right_node()) return find_node(node->get_right_node(), key);
        if (node->get_key() > key && node->have_left_node()) return find_node(node->get_left_node(), key);
        if (node->get_key() == key) return node;
        else return nullptr;
    }

    void fix(node<T, K> *selected_node) {
        if (selected_node != root_node && selected_node->get_parent_node()->get_flag()) {
            node<T, K>* grandpa_node = selected_node->get_parent_node()->get_parent_node();
            node<T, K>* parent_node = selected_node->get_parent_node();

            if (parent_node->is_left_child()) {
                node<T, K>* uncle = grandpa_node->get_right_node();

                if (uncle != nullptr && uncle->get_flag()) {
                    uncle->set_flag(false);
                    parent_node->set_flag(false);
                    parent_node->get_parent_node()->set_flag(true);
                } else {
                    if (selected_node->is_right_child()) {
                        selected_node = selected_node->get_parent_node();
                        left_rotate(selected_node);
                    }
                    selected_node->get_parent_node()->set_flag(false);
                    selected_node->get_parent_node()->get_parent_node()->set_flag(true);
                    right_rotate(selected_node->get_parent_node()->get_parent_node());
                }
            } else {
                node<T, K>* uncle = grandpa_node->get_left_node();

                if (uncle != nullptr && uncle->get_flag()) {
                    selected_node->get_parent_node()->set_flag(false);
                    uncle->set_flag(false);
                    selected_node->get_parent_node()->get_parent_node()->set_flag(true);
                    fix(selected_node->get_parent_node()->get_parent_node());
                } else {
                    if (selected_node->is_left_child()) {
                        selected_node = selected_node->get_parent_node();
                        right_rotate(selected_node->get_parent_node());
                    }
                    selected_node->get_parent_node()->set_flag(false);
                    selected_node->get_parent_node()->get_parent_node()->set_flag(true);
                    left_rotate(selected_node->get_parent_node()->get_parent_node());
                }
            }
        }
        if (root_node->get_flag()) root_node->set_flag(false);
    }

    void right_rotate(node<T, K> *parent_node) {
        node<T, K>* left_node = parent_node->get_left_node();

        if (!parent_node->have_left_node()) return;
        if (left_node != nullptr && left_node->have_right_node() ) left_node->get_right_node()->set_parent_node(parent_node);
        left_node->set_parent_node(parent_node->get_parent_node());
        parent_node->set_left_node(left_node->get_right_node());

        if (!parent_node->have_parent_node()) root_node = left_node;
        else if (parent_node->is_left_child()) { parent_node->get_parent_node()->set_left_node(left_node); }
        else { parent_node->get_parent_node()->set_right_node(left_node); }

        left_node->set_right_node(parent_node);
        parent_node->set_parent_node(left_node);
    }

    void left_rotate(node<T, K> *parent_node) {
        node<T, K> * right_node = parent_node->get_right_node();

        if (!parent_node->have_right_node()) return;
        if (right_node->have_left_node())
            right_node->get_left_node()->set_parent_node(parent_node);
        parent_node->set_right_node(right_node->get_left_node());
        right_node->set_parent_node(parent_node->get_parent_node());

        if (!parent_node->have_parent_node()) root_node = right_node;
        else if (parent_node->is_left_child()) { parent_node->get_parent_node()->set_left_node(right_node); }
        else { parent_node->get_parent_node()->set_right_node(right_node); }

        right_node->set_left_node(parent_node);
        parent_node->set_parent_node(right_node);
    }


public:
    red_black_tree() {
        root_node = nullptr;
    }

    red_black_tree(T data) {
        root_node = new node<T>(data, false);
        height = 1;
        size++;
    }

    red_black_tree(T data, K key) {
        root_node = new node<T, K>(data, key, false);
        height = 1;
        size++;
    }

    void get_string() {
        if (size <= 0) {
            std::cerr << TREE_IS_EMPTY;
            return;
        }
        find_height(root_node, 1);
        std::cout << "\n{\n\theight: " << height << ";\n\tsize: " << size << ";\n\tnodes: [";

        auto print_fnc = [&](node <T, K> *node) {
            std::string parent = (node->have_parent_node()) ? to_string(node->get_parent_node()->get_key()) : "NULL";
            std::string left = (node->have_left_node()) ? to_string(node->get_left_node()->get_key()) : "NULL";
            std::string right = (node->have_right_node()) ? to_string(node->get_right_node()->get_key()) : "NULL";

            std::string color = node->get_flag() ? "\x1B[91mRED\033[0m" : "\x1B[37mBLACK\033[0m";

            if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double> || std::is_same_v<T, std::string> || std::is_same_v<T, char *> ||
                    std::is_same_v<T, float>) {
                std::cout << "\n\t\t(" << node->get_key() << ": [p: " << parent << ", l: " << left << ", r: " << right
                     << ", color: " << color << "], data: " << node->get_data() << ")";
            } else {
                std::cout << "\n\t\t(" << node->get_key() << ": [p: " << parent << ", l: " << left << ", r: " << right
                     << ", color: " << color << "], node pointer: " << &node << ")";
            }
        };

        infix_transverse(root_node, print_fnc);
        std::cout << "\n\t]\n}";
    }

    void insert(T data, K key) {
        if (size == 0) {
            root_node = new node<T, K>(data, key, false);
            size++;
        } else recursive_insert(root_node, data, key);
    }

    void insert(T data) {
        if (size == 0) {
            root_node = new node<T, K>(data, data);
            size++;
        } else recursive_insert(root_node, data, data);
    }

    node<T, K> * find(K key) {
        try {
            if (size == 0) throw (TREE_IS_EMPTY);
            node<T, K> *node = find_node(root_node, key);
            if (node != nullptr) {
                return node;
            }
            std::cerr << NODE_NOT_FOUNDED;
            return nullptr;
        } catch (std::string error) {
            std::cerr << error;
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

    ~red_black_tree() {
        clear();
    }

};