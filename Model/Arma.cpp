//
// Created by jpfra on 19/11/25.
//

#include "Arma.h"
#include "Heroe.h" // Necesario para el dynamic_cast y métodos de Heroe
#include <iostream>

// Constructor
// Se usa "false" a Item porque las armas NO se consumen (no desaparecen al usarlas)
// Agregamos una descripcion generica
Arma::Arma(std::string nombre, std::string descripcion, int danio)
    : Item(nombre, "Arma de combate cuerpo a cuerpo", false), puntosDeAtaque(danio) {
}

void Arma::usar(Entidad* usuario) {
    // Intentamos convertir al usuario en Héroe
    Heroe* heroe = dynamic_cast<Heroe*>(usuario);

    if (heroe) {
        // Mensaje narrativo
        std::cout << heroe->getNombre() << " se ha equipado " << this->nombre << "." << std::endl;

        // === IMPORTANTE ===
        // Necesitamos acceder al ataque. Como 'ataque' es protected en Entidad,
        // tenemos dos opciones. La ideal es usar un setter.
        // Agrega este metodo en Entidad.h/.cpp si no existe, o usa esta lógica:

        // Opción A (Si agregas el metodo 'aumentarAtaque' en Entidad/Heroe):
        // heroe->aumentarAtaque(this->puntosDeAtaque);

        // Opción B (Por ahora, para que funcione rápido, vamos a modificar el ataque
        // usando un metodo que DEBES crear en Entidad, ver paso 3 abajo):
        heroe->modificarEstadisticas(0, this->puntosDeAtaque, 0);

        std::cout << "El ataque ha subido en " << this->puntosDeAtaque << " puntos!" << std::endl;
    } else {
        std::cout << "Solo el heroe puede equipar armas." << std::endl;
    }
}