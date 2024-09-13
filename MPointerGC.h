//
// Created by gabriel on 13/09/24.
//

#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include "MPointerList.h"
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

class MPointerGC {
private:
    MPointerList<void*> pointers;  // Lista de punteros conocidos
    static std::mutex gc_mutex;           // Mutex para evitar condiciones de carrera
    static MPointerGC* instance;   // Singleton para la gestión global

    MPointerGC();  // Constructor privado para Singleton
    ~MPointerGC(); // Destructor privado

    std::thread gcThread;
    bool isRunning= true;

public:
    static MPointerGC* getInstance();  // Obtener la instancia del Singleton
    int registerPointer(void* ptr);   // Registrar un nuevo puntero en la lista
    void unregisterPointer(void* ptr); // Desregistrar un puntero (cuando se destruye)
    void collectGarbage();             // Recolección manual de basura
    void stop ();
};


#endif
