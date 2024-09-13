//
// Created by gabonm7 on 7/09/24.
//

#include "MPointer.h"
#include <iostream>

template <typename T>
MPointerGC* MPointer<T>::gc = MPointerGC::getInstance();

template <typename T>
MPointer<T>::MPointer() : ptr(new T), id(gc->registerPointer(ptr)) {}

template <typename T>
MPointer<T>::~MPointer() {
    gc->unregisterPointer(ptr);
    delete ptr;
}

template <typename T>
MPointer<T> MPointer<T>::New() {
    return MPointer<T>();
}

template <typename T>
T& MPointer<T>::operator*() {
    return *ptr;
}

template <typename T>
T* MPointer<T>::operator&() {
    return ptr;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const T& value) {
    *ptr = value;
    return *this;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {
        gc->unregisterPointer(ptr);
        ptr = other.ptr;
        id = other.id;
        gc->registerPointer(ptr);
    }
    return *this;
}

template <typename T>
int MPointer<T>::getId() const {
    return id;
}

