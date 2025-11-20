//
// Created by marti on 16/11/2025.
//

#include "Guardia.h"
#include <iostream>
#include "Curativo.h"
#include "Arma.h"
#include "Armadura.h"

// ======================= CONSTRUCTOR =========================

Guardia::Guardia(std::string nombre, std::string descripcion, int pv, int atk, int def)
    : Entidad(std::move(nombre), std::move(descripcion), pv, atk, def)
{
    //No le ponemos comentario de invocacion

    // 2. Inventario del Guardia

    // Items base
    this->inventario.push_back(new Curativo("Vendas", "Curacion media. +10HP.", 10));
    this->inventario.push_back(new Curativo("Pocion de Curacion", "Curacion alta, para las mayores batallas. +25HP.", 25));


    this->inventario.push_back(new Arma("Espada del Heroe", "Espada formidable disennada para los mayores guerreros. +15ATK.", 15));
    this->inventario.push_back(new Armadura("Armadura del Heroe", "Armadura formidable disennada para los mayores guerreros. +7DEF.", 7));
}

// ======================= MÉTODOS PÚROS  =========================

void Guardia::movimiento1(Entidad& objetivo) {
    std::cout << this->nombre << " realiza un Ataque con Espada Estándar." << std::endl;
    objetivo.recibirDanio(this->ataque);
}