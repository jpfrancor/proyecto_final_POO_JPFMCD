//
// Created by marti on 14/11/2025.
//

#ifndef PROYECTO_FINAL_POO_JPFMCD_HEROE_H
#define PROYECTO_FINAL_POO_JPFMCD_HEROE_H
#include "Entidad.h"
#include <string>

class Arma;
class Armadura;

class Heroe : public Entidad {
private:
    int nivel;
    int experiencia;


    const int xpLevelUp = 125;
    const int maxNivel = 4;

    Arma* armaEquipada = nullptr;
    Armadura* armaduraEquipada = nullptr;

    // Metodos de utilidad
    void subirDeNivel();

public:
    // Constructor
    Heroe(std::string nombre, std::string descripcion, int pv, int atk, int def);

    // --- Métodos puros virtuales ---
    void movimiento1(Entidad& objetivo) override;

    // --- Sobrescritura de Comportamiento ---
    void morir(Entidad& atacante);

    // Metodo para ganar experiencia
    void ganarExperiencia(int expObtenida);

    // Metodo para logica de Curativo ---
    void curarse(int cantidad);

    void equiparArma(Arma* arma);
    void equiparArmadura(Armadura* armadura);

    // --- GETTERS ---
    int getNivel() const;
    int getExperiencia() const;

    // --- SETTERS ---
    void setNivel(int valor) { nivel = valor; }
    void setExperiencia(int valor) { experiencia = valor; }
};

#endif // PROYECTO_FINAL_POO_JPFMCD_HEROE_H