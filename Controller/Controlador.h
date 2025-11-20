//
// Created by jpfra on 19/11/25.
//

#ifndef PROYECTOFINALPOO_CONTROLADOR_H
#define PROYECTOFINALPOO_CONTROLADOR_H


#include "Heroe.h"
#include "Habitacion.h"
#include "Vista.h"
#include "Guardia.h"
#include "Esqueleto.h"
#include "Jefe.h"
#include "Arma.h"
#include "Armadura.h"
#include "Curativo.h"
#include "LugarDeInteraccion.h"
#include <fstream> //  para persistencia
#include <vector>

class Controlador {
private:
    Heroe* heroe;
    Habitacion* habitacionActual;
    Habitacion* habitacionAnterior;
    Vista vista;
    bool juegoTerminado;
    std::vector<Habitacion*> mapaGlobal; // vector para guarda el mapa global para persistencia


    // Métodos internos
    void inicializarMapa();
    void procesarCombate();
    void procesarMovimiento();
    void procesarInteraccion();
    void procesarInventario();
    void guardarPartida();
    void cargarPartida();

public:
    Controlador();
    ~Controlador();
    void iniciar();
};


#endif //PROYECTOFINALPOO_CONTROLADOR_H