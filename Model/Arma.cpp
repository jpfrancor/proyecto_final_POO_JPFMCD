//
// Created by jpfra on 19/11/25.
//

#include "Arma.h"
#include "Heroe.h" // Necesario para el dynamic_cast y métodos de Heroe
#include <iostream>

// Constructor
// Se usa false a Item porque las armas no son consumbibles
Arma::Arma(std::string nombre, std::string descripcion, int danio)
    : Item(nombre, descripcion, false) {
    this->puntosDeAtaque = danio;

    // Si el arma hace poco daño, es común. Si es fuerte, es rara.
    if (danio <= 5) this->probabilidadDrop = 50;      // Para lanza
    else if (danio >= 15) this->probabilidadDrop = 15; // Para espada del heroe
}
void Arma::usar(Entidad* usuario) {
    // Intentamos convertir al usuario en Héroe
    Heroe* heroe = dynamic_cast<Heroe*>(usuario);

    if (heroe) {
        // Mensaje narrativo
        std::cout << heroe->getNombre() << " se ha equipado " << this->nombre << "." << std::endl;
        heroe->modificarEstadisticas(0, this->puntosDeAtaque, 0);

        std::cout << "El ataque ha subido en " << this->puntosDeAtaque << " puntos!" << std::endl;
    } else {
        std::cout << "Solo el heroe puede equipar armas." << std::endl;
    }
}