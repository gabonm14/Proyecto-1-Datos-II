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

#include "MPointer.tpp"  // Implementación en un archivo separado para templates
#endif

