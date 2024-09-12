//
// Created by gabonm7 on 11/09/24.
//

#ifndef LISTADUPLAMENTEVINCULADA_H
#define LISTADUPLAMENTEVINCULADA_H
#include <iostream>
using namespace std;


enum class DataType {
    INT,
    DOUBLE,
    FLOAT,
    UNKNOWN
};


struct Node {
    int id;
    void* address = nullptr;
    int refCount = 0;
    Node* next = nullptr;
    DataType type;


    Node(int id = 0, void* address = nullptr, int refCount = 0, Node* next = nullptr, DataType type = DataType::INT) : id(id), address(address), refCount(refCount), next(next), type(type) {}
};


class LinkedList {
private:
    Node* head;
    int size;

public:

    LinkedList() : head(nullptr) {}


    ~LinkedList() = default;

    void newMpointer(int id, void* address, DataType type);
    void addRef(int identifier);
    int substractRef(int identifier);
    void remove(int identifier);
    void print();
    int getSize();
    int getIDAt(int index);
    int getRefCount(int id);
};
#include "../ListaDuplamenteVinculada.cpp"
#endif
