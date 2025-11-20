//
// Created by marti on 14/11/2025.
//

#include "Heroe.h"
#include <iostream>
#include <algorithm> // Para std::min/std::max

// ======================= CONSTRUCTOR =========================
Heroe::Heroe(std::string nombre, std::string descripcion, int pv, int atk, int def)
    : Entidad(std::move(nombre), std::move(descripcion), pv, atk, def),
      nivel(1),
      experiencia(0)
{
    // Inicializamos puntosDeVidaMax igual a la vida inicial si no se hizo en Entidad
    // this->puntosDeVidaMax = pv;
    std::cout << "¡El Caballero " << this->nombre << " ha comenzado su aventura!" << std::endl;
}

// ======================= SUBIDA DE NIVEL =========================

void Heroe::ganarExperiencia(int expObtenida) {
    if (nivel >= maxNivel) {
        std::cout << this->nombre << " ha alcanzado el nivel máximo (" << maxNivel << ")." << std::endl;
        return;
    }

    this->experiencia += expObtenida;
    std::cout << this->nombre << " ganó " << expObtenida << " EXP." << std::endl;

    // Corregido: 'expToLevelUp' cambiado a 'xpLevelUp' y 'maxNivelL' a 'maxNivel'
    while (this->experiencia >= xpLevelUp && nivel < maxNivel) {
        subirDeNivel();
    }
}

void Heroe::subirDeNivel() {
    // 1. Aumentar nivel y resetear experiencia
    this->nivel++;
    this->experiencia -= xpLevelUp; // Corregido nombre variable

    // 2. Mejorar stats
    this->puntosDeVidaMax += 20;    // Aumentamos el TOPE de vida
    this->puntosDeVida = this->puntosDeVidaMax; // Restauramos la vida al máximo al subir nivel
    this->ataque += 5;
    this->defensa += 3;

    std::cout << "¡" << this->nombre << " subió al Nivel " << this->nivel << "!" << std::endl;
    std::cout << "Stats mejorados: HP Max +" << 20 << ", ATK +" << 5 << ", DEF +" << 3 << "." << std::endl;
}

// ======================= MÉTODOS PUROS =========================

void Heroe::movimiento1(Entidad& objetivo) {
    std::cout << this->nombre << " realiza un Ataque Básico a " << objetivo.getNombre() << "." << std::endl;
    objetivo.recibirDanio(this->ataque);
}

// ======================= LÓGICA DE CURACION =========================

void Heroe::curarse(int cantidad) {
    int vidaAntes = this->puntosDeVida;

    this->puntosDeVida += cantidad;


    if (this->puntosDeVida > this->puntosDeVidaMax) {
        this->puntosDeVida = this->puntosDeVidaMax;
    }

    int recuperado = this->puntosDeVida - vidaAntes;

    std::cout << ">>> " << this->nombre << " recuperó " << recuperado << " HP.";
    std::cout << " (Vida actual: " << this->puntosDeVida << "/" << this->puntosDeVidaMax << ")" << std::endl;
}

// ======================= SOBRESCRITURA DE MORIR =========================

void Heroe::morir(Entidad& atacante) {
    std::cout << "\n==========================================" << std::endl;
    std::cout << this->nombre << " ha sido derrotado por " << atacante.getNombre() << "." << std::endl;
    std::cout << "G A M E   O V E R" << std::endl;
    std::cout << "==========================================" << std::endl;
}

// ======================= GETTERS =========================

int Heroe::getNivel() const { return nivel; }
int Heroe::getExperiencia() const { return experiencia; }