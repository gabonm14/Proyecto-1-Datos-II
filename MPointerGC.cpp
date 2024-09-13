//
// Created by gabriel on 13/09/24.
//
#include <mutex>
#include "MPointerGC.h"
#include <iostream>

// Inicializamos el puntero singleton
MPointerGC* MPointerGC::instance = nullptr;
std::mutex MPointerGC::gc_mutexx;
// Constructor privado: inicializa el hilo del recolector de basura
MPointerGC::MPointerGC() {
    gcThread = std::thread(&MPointerGC::verifyReferences, this) {
        runGCThread();
    }).detach();  // Ejecuta el recolector en un hilo separado
}

// Destructor privado
MPointerGC::~MPointerGC() {
    stop();  // Detener el hilo del recolector de basura
    if (gcThread.joinable()) {
        gcThread.join();  // Unir el hilo para una finalización ordenada
    }
    debug();
}

// Obtener la instancia única de MPointerGC (patrón Singleton)
MPointerGC* MPointerGC::getInstance() {
    if (!instance) {
        instance = new MPointerGC();
    }
    return instance;
}

// Registrar un puntero en la lista de MPointers
#include <iostream>

static int current_id = 0;  // Variable estática para generar IDs únicos

int MPointerGC::registerPointer(void* ptr) {
    std::lock_guard<std::mutex> lock(gc_mutex);
    pointers.add(ptr);
    std::cout << "Puntero registrado: " << ptr << " con ID " << current_id << std::endl;
    return current_id++;  // Devuelve el ID actual y lo incrementa
}


// Desregistrar un puntero cuando es destruido (o no se utiliza más)
void MPointerGC::unregisterPointer(void* ptr) {
    std::lock_guard<std::mutex> lock(gc_mutex);
    pointers.remove(ptr);
    std::cout << "Puntero desregistrado: " << ptr << std::endl;
}

// Función que ejecuta la recolección de basura periódicamente
void MPointerGC::runGCThread() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));  // Espera 10 segundos
        collectGarbage();
    }
}

// Recolección de basura manual
void MPointerGC::collectGarbage() {
    std::lock_guard<std::mutex> lock(gc_mutex);

    auto current = pointers.getHead();  // Obtener el primer nodo de la lista
    while (current) {
        if (current->data == nullptr) {
            // Si el puntero es nullptr, lo eliminamos de la lista
            pointers.remove(current->data);
            std::cout << "Puntero eliminado por GC: " << current->data << std::endl;
        }
        current = current->next;
    }
    std::cout << "Recolección de basura completada." << std::endl;
}


