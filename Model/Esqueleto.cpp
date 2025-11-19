//
// Created by marti on 17/11/2025.
//

#include "Esqueleto.h"
#include <iostream>
#include <utility>
#include "Curativo.h"
#include "Arma.h"
#include "Armadura.h"

// ======================= CONSTRUCTOR =========================

Esqueleto::Esqueleto(std::string nombre, std::string descripcion, int pv, int atk, int def)
    : Entidad(std::move(nombre), std::move(descripcion), pv, atk, def)
{
    std::cout << "Un Esqueleto se levanta: " << this->nombre << "." << std::endl;


    // Items básicos y curativos
    this->inventario.push_back(new Curativo("Hierbas", 5));
    this->inventario.push_back(new Curativo("Vendas", 10));


    this->inventario.push_back(new Arma("Daga Oxidada", 5));
    this->inventario.push_back(new Armadura("Casco Roto", 2));
}

// ======================= MÉTODOS PÚROS =========================

void Esqueleto::movimiento1(Heroe& objetivo) {
    std::cout << this->nombre << " ataca con su Hueso Roto." << std::endl;
    objetivo.recibirDanio(this->ataque);
}
}