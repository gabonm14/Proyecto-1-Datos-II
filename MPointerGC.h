//
// Created by gabriel on 13/09/24.
//

#ifndef MPOINTERGC_H
#define MPOINTERGC_H
#include "MPointerList.h"
#include <mutex>


class MPointerGC {
private:
    MPointerList<void*> pointers;  // Lista de punteros conocidos
    std::mutex gc_mutex;  // Para evitar condiciones de carrera

    MPointerGC();  // Constructor privado para singleton
    static MPointerGC* instance;

public:
    static MPointerGC* getInstance();  // Obtener instancia única
    void registerPointer(void* ptr);  // Registrar un MPointer
    void unregisterPointer(void* ptr);  // Desregistrar un MPointer
    void collectGarbage();  // Realizar la recolección de basura
};



#endif //MPointerGC
