//
// Created by gabriel on 13/09/24.
//
#include "MPointer.h"
#include "MPointerGC.h"
#include <iostream>

int main() {
    // Inicializa el recolector de basura
    MPointerGC* gc = MPointerGC::getInstance();

    // Crea algunos MPointers
    MPointer<int> ptr1 = MPointer<int>::New();
    MPointer<int> ptr2 = MPointer<int>::New();

    // Asigna valores
    *ptr1 = 42;
    *ptr2 = 23;

    std::cout << "Valor de ptr1: " << *ptr1 << std::endl;
    std::cout << "Valor de ptr2: " << *ptr2 << std::endl;

    // Asigna ptr1 a ptr2 (ambos apuntan a la misma dirección)
    ptr2 = ptr1;
    std::cout << "Nuevo valor de ptr2 (apunta a ptr1): " << *ptr2 << std::endl;

    // Destruye ptr1
    {
        MPointer<int> ptr3 = MPointer<int>::New();
        *ptr3 = 100;
        std::cout << "Valor de ptr3: " << *ptr3 << std::endl;
    }  // ptr3 se destruye aquí

    // Forzar recolección de basura (manual para prueba)
    gc->collectGarbage();

    return 0;
}
