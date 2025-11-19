//
// Created by jpfra on 19/11/25.
//

#ifndef PROYECTOFINALPOO_JEFE_H
#define PROYECTOFINALPOO_JEFE_H

#include "Entidad.h" // Hereda de la clase base
#include <string>

class Heroe; // Declaración adelantada para usar Heroe& en los métodos

class Jefe : public Entidad {
public:
    // Constructor
    Jefe(std::string nombre, std::string descripcion, int hp, int atk, int def);

    // Sobrescritura obligatoria con el objetivo (Heroe&)
    void movimiento1(Heroe& objetivo) override;

    // Aquí irían otros métodos específicos si fueran necesarios...

    // NOTA: Si el Jefe Final tiene una lógica de muerte única, el destructor
    // o el morir() deberían ser sobrescritos.
};

#endif //PROYECTOFINALPOO_JEFE_H