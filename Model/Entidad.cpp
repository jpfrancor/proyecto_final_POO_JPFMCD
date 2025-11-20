//
// Created by jpfra on 11/11/25.
//

#include <iostream>
#include "Entidad.h"
#include <cstdlib>  //para random

#include "Heroe.h"
#include "Item.h"
#include "Arma.h"
#include "Armadura.h"
#include "Curativo.h"

// Constructor
Entidad::Entidad(std::string nombre, std::string descripcion, int hp, int atk, int def)
    : nombre(nombre),
      descripcion(descripcion),
      puntosDeVida(hp),
      puntosDeVidaMax(hp),
      ataque(atk),
      defensa(def) {//Vacio para que no imprima nada
}

// Implementación del metodo morir.
// Usa una referencia (&) al Heroe que derrotó a esta entidad (enemigo)
void Entidad::morir(Heroe& heroe) {
    std::cout << "\n" << this->nombre << " ha sido derrotado." << std::endl;

    bool soltoAlgo = false;

    for (Item* item : inventario) {
        // Tiramos el dado (0 a 100)
        int suerte = std::rand() % 100;

        // Usamos la probabilidad propia de CADA item
        // Si el dado saca MENOS que la probabilidad, el item cae.
        // Ejemplo: Hierbas (90%), si sacas 50, cae. Excalibur (10%), si sacas 50, NO cae.
        if (suerte <= item->getProbabilidadDrop()) {
            std::cout << ">>> " << this->nombre << " ha dejado caer: " << item->getNombre() << "!" << std::endl;
            heroe.agregarItemInventario(item);
            soltoAlgo = true;
        } else {
            // El item se pierde
            delete item;
        }
    }

    inventario.clear();

    if (!soltoAlgo) {
        std::cout << this->nombre << " no dejo caer nada util." << std::endl;
    }
}

// Implementación del mtodo para añadir objetos al inventario
void Entidad::agregarItemInventario(Item* item) {
    inventario.push_back(item);
    std::cout << "Se agregó " << item->getNombre() << " al inventario de " << this->nombre << "." << std::endl;
}

void Entidad::recibirDanio(int cantidad) {
    // 1. Calculamos el daño real restando la defensa
    int danioReal = cantidad - this->defensa;
    if (danioReal < 0) {
        danioReal = 0;
    }
    this->puntosDeVida -= danioReal;

    if (this->puntosDeVida < 0) {
        this->puntosDeVida = 0;
    }
    std::cout << this->nombre << " recibio " << danioReal
              << " puntos de danio (Defensa bloqueo: " << this->defensa << ")." << std::endl;
    std::cout << "Vida restante de " << this->nombre << ": " << this->puntosDeVida << std::endl;
}

void Entidad::modificarEstadisticas(int vida, int ataqueExtra, int defensaExtra) {
    this->puntosDeVida += vida;
    if(this->puntosDeVida > this->puntosDeVidaMax) this->puntosDeVida = this->puntosDeVidaMax;

    this->ataque += ataqueExtra;
    this->defensa += defensaExtra;
}

//Con esto sacamos un item del inventario
void Entidad::eliminarItem(int indice) {
    if (indice >= 0 && indice < inventario.size()) {
        // Borra el elemento en la posición indice
        inventario.erase(inventario.begin() + indice);
    }
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
int Entidad::getPuntosDeVidaMax() const
{ return puntosDeVidaMax;
}

const std::vector<Item*>& Entidad::getInventario() const {
    return inventario;
}
