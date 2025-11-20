#include <iostream>
// En main.cpp (o donde inicialices el Controlador)
#include <cstdlib> // Para srand()
#include <ctime>   // Para time()
#include "Controlador.h"

int main() {
    // Semilla para aleatoriedad (para el Jefe)
    srand(time(0));

    Controlador controlador;
    controlador.iniciar();

    return 0;
}