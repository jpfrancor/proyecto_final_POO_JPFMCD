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
    const int xpLevelUp = 100; // la lógica de subida de nivel
    const int maxNivel = 3;         // Nivel máximo según el guion

    // Métodos de utilidad
    void subirDeNivel(); // Implementación del metodo que mejora los stats

public:
    // Constructor. Inicializa atributos propios y llama al constructor de la clase base.
    Heroe(std::string nombre, std::string descripcion, int pv, int atk, int def);

    // --- Métodos puros virtuales ---
    // Implementación de la accion del héroe que el usuario puede elegir.
    void movimiento1() override;

    // --- Sobrescritura de Comportamiento ---

    // El metodo morir es sobrescrito para la lógica de "Game Over", no para el despojo.
    // Usamos 'Entidad&' para mayor abstracción, aunque aquí solo necesitamos el 'override'.
    void morir(Entidad& atacante) override;

    // Metodo para ganar experiencia (llamado al derrotar un enemigo)
    void ganarExperiencia(int expObtenida);

    // --- GETTERS ---
    int getNivel() const;
    int getExperiencia() const;
};


#endif //PROYECTO_FINAL_POO_JPFMCD_HEROE_H