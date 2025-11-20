//
// Created by marti on 19/11/2025.
//

#include "Armadura.h"
#include "Heroe.h"
#include <iostream>

// El constructor debe coincidir
Armadura::Armadura(std::string nombre, std::string descripcion, int defensa)
    : Item(nombre, descripcion, false) { // Pasamos la descripcion al padre
    this->defensaExtra = defensa;
}

void Armadura::usar(Entidad* usuario) {
    Heroe* heroe = dynamic_cast<Heroe*>(usuario);
    if (heroe) {
        std::cout << heroe->getNombre() << " se equipo " << this->nombre << std::endl;
        heroe->modificarEstadisticas(0, 0, this->defensaExtra);
    }
}