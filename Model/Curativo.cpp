//
// Created by marti on 19/11/2025.
//

#include "Curativo.h"
#include "Heroe.h" // ¡Ahora incluimos Heroe.h!
#include <iostream>

Curativo::Curativo(std::string nombre, std::string descripcion, int curacion)
    : Item(nombre, descripcion, true) { // true porque es consumible
    this->valorCuracion = curacion;

    if (curacion <= 5) {
        // Hierbas (Debiles) -> Comun (70% de caer)
        this->probabilidadDrop = 70;
    }
    else if (curacion <= 15) {
        // Vendas (Medias) -> Raro (30% de caer)
        this->probabilidadDrop = 30;
    }
    else {
        // Pocima de Curacion (Fuerte) -> Epico (10% de caer)
        this->probabilidadDrop = 10;
    }
}


void Curativo::usar(Entidad* objetivo) {
    // 1. Intentar convertir la referencia de Entidad a Heroe
    Heroe* heroe = dynamic_cast<Heroe*>(objetivo);

    // 2. Comprobar que la conversión fue exitosa
    if (heroe) {
        std::cout << heroe->getNombre() << " ha usado " << this->getNombre()
                  << " y ha recuperado " << this->valorCuracion << " HP." << std::endl;

        // **Llamada al metodo específico del Héroe**
        heroe->curarse(this->valorCuracion);
    } else {
        std::cout << "ERROR: Solo el Heroe puede usar items curativos." << std::endl;
    }
}
