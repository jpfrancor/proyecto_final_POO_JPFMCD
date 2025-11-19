//
// Created by marti on 17/11/2025.
//

#ifndef PROYECTO_FINAL_POO_JPFMCD_ESQUELETO_H
#define PROYECTO_FINAL_POO_JPFMCD_ESQUELETO_H

#include "Entidad.h" // Heredamos de Entidad
#include <string>

class Esqueleto : public Entidad {
public:
    // Constructor
    Esqueleto(std::string nombre, std::string descripcion, int pv, int atk, int def);

    // Destructor
    ~Esqueleto() override = default;

    // Implementación de la accion específica del Esqueleto.
    void movimiento1() override;
};

#endif //PROYECTO_FINAL_POO_JPFMCD_ESQUELETO_H