//
// Created by jpfra on 11/11/25.
//

#include <iostream>
#include "Entidad.h" // Incluimos el archivo de cabecera que acabamos de definir
#include <algorithm> // Útil para lógica futura

// NOTA: Para que compile este archivo, necesitas incluir la clase Heroe.h
// y Item.h. Asumimos que existen en la carpeta /Modelo.
//#include "Heroe.h"
//#include "Item.h"

// Constructor
Entidad::Entidad(std::string nombre, std::string descripcion, int hp, int atk, int def)
    : nombre(nombre), // Se usa std::move para optimización
      descripcion(descripcion),
      puntosDeVida(hp),
      ataque(atk),
      defensa(def) {
    std::cout << "Enhorabuena! " << this->nombre << " ha aparecido." << std::endl;
}

// Implementación del método morir.
// Usa una referencia (&) al Heroe que derrotó a esta entidad (enemigo)
void Entidad::morir(Heroe& heroe) { // Esta es la lógica central para el despojo (loot) de enemigos
    std::cout << this->nombre << " ha sido derrotado." << std::endl; // 1. Lógica de drops: Itera sobre el inventario del enemigo.

    for (Item* item : inventario) {
        std::cout << this->nombre << " ha dejado caer: " << item->getNombre() << std::endl;
        heroe.agregarItemInventario(item); //Transferencia del loot al inventario del Heroe
    }
    inventario.clear(); //Se limpia el inventario para no causar errores.
    // Es importante NOTA: El puntero al Item se mueve al Heroe, no se borra.
}

// Implementación del método para añadir objetos al inventario
void Entidad::agregarItemInventario(Item* item) {
    inventario.push_back(item);
    std::cout << "Se agregó " << item->getNombre() << " al inventario de " << this->nombre << "." << std::endl;
}

// ======================= GETTERS =========================

std::string Entidad::getNombre() const {
    return nombre;
}

std::string Entidad::getDescripcion() const {
    return descripcion;
}

int Entidad::getPuntosDeVida() const {
    return puntosDeVida;
}

int Entidad::getAtaque() const {
    return ataque;
}

int Entidad::getDefensa() const {
    return defensa;
}