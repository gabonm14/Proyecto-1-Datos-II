//
// Created by gabonm7 on 11/09/24.
//

#include "MPointerList.h"
#include <iostream>

template <typename T>
MPointerList<T>::MPointerList() : head(nullptr), tail(nullptr) {}

template <typename T>
MPointerList<T>::~MPointerList() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
void MPointerList<T>::add(T data) {
    Node* newNode = new Node(data);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

template <typename T>
void MPointerList<T>::remove(T data) {
    Node* current = head;
    while (current) {
        if (current->data == data) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            delete current;
            return;
        }
        current = current->next;
    }
}

template <typename T>
typename MPointerList<T>::Node* MPointerList<T>::find(T data) {
    Node* current = head;
    while (current) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
