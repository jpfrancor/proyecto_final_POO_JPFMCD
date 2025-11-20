//
// Created by jpfra on 19/11/25.
//

#ifndef PROYECTOFINALPOO_CONTROLADOR_H
#define PROYECTOFINALPOO_CONTROLADOR_H


#include "Heroe.h"
#include "Habitacion.h"
#include "Vista.h"
// Incluye tus enemigos y objetos
#include "Guardia.h"
#include "Esqueleto.h"
#include "Jefe.h"
#include "Arma.h"
#include "Armadura.h"
#include "Curativo.h"
#include "LugarDeInteraccion.h"

class Controlador {
private:
    Heroe* heroe;
    Habitacion* habitacionActual;
    Vista vista;
    bool juegoTerminado;

    // Métodos internos
    void inicializarMapa();
    void procesarCombate();
    void procesarMovimiento();
    void procesarInteraccion();
    void procesarInventario();
    void guardarPartida(); // Implementación básica

public:
    Controlador();
    ~Controlador();
    void iniciar();
};


#endif //PROYECTOFINALPOO_CONTROLADOR_H