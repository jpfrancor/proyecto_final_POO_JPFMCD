//
// Created by jpfra on 19/11/25.
//

#include "Jefe.h"
#include "Heroe.h" // Incluimos Heroe para poder usar Heroe&
#include <iostream>
#include <cstdlib> // Necesario para rand()
#include <utility> // Para std::move

// ======================= CONSTRUCTOR =========================

Jefe::Jefe(std::string nombre, std::string descripcion, int hp, int atk, int def)
    // Llama al constructor de la clase base, inicializando los atributos
    : Entidad(std::move(nombre), std::move(descripcion), hp, atk, def)
{
    std::cout << "El Jefe Final " << this->nombre << " ha sido invocado." << std::endl;
}

// ======================= MÉTODOS DE ATAQUE SOBRESCRITOS =========================

void Jefe::movimiento1(Heroe& objetivo) {
    // Usamos rand() para simular la elección entre 3 ataques diferentes del Jefe.
    int ataqueElegido = rand() % 3; // Genera 0, 1 o 2

    switch (ataqueElegido) {
        case 0:
            std::cout << this->nombre << " usa [Ataque Básico] contra " << objetivo.getNombre() << "!" << std::endl;
            // Lógica de daño: objetivo.recibirDanio(...)
            break;
        case 1:
            std::cout << this->nombre << " usa [Prisión de Sombras], reduciendo la defensa de " << objetivo.getNombre() << "." << std::endl;
            // Lógica del Ataque 2: Aplicar efecto o daño
            break;
        case 2:
            std::cout << this->nombre << " desata [Juicio del Calabozo]! Un ataque devastador sobre " << objetivo.getNombre() << "." << std::endl;
            // Lógica del Ataque 3: Daño muy alto
            break;
    }
}