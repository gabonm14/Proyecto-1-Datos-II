//
// Created by gabonm7 on 7/09/24.
//

#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"

template <typename T>
class MPointer {
private:
    T* ptr;  // Puntero al tipo T
    int id;  // ID único generado por MPointerGC
    static MPointerGC* gc;  // Referencia al recolector de basura

public:
    MPointer();
    ~MPointer();

    static MPointer<T> New();
    T& operator*();  // Sobrecarga del operador *
    T* operator&();  // Sobrecarga del operador &
    MPointer<T>& operator=(const T& value);  // Asignación de valor
    MPointer<T>& operator=(const MPointer<T>& other);  // Asignación entre MPointers
    int getId() const;
};

// Inicialización del puntero gc
template <typename T>
MPointerGC* MPointer<T>::gc = MPointerGC::getInstance();

// Constructor
template <typename T>
MPointer<T>::MPointer() : ptr(new T), id(gc->registerPointer(ptr)) {}

// Destructor
template <typename T>
MPointer<T>::~MPointer() {
    gc->unregisterPointer(ptr);
    delete ptr;
}


template <typename T>
MPointer<T> MPointer<T>::New() {
    return MPointer<T>();
}

// Sobrecarga del operador *
template <typename T>
T& MPointer<T>::operator*() {
    return *ptr;
}

// Sobrecarga del operador &
template <typename T>
T* MPointer<T>::operator&() {
    return ptr;
}

// Asignación de valor
template <typename T>
MPointer<T>& MPointer<T>::operator=(const T& value) {
    *ptr = value;
    return *this;
}

// Asignación entre MPointers
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

// Obtener el ID del puntero
template <typename T>
int MPointer<T>::getId() const {
    return id;
}

#endif
