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
   ## ##              /###     /###   ##   ####    ###  /###     /###         /##  ###  /###
   ## ##             / ###  / / ###  / ##    ###  / ###/ #### / / ###  /     / ###  ###/ #### /
   ## ##            /   ###/ /   ###/  ##     ###/   ##   ###/ /   ###/     /   ###  ##   ###/
   ## ##           ##    ## ##         ##      ##    ##       ##    ##     ##    ### ##    ##
   ## ##           ##    ## ##         ##      ##    ##       ##    ##     ########  ##    ##
   #  ##           ##    ## ##         ##      ##    ##       ##    ##     #######   ##    ##
      /            ##    ## ##         ##      ##    ##       ##    ##     ##        ##    ##
  /##/           / ##    ## ###     /  ##      /#    ##       ##    /#     ####    / ##    ##
 /  ############/   ######   ######/    ######/ ##   ###       ####/ ##     ######/  ###   ###
/     #########      ####     #####      #####   ##   ###       ###   ##     #####    ###   ###
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
    cout << "                    BIENVENIDO, AVENTURERO" << endl;
    cout << "==================================================================" << endl;
    cout << "Ingresa el nombre de tu Heroe: ";
}

void Vista::mostrarLugar(Habitacion* habitacion) {
    cout << "\n--- " << habitacion->getNombre() << " ---" << endl;
    cout << habitacion->getDescripcion() << endl;

    // Mostrar salidas
    cout << "Salidas visibles: ";
    for (auto const& [direccion, puntero] : habitacion->getSalidas()) {
        cout << "[" << direccion << "] ";
    }
    cout << endl;

    // Mostrar enemigos
    if (!habitacion->estaDespejada()) {
        cout << "¡PELIGRO! Enemigos presentes: ";
        for (auto enemigo : habitacion->getEnemigos()) {
            cout << enemigo->getNombre() << " ";
        }
        cout << endl;
    } else {
        cout << "(Zona despejada)" << endl;
    }
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

void Vista::mostrarInventario(Heroe* heroe) {
    // Nota: Necesitas un getter publico del inventario en Entidad/Heroe para esto
    // Asumo que agregas: const std::vector<Item*>& getInventarioVec() const { return inventario; }
    // O implementas un metodo mostrarInventario en Heroe.

    // Para simplificar la vista, asumimos que Heroe tiene un metodo para mostrarlo o accedemos al vector
    // Aquí simulamos un mensaje genérico si no tienes el getter listo:
    cout << "\n--- INVENTARIO ---" << endl;
    // (Aquí recorrerías el vector del héroe)
    cout << "Usa la logica del Controlador para listar items." << endl;
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