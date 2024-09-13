//
// Created by gabriel on 13/09/24.
//

#include "MPointerGC.h"
#include <iostream>
#include <thread>
#include <chrono>


MPointerGC* MPointerGC::instance = nullptr;

MPointerGC* MPointerGC::getInstance() {
    if (!instance) {
        instance = new MPointerGC();
    }
    return instance;
}

MPointerGC::MPointerGC() {}

void MPointerGC::registerPointer(void* ptr) {
    std::lock_guard<std::mutex> lock(gc_mutex);
    pointers.add(ptr);
}

void MPointerGC::unregisterPointer(void* ptr) {
    std::lock_guard<std::mutex> lock(gc_mutex);
    pointers.remove(ptr);
}

void MPointerGC::collectGarbage() {
    std::lock_guard<std::mutex> lock(gc_mutex);
    Node<void*>* current = pointers.head;
    while (current) {
        if (current->data == nullptr) {  // Si el puntero es nulo, lo eliminamos
            Node<void*>* toDelete = current;
            current = current->next;
            pointers.remove(toDelete->data);
        } else {
            current = current->next;
        }
    }
}

