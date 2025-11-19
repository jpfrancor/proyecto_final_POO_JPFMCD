//
// Created by marti on 19/11/2025.
//

#ifndef PROYECTO_FINAL_POO_JPFMCD_CURATIVO_H
#define PROYECTO_FINAL_POO_JPFMCD_CURATIVO_H

#include "Item.h"
#include <iostream>

class Entidad;
class Heroe;

class Curativo : public Item {
private:
    int valorCuracion;

public:
    // Constructor
    // El destructor no se coloca por que se hereda de (entidad)
    Curativo(std::string nombre, int curacion);


    void usar(Entidad& usuario) override;
};

#endif //PROYECTO_FINAL_POO_JPFMCD_CURATIVO_H