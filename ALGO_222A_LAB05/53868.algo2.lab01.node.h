//
// Created by Владимир Марянчук on 10/10/2023.
//
#include <iostream>

#ifndef UNTITLED5_NODE_H
#define UNTITLED5_NODE_H


using namespace std;

template<class T>
class Node {
private:
    int index;
    Node<T> *next;
    Node<T> *prev;
    T data;

public:
    Node() {
        index = 0;
        next = nullptr;
        prev = nullptr;
    }

    Node(T data) {
        Node();
        this->data = data;
    }

    int getIndex() { return index; }

    Node<T> *getNext() { return next; }

    Node<T> *getPrev() { return prev; }

    T getData() { return data; }

    Node<T> *getNode(Node<T> *node, int index) {
        if (node->index == index) return node;
        return getNode(node->getNext(), index);
    }

    void deletePrevNode() { prev = nullptr; }

    void setData(T data) { this->data = data; }

    void setIndex(int index) { this->index = index; }

    void setNext(Node<T> *node) { next = node; }

    void setPrev(Node<T> *node) { prev = node; }
};


#endif //UNTITLED5_NODE_H
