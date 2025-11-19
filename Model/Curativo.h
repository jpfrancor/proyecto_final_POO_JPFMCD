//
// Created by marti on 19/11/2025.
//

#ifndef PROYECTO_FINAL_POO_JPFMCD_CURATIVO_H
#define PROYECTO_FINAL_POO_JPFMCD_CURATIVO_H

#include "Item.h"
#include <iostream>
#include "Entidad.h"
#include "Heroe.h"

class Curativo : public Item {
private:
    int valorCuracion;

public:
    // Constructor
    // El destructor no se coloca por que se hereda de (entidad)
    Curativo(std::string nombre, std::string descripcion, int curacion);


    void usar(Entidad* objetivo) override;
};

#endif //PROYECTO_FINAL_POO_JPFMCD_CURATIVO_H