//
// Created by jpfra on 19/11/25.
//

#include "Controlador.h"
#include <iostream>

Controlador::Controlador() : heroe(nullptr), habitacionActual(nullptr), juegoTerminado(false) {}

Controlador::~Controlador() {
    delete heroe;
    // Aquí deberías borrar recursivamente las habitaciones si no usas un gestor global
    // Por simplicidad, asumimos que el SO limpia al terminar, pero idealmente
    // deberías tener un vector<Habitacion*> todasLasHabitaciones para borrarlas.
}

void Controlador::inicializarMapa() {
    // 1. Crear Habitaciones
    Habitacion* celda = new Habitacion("Celda Prision", "Una celda humeda y oscura.", 1);
    Habitacion* pasillo = new Habitacion("Pasillo de Piedra", "Antorchas iluminan tenuemente las paredes.", 1);
    Habitacion* armeria = new Habitacion("Armeria Abandonada", "Estantes rotos y armas oxidadas.", 2);
    Habitacion* salaTrono = new Habitacion("Sala del Trono", "El aire es pesado aqui. El Jefe espera.", 3);

    // 2. Conectar Habitaciones
    celda->agregarSalida("Norte", pasillo);
    pasillo->agregarSalida("Sur", celda);
    pasillo->agregarSalida("Este", armeria);
    pasillo->agregarSalida("Norte", salaTrono);
    armeria->agregarSalida("Oeste", pasillo);
    salaTrono->agregarSalida("Sur", pasillo);

    // 3. Agregar Enemigos
    pasillo->agregarEnemigo(new Esqueleto("Esqueleto Errante", "Un monton de huesos vivientes.", 20, 5, 1));
    armeria->agregarEnemigo(new Guardia("Guardia Corrupto", "Un guardia que olvido su juramento.", 40, 10, 3));
    salaTrono->agregarEnemigo(new Jefe("Chameni", "El señor oscuro del calabozo.", 100, 20, 10));

    // 4. Agregar Interacciones (Loot)
    // Cofre en la celda
    Item* pocion = new Curativo("Pocion Pequena", 20);
    celda->agregarInteraccion(new LugarDeInteraccion("Cofre Viejo", "Bajo la cama", pocion, 0));

    // Altar en la armería
    armeria->agregarInteraccion(new LugarDeInteraccion("Fuente Sagrada", "Agua brillante", nullptr, 50));

    // Arma en la armería (Cofre)
    Item* espada = new Arma("Espada Real", 25);
    armeria->agregarInteraccion(new LugarDeInteraccion("Expositor de Armas", "Vitrina rota", espada, 0));

    // 5. Definir inicio
    this->habitacionActual = celda;
}

void Controlador::iniciar() {
    vista.mostrarBienvenida();
    std::string nombre = vista.pedirString();

    // Crear Héroe (Nombre, Desc, HP, Atk, Def)
    heroe = new Heroe(nombre, "Un valiente aventurero", 100, 10, 5);

    inicializarMapa();

    // Bucle Principal
    while (!juegoTerminado && heroe->getPuntosDeVida() > 0) {
        vista.mostrarHUD(heroe);
        vista.mostrarLugar(habitacionActual);

        // Si hay enemigos, entramos en combate OBLIGATORIO (o das opción a huir)
        if (!habitacionActual->estaDespejada()) {
            procesarCombate();
            if (heroe->getPuntosDeVida() <= 0) break; // Game Over
        }

        // Si no hay enemigos (o ya murieron), mostramos menú de exploración
        vista.mostrarMenuAcciones();
        int opcion = vista.pedirOpcion();

        switch (opcion) {
            case 1: procesarMovimiento(); break;
            case 2: procesarInteraccion(); break;
            case 3: procesarInventario(); break;
            case 4:
                guardarPartida();
                juegoTerminado = true;
                break;
            default: vista.mostrarMensaje("Opcion no valida.");
        }
    }

    if (heroe->getPuntosDeVida() <= 0) {
        vista.mostrarMensaje("=== HAS MUERTO ===");
    } else {
        vista.mostrarMensaje("¡Gracias por jugar!");
    }
}

void Controlador::procesarCombate() {
    vista.mostrarMensaje("\n!!! COMBATE INICIADO !!!");

    // Simplificación: Peleamos contra el primer enemigo de la lista
    // Nota: Necesitas acceso a los enemigos. Habitacion tiene getEnemigos().
    // Asumimos que getEnemigos devuelve una referencia al vector.

    // Obtenemos el primer enemigo vivo
    std::vector<Entidad*> enemigos = habitacionActual->getEnemigos();
    if (enemigos.empty()) return;

    Entidad* enemigo = enemigos[0];

    while (enemigo->getPuntosDeVida() > 0 && heroe->getPuntosDeVida() > 0) {
        vista.mostrarMensaje("\nVs: " + enemigo->getNombre() + " (HP: " + std::to_string(enemigo->getPuntosDeVida()) + ")");
        vista.mostrarMenuCombate();
        int op = vista.pedirOpcion();

        // Turno Jugador
        if (op == 1) {
            heroe->movimiento1(*enemigo); // Atacar
        } else if (op == 2) {
            procesarInventario(); // Usar item en combate
        } else if (op == 3) {
            vista.mostrarMensaje("¡Intentas huir pero te bloquean el paso!");
            // Podrías agregar % de éxito
        }

        // Turno Enemigo (si sigue vivo)
        if (enemigo->getPuntosDeVida() > 0) {
            enemigo->movimiento1(*heroe);
        }
    }

    if (enemigo->getPuntosDeVida() <= 0) {
        vista.mostrarMensaje("¡Has derrotado a " + enemigo->getNombre() + "!");
        enemigo->morir(*heroe); // Loot
        habitacionActual->removerEnemigo(enemigo);

        // Héroe gana experiencia (Faltaba implementar getters de experiencia en enemigo, inventamos valor)
        heroe->ganarExperiencia(50);
    }
}

void Controlador::procesarMovimiento() {
    vista.mostrarMensaje("¿Hacia donde? (Escribe: Norte, Sur, Este, Oeste): ");
    std::string dir = vista.pedirString();

    Habitacion* destino = habitacionActual->getSalida(dir);
    if (destino != nullptr) {
        habitacionActual = destino;
        vista.mostrarMensaje("Te mueves hacia el " + dir);
    } else {
        vista.mostrarMensaje("No hay salida en esa dirección.");
    }
}

void Controlador::procesarInteraccion() {
    // Preguntar qué quiere investigar
    // Por simplicidad, interactuamos con todo lo que haya en la sala secuencialmente
    // Lo ideal sería listar las interacciones y elegir.

    // Nota: En tu Habitacion.h necesitas un metodo getInteracciones() publico o
    // usar el metodo interactuarCon(nombre).

    vista.mostrarMensaje("¿Que quieres investigar? (Escribe el nombre exacto del objeto/lugar):");
    // Mostramos qué hay
    // (Asumiendo que puedes acceder a la lista o implementar un metodo 'mostrarInteracciones' en habitacion)

    std::string nombre = vista.pedirString();
    bool exito = habitacionActual->interactuarCon(nombre, *heroe);

    if (!exito) {
        vista.mostrarMensaje("No ves eso por aqui.");
    }
}

void Controlador::procesarInventario() {
    // Aquí deberías recorrer heroe->inventario y permitir usar items.
    // Requiere implementar getters públicos del inventario en Entidad.
    vista.mostrarMensaje("Gestión de inventario pendiente de implementar getter publico.");
}

void Controlador::guardarPartida() {
    vista.mostrarMensaje("Guardando partida... (Simulacion)");
    // Aquí usarías <fstream> para escribir heroe->getNombre(), nivel, hp, etc. en un .txt
}