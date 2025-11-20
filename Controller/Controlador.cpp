//
// Created by jpfra on 19/11/25.
//

#include "Controlador.h"
#include <iostream>
#include <algorithm> // para transform
#include <cctype>    // para tolower

Controlador::Controlador() : heroe(nullptr), habitacionActual(nullptr), juegoTerminado(false) {}

Controlador::~Controlador() {
    delete heroe;
    // Aquí deberías borrar recursivamente las habitaciones si no usas un gestor global
    // Por simplicidad, asumimos que el SO limpia al terminar, pero idealmente
    // deberías tener un vector<Habitacion*> todasLasHabitaciones para borrarlas.
}

void Controlador::inicializarMapa() {
    // Habitaciones
    Habitacion* entrada = new Habitacion("Entrada del Calabozo", "Te aproximas al temido Calabozo de Erelis, una ciudad macabra con una historia violenta. \nVas en busca de tu hija de 5 anios, Carlotta, que desapareció hace tres semanas justo aquí, en el Calabozo.", 1);
    Habitacion* pasillo = new Habitacion("Pasillo Principal", "Entras al calabozo, dispuesto a salvar a tu hija. Tus ojos se adaptan a la poca luz, solo algunas antorchas iluminan tu camino.\nEl pasillo se extiende hacia la oscuridad, no ves su final, pero escuchas el traqueteo de...huesos?", 1);
    Habitacion* armeria = new Habitacion("Armeria Abandonada", "Estantes rotos y armas oxidadas.", 2);
    Habitacion* salaTrono = new Habitacion("Sala del Trono", "El aire es pesado aqui. El Jefe espera.", 3);

    // Conexiones entre Habitaciones
    entrada->agregarSalida("Norte", pasillo);
    pasillo->agregarSalida("Sur", entrada);
    pasillo->agregarSalida("Este", armeria);
    pasillo->agregarSalida("Norte", salaTrono);
    armeria->agregarSalida("Oeste", pasillo);
    salaTrono->agregarSalida("Sur", pasillo);

    //Agregamos Enemigos
    pasillo->agregarEnemigo(new Esqueleto("Esqueleto Errante", "Un monton de huesos vivientes.", 20, 5, 1));
    armeria->agregarEnemigo(new Guardia("Guardia Corrupto", "Un guardia que olvido su juramento.", 40, 10, 3));
    salaTrono->agregarEnemigo(new Jefe("Chameni", "El señor oscuro del calabozo.", 100, 20, 10));

    //Agregamos Interacciones
    // Cofre en la celda
    Item* hierbas1 = new Curativo("Hierbas", "Curacion baja. +5HP.", 5);
    entrada->agregarInteraccion(new LugarDeInteraccion("Caja", "Una caja de cargamento antigua, no se sabe quien la dejo ahi.", hierbas1, 0));

    // Altar en la armería
    armeria->agregarInteraccion(new LugarDeInteraccion("Fuente Sagrada", "Agua brillante", nullptr, 50));

    // Arma en la armería (Cofre)
    Item* espada = new Arma("Espada del Heroe","Espada formidable disennada para los mayores guerreros. +15ATK.",  25);
    armeria->agregarInteraccion(new LugarDeInteraccion("Expositor de Armas", "Vitrina rota", espada, 0));

    // 5. Definir inicio
    this->habitacionActual = entrada;
}

void Controlador::iniciar() {
    vista.mostrarBienvenida();
    std::string nombre = vista.pedirString();

    // Crear Héroe (Nombre, Desc, HP, Atk, Def)
    heroe = new Heroe(nombre, "Un valiente aventurero, en busca de su hija perdida en la oscuridad.", 100, 10, 1);

    inicializarMapa();

    // Bucle Principal
    while (!juegoTerminado && heroe->getPuntosDeVida() > 0) {
        vista.mostrarHUD(heroe);
        vista.mostrarLugar(habitacionActual);

        // Si hay enemigos, entramos en combate OBLIGATORIO
        if (!habitacionActual->estaDespejada()) {
            procesarCombate();
            if (heroe->getPuntosDeVida() <= 0) break; // GAMEOVERRRR se acaba
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
        vista.mostrarMensaje("\nVS.: " + enemigo->getNombre() + " (HP: " + std::to_string(enemigo->getPuntosDeVida()) + ")");
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

// Para convertir a minúsculas (las funciones auxiliares deben ponerse arriba de la funcion grande q las usa)
std::string aMinusculas(std::string texto) {
    std::transform(texto.begin(), texto.end(), texto.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return texto;
}

void Controlador::procesarMovimiento() {
    vista.mostrarMensaje("¿Hacia donde? (Norte, Sur, Este, Oeste): ");
    std::string entradaUsuario = vista.pedirString();

    //Aqui se convierte a minusculas con la funcion de justo arribita
    std::string direccion = aMinusculas(entradaUsuario);

    // Solo dejamos la primera letra mayuscula para que cuadre con lo de movimiento
    if (!direccion.empty()) {
        direccion[0] = std::toupper(direccion[0]);
    }

    // Se usa la salida formateada
    Habitacion* destino = habitacionActual->getSalida(direccion);

    if (destino != nullptr) {
        habitacionActual = destino;
        vista.mostrarMensaje("Te mueves hacia el " + direccion);
    } else {
        vista.mostrarMensaje("No hay salida hacia el " + direccion);
    }
}

void Controlador::procesarInteraccion() {
    // 1. Obtenemos la lista de cosas en la habitación actual
    // (Asegúrate de haber agregado el getter en el paso 1)
    const std::vector<LugarDeInteraccion*>& lista = habitacionActual->getInteracciones();

    // 2. Le decimos a la vista que muestre la lista numerada
    vista.mostrarInteraccionesDisponibles(lista);

    if (lista.empty()) return; // Si no hay nada, salimos

    // 3. Pedimos el número al usuario
    int opcion = vista.pedirOpcion();

    // 4. Lógica de selección
    if (opcion == 0) {
        vista.mostrarMensaje("Decides no tocar nada.");
        return;
    }

    // Validamos que el número sea válido (entre 1 y el tamaño de la lista)
    if (opcion > 0 && opcion <= lista.size()) {
        // El vector empieza en 0, pero el menú empieza en 1, así que restamos 1
        LugarDeInteraccion* lugarElegido = lista[opcion - 1];

        // Ejecutamos la interacción
        lugarElegido->ejecutarInteraccion(*heroe);
    } else {
        vista.mostrarMensaje("Opcion no valida.");
    }
}

void Controlador::procesarInventario() {
    // Obtener el inventario
    const std::vector<Item*>& mochila = heroe->getInventario();

    // Si está vacío, avisar y salir
    if (mochila.empty()) {
        vista.mostrarMensaje("Tu inventario esta vacio.");
        return;
    }

    // Mostrar el inventario
    vista.mostrarInventario(mochila);

    // Pedir número de inventario a elegir
    int opcion = vista.pedirOpcion();

    // Para salir del inventario
    if (opcion == 0) return;

    // Validar rango para no coger objetos por fuera
    if (opcion > 0 && opcion <= mochila.size()) {
        // Ajustamos indice (Usuario pone 1 pero el Vector empieza en 0)
        int indice = opcion - 1;
        Item* itemElegido = mochila[indice];

        // Intentamos ver si el objeto es de tipo Curativo
        Curativo* pocion = dynamic_cast<Curativo*>(itemElegido);

        // Si ES curativo y la vida ya está al máximo no se usa para que el usuario no desperdicie
        if (pocion != nullptr && heroe->getPuntosDeVida() >= heroe->getPuntosDeVidaMax()) {
            vista.mostrarMensaje("Tu salud esta al maximo. No tiene sentido usar esto ahora.");
            return; // Salimos aquí para NO gastar el objeto
        }

        // Si pasa la validación, lo usamos normalmente
        // Usar esta construido para manejar la funcion de cualquiera de los 3 objetos, POLIMORFISMO
        itemElegido->usar(heroe);

        if (itemElegido->getEsConsumible()) {
            // Lo sacamos del vector del héroe
            heroe->eliminarItem(indice);
            // Lo borramos de la memoria para evitar memory leak
            delete itemElegido;
        }
    } else {
        vista.mostrarMensaje("Opcion invalida.");
    }
}

void Controlador::guardarPartida() {
    vista.mostrarMensaje("Guardando partida... (Simulacion)");
    // Aquí usarías <fstream> para escribir heroe->getNombre(), nivel, hp, etc. en un .txt
}

