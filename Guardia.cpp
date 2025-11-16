//
// Created by marti on 16/11/2025.
//

#include "Guardia.h"
#include <iostream>
#include <utility>
// Asumimos que estas clases ya existen o serán creadas (heredan de Item)
#include "Curativo.h"
#include "Arma.h"

// ======================= CONSTRUCTOR =========================

Guardia::Guardia(std::string nombre, std::string descripcion, int pv, int atk, int def)
    // 1. Inicialización de la clase base (Entidad)
    : Entidad(std::move(nombre), std::move(descripcion), pv, atk, def)
{
    std::cout << "Un Guardia hostil ha aparecido: " << this->nombre << "." << std::endl;

    // 2. Inventario del Guardia

    // Items base (Curativos)
    this->inventario.push_back(new Curativo("Hierbas", 5));
    this->inventario.push_back(new Curativo("Vendas", 10));
    this->inventario.push_back(new Curativo("Pocion de Curacion", 25)); // Específico del Guardia

    // Armas/Armaduras avanzadas (Se asume la existencia de la clase Arma y Armadura)
    // NOTA: En una implementación real, se usaría lógica de probabilidad (rand()).
    this->inventario.push_back(new Arma("Espada Larga", 15));
    // this->inventario.push_back(new Armadura("Pechera de Guardia", 10));
}

// ======================= MÉTODOS PÚROS  =========================

void Guardia::movimiento1() {
    std::cout << this->nombre << " realiza un Ataque con Espada Estándar." << std::endl;
    // Lógica para atacar
}

}