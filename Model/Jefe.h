//
// Created by jpfra on 19/11/25.
//

#ifndef PROYECTOFINALPOO_JEFE_H
#define PROYECTOFINALPOO_JEFE_H

#include "Entidad.h" // Hereda de la clase base
#include <string>



class Jefe : public Entidad {
public:
    // Constructor
    Jefe(std::string nombre, std::string descripcion, int hp, int atk, int def);

    // Sobrescritura obligatoria con el objetivo (Heroe&)
    void movimiento1(Entidad& objetivo) override;
};

#endif //PROYECTOFINALPOO_JEFE_H