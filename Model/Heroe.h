//
// Created by marti on 14/11/2025.
//

#ifndef PROYECTO_FINAL_POO_JPFMCD_HEROE_H
#define PROYECTO_FINAL_POO_JPFMCD_HEROE_H
#include "Entidad.h"
#include <string>

class Heroe : public Entidad {
private:
    int nivel;
    int experiencia;


    const int xpLevelUp = 100;
    const int maxNivel = 3;

    // Metodos de utilidad
    void subirDeNivel();

public:
    // Constructor
    Heroe(std::string nombre, std::string descripcion, int pv, int atk, int def);

    // --- Métodos puros virtuales ---
    void movimiento1(Entidad& objetivo) override;

    // --- Sobrescritura de Comportamiento ---
    void morir(Entidad& atacante) override;

    // Metodo para ganar experiencia
    void ganarExperiencia(int expObtenida);

    // Metodo para logica de Curativo ---
    void curarse(int cantidad);

    // --- GETTERS ---
    int getNivel() const;
    int getExperiencia() const;
};

#endif // PROYECTO_FINAL_POO_JPFMCD_HEROE_H
#endif //PROYECTO_FINAL_POO_JPFMCD_HEROE_H