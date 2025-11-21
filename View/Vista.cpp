//
// Created by jpfra on 19/11/25.
//

#include "Vista.h"
#include <iostream>
#include <windows.h> // SIN esto se daña el arte ascii

using namespace std;

void Vista::mostrarBienvenida() {
    // Con esto hacemos que la consola lea UTF-8 y el arte ascii funcione
    SetConsoleOutputCP(65001);

    cout << R"(



     ##### /
  ######  /
 /#   /  /
/    /  /
    /  /
   ## ##              /###     /###   ##   ####    ###  /###     /###             /##  ###  /###
   ## ##             / ###  / / ###  / ##    ###  / ###/ #### / / ###  /         / ###  ###/ #### /
   ## ##            /   ###/ /   ###/  ##     ###/   ##   ###/ /   ###/         /   ###  ##   ###/
   ## ##           ##    ## ##         ##      ##    ##       ##    ##         ##    ### ##    ##
   ## ##           ##    ## ##         ##      ##    ##       ##    ##         ########  ##    ##
   #  ##           ##    ## ##         ##      ##    ##       ##    ##         #######   ##    ##
      /            ##    ## ##         ##      ##    ##       ##    ##         ##        ##    ##
  /##/           / ##    ## ###     /  ##      /#    ##       ##    /#         ####    / ##    ##
 /  ############/   ######   ######/    ######/ ##   ###       ####/ ##         ######/  ###   ###
/     #########      ####     #####      #####   ##   ###       ###   ##         #####    ###   ###
#
 ##


###                         ##### ##                             /##                               ##
 ###                     ######  /###                          #/ ###                               ##
  ##                    /#   /  /  ###                        ##   ###                              ##
  ##                   /    /  /    ###                       ##                                    ##
  ##                       /  /      ##                       ##                                    ##
  ##      /###            ## ##      ## ###  /###     /###    ###### ##   ####    ###  /###     ### ##    /###
  ##     / ###  /         ## ##      ##  ###/ #### / / ###  / #####   ##    ###  / ###/ #### / ######### / ###  /
  ##    /   ###/        /### ##      /    ##   ###/ /   ###/  ##      ##     ###/   ##   ###/ ##   #### /   ###/
  ##   ##    ##        / ### ##     /     ##       ##    ##   ##      ##      ##    ##    ##  ##    ## ##    ##
  ##   ##    ##           ## ######/      ##       ##    ##   ##      ##      ##    ##    ##  ##    ## ##    ##
  ##   ##    ##           ## ######       ##       ##    ##   ##      ##      ##    ##    ##  ##    ## ##    ##
  ##   ##    ##           ## ##           ##       ##    ##   ##      ##      ##    ##    ##  ##    ## ##    ##
  ##   ##    ##           ## ##           ##       ##    ##   ##      ##      /#    ##    ##  ##    /# ##    ##
  ### / ######            ## ##           ###       ######    ##       ######/ ##   ###   ###  ####/    ######
   ##/   ####        ##   ## ##            ###       ####      ##       #####   ##   ###   ###  ###      ####
                    ###   #  /
                     ###    /
                      #####/
                        ###
    )" << endl; //El R de arriba significa raw string y hace que se lea el arte sin modificaciones raras

    cout << "==================================================================" << endl;
    cout << "              BIENVENIDO A LA OSCURIDAD, AVENTURERO" << endl;
    cout << "==================================================================" << endl;
}

void Vista::mostrarLugar(Habitacion* habitacion) {
    cout << "\n--- " << habitacion->getNombre() << " ---" << endl;
    cout << habitacion->getDescripcion() << endl;

    // Mostrar salidas
    cout << "Movimientos posibles: ";
    for (auto const& [direccion, puntero] : habitacion->getSalidas()) {
        cout << "[" << direccion << "] ";
    }
    cout << endl;

    // Mostrar enemigos
    if (!habitacion->estaDespejada()) {
        std::cout << "¡PELIGRO! Enemigos presentes: ";

        // Invocamos la lista para poder contar cuántos enemigos hay
        const std::vector<Entidad*>& lista = habitacion->getEnemigos();

        for (size_t i = 0; i < lista.size(); ++i) {
            // Imprimimos el nombre del enemigo actual
            std::cout << lista[i]->getNombre();

            //
            // Si NO es el último de la lista, pone una coma y un espacio
            if (i < lista.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << endl;
    } else {
        std::cout << "(Zona despejada)" << endl;
    }
}

void Vista::mostrarInteraccionesDisponibles(const std::vector<LugarDeInteraccion*>& lista) {
    std::cout << "\n--- OBJETOS VISIBLES ---" << std::endl;

    if (lista.empty()) {
        std::cout << "No ves nada interesante aqui." << std::endl;
        return;
    }

    for (size_t i = 0; i < lista.size(); ++i) {
        // Mostramos "1. Nombre", "2. Nombre"
        std::cout << (i + 1) << ". " << lista[i]->getNombre();

        // Opcional: Mostrar si ya fue usado para que el jugador sepa
        if (lista[i]->isUsado()) {
            std::cout << " (Ya investigado)";
        }
        std::cout << std::endl;
    }
    std::cout << "0. Cancelar" << std::endl;
    std::cout << "Selecciona un numero: ";
}

void Vista::mostrarHUD(Heroe* heroe) {
    cout << "\n[" << heroe->getNombre() << " | Nvl: " << heroe->getNivel()
         << " | HP: " << heroe->getPuntosDeVida() << "/" << heroe->getPuntosDeVidaMax()
         << " | ATK: " << heroe->getAtaque() << " | DEF: " << heroe->getDefensa() << "]" << endl;
}

void Vista::mostrarMenuAcciones() {
    cout << "\n¿Que deseas hacer?" << endl;
    cout << "1. Moverse" << endl;
    cout << "2. Interactuar / Buscar" << endl;
    cout << "3. Gestionar Inventario" << endl;
    cout << "4. Guardar y Salir" << endl;
    cout << ">> ";
}

void Vista::mostrarMenuCombate() {
    cout << "\n--- COMBATE ---" << endl;
    cout << "1. Atacar" << endl;
    cout << "2. Usar Item" << endl;
    cout << "3. Intentar Huir" << endl;
    cout << ">> ";
}

void Vista::mostrarInventario(const std::vector<Item*>& inventario) {
    std::cout << "\n=== MOCHILA DEL HEROE ===" << std::endl;

    if (inventario.empty()) {
        std::cout << "(Vacia)" << std::endl;
        return;
    }

    for (size_t i = 0; i < inventario.size(); ++i) {
        std::cout << "[" << (i + 1) << "] " << inventario[i]->getNombre()
                  << " (" << inventario[i]->getDescripcion() << ")" << std::endl;
    }
    std::cout << "[0] Salir" << std::endl;
    std::cout << "Elige un objeto para usar/equipar: ";
}

void Vista::mostrarMensaje(std::string mensaje) {
    cout << mensaje << endl;
}

int Vista::pedirOpcion() {
    int opcion;
    cin >> opcion;
    // Limpieza basica del buffer
    if(cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        return -1;
    }
    return opcion;
}

std::string Vista::pedirString() {
    string texto;
    cin >> texto;
    return texto;
}