//
// Created by marti on 16/11/2025.
//

#ifndef PROYECTO_FINAL_POO_JPFMCD_GUARDIA_H
#define PROYECTO_FINAL_POO_JPFMCD_GUARDIA_H

#include "Entidad.h"
#include <string>

class Guardia : public Entidad {
public:
    // Constructor. Define los stats base de un Guardia.
    Guardia(std::string nombre, std::string descripcion, int pv, int atk, int def);

    // Destructor se hereda el virtual de Entidad
    ~Guardia() override = default;

    // --- Métodos puros virtuales---
    // Implementación de la accion específica del Guardia.
    void movimiento1(Heroe& objetivo) override;


    // NOTA: No necesitamos sobrescribir morir(), usará la lógica de despojo de Entidad.
};


#endif //PROYECTO_FINAL_POO_JPFMCD_GUARDIA_H