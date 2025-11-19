//
// Created by jpfra on 19/11/25.
//

#ifndef PROYECTOFINALPOO_VISTA_H
#define PROYECTOFINALPOO_VISTA_H


#include <string>
#include <vector>
#include "Heroe.h"
#include "Habitacion.h"

class Vista {
public:
    // Muestra el título
    void mostrarBienvenida();

    // Muestra la información de la habitación actual
    void mostrarLugar(Habitacion* habitacion);

    // Muestra el estado del héroe (Vida, XP, Nivel)
    void mostrarHUD(Heroe* heroe);

    // Muestra el menú de acciones disponibles
    void mostrarMenuAcciones();

    // Muestra el menú de combate
    void mostrarMenuCombate();

    // Muestra el inventario enumerado para elegir
    void mostrarInventario(Heroe* heroe);

    // Con esto se imprimen los mensajes
    void mostrarMensaje(std::string mensaje);

    // Captura la entrada del usuario (int)
    int pedirOpcion();

    // Captura la entrada del usuario (string) para nombres
    std::string pedirString();
};

#endif //PROYECTOFINALPOO_VISTA_H