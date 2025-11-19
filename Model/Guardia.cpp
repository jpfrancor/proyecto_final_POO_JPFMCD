//
// Created by marti on 16/11/2025.
//

#include "Guardia.h"
#include <iostream>
#include <utility>
#include "Curativo.h"
#include "Arma.h"

// ======================= CONSTRUCTOR =========================

Guardia::Guardia(std::string nombre, std::string descripcion, int pv, int atk, int def)
    : Entidad(std::move(nombre), std::move(descripcion), pv, atk, def)
{
    std::cout << "Un Guardia hostil ha aparecido: " << this->nombre << "." << std::endl;

    // 2. Inventario del Guardia

    // Items base
    this->inventario.push_back(new Curativo("Hierbas", 5));
    this->inventario.push_back(new Curativo("Vendas", 10));
    this->inventario.push_back(new Curativo("Pocion de Curacion", 25));


    this->inventario.push_back(new Arma("Espada del Heroe", "Espada formidable disennada para los mayores guerreros.", 15));
    this->inventario.push_back(new Armadura("Pechera del Heroe", "Pechera formidable disennada para los mayores guerreros.", 10));
}

// ======================= MÉTODOS PÚROS  =========================

void Guardia::movimiento1(Entidad& objetivo) {
    std::cout << this->nombre << " realiza un Ataque con Espada Estándar." << std::endl;
    objetivo.recibirDanio(this->ataque);
}