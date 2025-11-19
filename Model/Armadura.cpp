//
// Created by marti on 19/11/2025.
//

#include "Armadura.h"
#include "Entidad.h"
#include <iostream>

// Constructor

Armadura::Armadura(std::string nombre, int defensaExtra)
    : Item(nombre, descripcion, true),
      defensaAdicional(defensaExtra)
{
}

void Armadura::usar(Entidad* objetivo) {
    if (objetivo != nullptr) {

        std::cout << objetivo->getNombre() << " se ha equipado " << this->getNombre() << "." << std::endl;

        // === LÓGICA PRINCIPAL ===


        objetivo->modificarEstadisticas(0, 0, this->defensaAdicional);


        std::cout << "Defensa aumentada en +" << this->defensaAdicional
                  << ". (Defensa Total: " << objetivo->getDefensa() << ")" << std::endl;
    }
}

int Armadura::getDefensaAdicional() const {
    return defensaAdicional;
}