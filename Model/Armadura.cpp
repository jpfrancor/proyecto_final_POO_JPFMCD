//
// Created by marti on 19/11/2025.
//

#include "Armadura.h"
#include "Heroe.h"
#include <iostream>

//consructor
Armadura::Armadura(std::string nombre, std::string descripcion, int defensa)
    : Item(nombre, descripcion, false) {
    this->defensaExtra = defensa;

    // Probabilidad
    if (defensa == 3) this->probabilidadDrop = 60;     // Pechera
    else if (defensa == 7) this->probabilidadDrop = 15; // Armadura del heroe
}

void Armadura::usar(Entidad* usuario) {
    Heroe* heroe = dynamic_cast<Heroe*>(usuario);
    if (heroe) {
        std::cout << heroe->getNombre() << " se equipo " << this->nombre << std::endl;
        heroe->modificarEstadisticas(0, 0, this->defensaExtra);
    }
}