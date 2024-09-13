//
// Created by gabonm7 on 11/09/24.
//

#ifndef MPOINTERLIST_H
#define MPOINTERLIST_H


template <typename T>
class MPointerList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    MPointerList();
    ~MPointerList();

    void add(T data);
    void remove(T data);
    Node* find(T data);
};

#include "MPointerList.tpp"
#endif

