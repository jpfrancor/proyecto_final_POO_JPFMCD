//
// Created by jpfra on 19/11/25.
//

#include "Jefe.h"
#include "Heroe.h" // Incluimos Heroe para poder usar Heroe&
#include <iostream>
#include <cstdlib> // Necesario para rand()

// ======================= CONSTRUCTOR =========================

Jefe::Jefe(std::string nombre, std::string descripcion, int hp, int atk, int def)
    // Llama al constructor de la clase base, inicializando los atributos
    : Entidad(nombre, descripcion, hp, atk, def)
{
    std::cout << "El Jefe Final " << this->nombre << " ha sido invocado." << std::endl;
}

// ======================= MÉTODOS DE ATAQUE SOBRESCRITOS =========================

void Jefe::movimiento1(Entidad& objetivo) {
    // Usamos rand() para simular la elección entre 3 ataques diferentes del Jefe.
    int ataqueElegido = rand() % 3; // Genera 0, 1 o 2

    switch (ataqueElegido) {
        case 0:
            std::cout << this->nombre << " usa [Ataque Basico] contra " << objetivo.getNombre() << "!" << std::endl;
            objetivo.recibirDanio(this->ataque);
            break;
        case 1:
            std::cout << this->nombre << " usa [Prision de Sombras], reduciendo la defensa de " << objetivo.getNombre() << "." << std::endl;
            objetivo.setDefensa(objetivo.getDefensa() - 2);
            break;
        case 2:
            std::cout << this->nombre << " desata [Juicio del Calabozo]! Un ataque devastador sobre " << objetivo.getNombre() << "." << std::endl;
            objetivo.recibirDanio(this->ataque * 2);
            break;
    }
}