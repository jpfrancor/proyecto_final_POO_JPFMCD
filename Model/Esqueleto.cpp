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
    //Vacio por ahora para que no salga mensaje de invocacion


    // Items básicos y curativos
    this->inventario.push_back(new Curativo("Hierbas", "Curacion baja. +10HP.", 10));
    this->inventario.push_back(new Curativo("Vendas", "Curacion media. +25HP.", 25));


    this->inventario.push_back(new Arma("Lanza", "Una lanza de caballeria, ideal para atravesar enemigos que se acercan demasiado. +7ATK.", 7));
    this->inventario.push_back(new Armadura("Pechera", "Ofrece mas resistencia, enhorabuena. +7DEF.", 7));
}

// ======================= MÉTODOS PÚROS =========================

void Esqueleto::movimiento1(Entidad& objetivo) {
    std::cout << this->nombre << " ataca con su Hueso Roto." << std::endl;
    objetivo.recibirDanio(this->ataque);
}
