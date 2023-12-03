//
// Created by Владимир Марянчук on 09/10/2023.
//

#include <iostream>
#include "53868.algo2.lab01.node.h"

#ifndef UNTITLED5_LIST_H
#define UNTITLED5_LIST_H


using namespace std;

template<class T>
class List {
private:
    int size;
    Node<T> *head_node;
    Node<T> *tail_node;


    void sortIndexes() {
        Node<T> *node = head_node;
        for (int i = 0; i < size; i++) {
            node->setIndex(i);
            node = node->getNext();
        }
    }

    void addFirst(T data) {
        size += 1;
        Node<T> *node = new Node(data);
        tail_node = node;
        head_node = node;
    }

public:

    List() {
        tail_node = nullptr;
        head_node = nullptr;
        size = 0;
    }

    List(T data) {
        Node<T> *node = new Node(data);
        tail_node = node;
        head_node = node;
        size = 1;
    }

    void addBack(T data) {
        if (tail_node == nullptr && head_node == nullptr) {
            addFirst(data);
        } else {
            size += 1;
            Node<T> *node = new Node(data);
            node->setPrev(tail_node);
            node->setIndex(tail_node->getIndex() + 1);
            tail_node->setNext(node);
            tail_node = node;
        }
    }

    void add(int index, T data) {
        try {
            if (index >= size && head_node) throw (-1);
            if (tail_node == nullptr && head_node == nullptr) {
                addFirst(data);
            } else {
                size += 1;
                Node<T> *node = new Node(data);

                node->setPrev(node->getNode(head_node, index - 1));
                node->setNext(node->getNode(head_node, index));

                node->getPrev()->setNext(node);
                node->getNext()->setPrev(node);

                sortIndexes();
            }
        } catch (int status) {
            std::cout << std::endl << "Entered index is not correct";
            exit(status);
        }
    }

    void addFront(T data) {
        if (tail_node == nullptr && head_node == nullptr) {
            addFirst(data);
        } else {
            size += 1;
            Node<T> *node = new Node(data);
            node->setNext(head_node);
            head_node->setPrev(node);
            head_node = node;
            sortIndexes();
        }
    }

    T get(int index) {
        try {
            if (index >= size && !!head_node) throw (-1);
            return head_node->getNode(head_node, index)->getData();
        } catch (int status) {
            std::cout << std::endl << "Entered index is not correct";
            exit(status);
        }
    }

    int length() { return size; }

    void string() {
        cout << "\n\n\tThe list consists of [" << size << "] items";
        for (int i = 0; i < size; i++) {
            cout << endl << "|\tIndex: " << head_node->getNode(head_node, i)->getIndex();
            cout << "\t|\tPointer: " << head_node->getNode(head_node, i) << "\t|";
        }
    }

    void remove(int index) {
        try {
            if (index >= size && head_node != nullptr) throw (-1);
            Node<T> *node = head_node->getNode(head_node, index);

            if (node == head_node) {
                removeFirst();
                return;
            }
            if (node == tail_node) {
                removeLast();
                return;
            }

            if (node->getPrev() != nullptr) node->getPrev()->setNext(node->getNext());
            if (node->getNext() != nullptr) node->getNext()->setPrev(node->getPrev());

            delete node;
            size--;

            sortIndexes();
        } catch (int errCode) {
            std::cout << std::endl << "Entered index is not correct";
            exit(errCode);
        }
    }

    void removeFirst() {
        size--;
        Node<T> *node = head_node->getNext();

        node->setPrev(nullptr);

        delete head_node;
        head_node = node;

        sortIndexes();
    }

    void removeLast() {
        size--;
        Node<T> *node = tail_node->getPrev();

        node->setNext(nullptr);

        delete tail_node;
        tail_node = node;
    }

    void update(int index, T data) {
        head_node->getNode(head_node, index)->setData(data);
    }

    void clear() {
        while (head_node != nullptr) {
            Node<T> *node = head_node;
            head_node = head_node->getNext();
            delete node;
        }
        size = 0;
    }
};


#endif //UNTITLED5_LIST_H
