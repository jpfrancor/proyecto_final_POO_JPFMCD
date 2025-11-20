//
// Created by marti on 19/11/2025.
//

#include "Curativo.h"
#include "Heroe.h" // ¡Ahora incluimos Heroe.h!
#include <iostream>

// ... (Constructor)

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
}