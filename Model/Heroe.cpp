//
// Created by marti on 14/11/2025.
//

#include "Heroe.h"
#include <iostream>
#include <algorithm> // Para std::min/std::max

// ======================= CONSTRUCTOR =========================

// Llama al constructor de la clase base (Entidad) y luego inicializa los atributos propios.
Heroe::Heroe(std::string nombre, std::string descripcion, int pv, int atk, int def)
    // 1. Inicialización de la clase base (Entidad)
    : Entidad(std::move(nombre), std::move(descripcion), pv, atk, def),
      // 2. Inicialización de atributos propios (Heroe comienza en Nivel 1, EXP 0)
      nivel(1),
      experiencia(0)
{
    std::cout << "¡El Caballero " << this->nombre << " ha comenzado su aventura!" << std::endl;
}

// ======================= SUBIDA DE NIVEL =========================

void Heroe::ganarExperiencia(int expObtenida) {
    if (nivel >= maxNivelL) {
        // No se gana más experiencia si se alcanzó el nivel máximo.
        std::cout << this->nombre << " ha alcanzado el nivel máximo (" << maxNivel << ")." << std::endl;
        return;
    }

    this->experiencia += expObtenida;
    std::cout << this->nombre << " ganó " << expObtenida << " EXP." << std::endl;

    while (this->experiencia >= expToLevelUp && nivel < maxNivelL) {
        subirDeNivel();
    }
}

void Heroe::subirDeNivel() {
    // 1. Aumentar nivel y resetear experiencia
    this->nivel++;
    this->experiencia -= expToLevelUp;

    // 2. Mejorar stats
    this->puntosDeVida += 20; // Atributos protected de Entidad son accesibles
    this->ataque += 5;
    this->defensa += 3;

    std::cout << "¡" << this->nombre << " subió al Nivel " << this->nivel << "!" << std::endl;
    std::cout << "Stats mejorados: HP +" << 20 << ", ATK +" << 5 << ", DEF +" << 3 << "." << std::endl;
}

// ======================= MÉTODOS PÚROS =========================

void Heroe::movimiento1() {
    std::cout << this->nombre << " realiza un Ataque Básico." << std::endl;

}

// ======================= SOBRESCRITURA DE MORIR =========================

// El Heroe sobrescribe el metodo morir para la lógica de Game Over.
void Heroe::morir(Entidad& atacante) {
    std::cout << "\n==========================================" << std::endl;
    std::cout << this->nombre << " ha sido derrotado por " << atacante.getNombre() << "." << std::endl;
    std::cout << "G A M E   O V E R" << std::endl;
    std::cout << "==========================================" << std::endl;
    // Lógica para salir del juego o volver al menú principal
}

// ======================= GETTERS =========================

int Heroe::getNivel() const {
    return nivel;
}

int Heroe::getExperiencia() const {
    return experiencia;
}