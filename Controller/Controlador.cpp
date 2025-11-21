//
// Created by jpfra on 19/11/25.
//

#include "Controlador.h"
#include <iostream>
#include <algorithm> // para transform
#include <cctype>    // para tolower


Controlador::Controlador() : heroe(nullptr), habitacionActual(nullptr), habitacionAnterior(nullptr), juegoTerminado(false) {}

Controlador::~Controlador() {
    if (heroe != nullptr) {
        delete heroe;
    }

    // Borrar habitaciones para evitar fugas
    // Como usamos mapaGlobal lo recorremos para borrarlas todas.
    for (Habitacion* hab : mapaGlobal) {
        delete hab;
    }

    // Limpiar el vector para que no queden punteros a la deriva
    mapaGlobal.clear();
}

void Controlador::inicializarMapa() {
    // Habitaciones
    Habitacion* entrada = new Habitacion("Entrada del Calabozo", "Te aproximas al temido Calabozo de Erelis, una ciudad macabra con una historia violenta. \nVas en busca de tu hija de 5 anios, Carlotta, que desapareció hace tres semanas justo aquí, en el Calabozo.", 1);
    Habitacion* pasillo = new Habitacion("Pasillo Principal", "Entras al calabozo, dispuesto a salvar a tu hija. Tus ojos se adaptan a la poca luz, solo algunas antorchas iluminan tu camino.\nEl pasillo se extiende hacia la oscuridad, no ves su final, pero escuchas el traqueteo de...huesos?", 1);
    Habitacion* armeria = new Habitacion("Armeria Abandonada", "Entre estantes rotos y armas oxidadas entras a una antigua armeria. \nNo hay mucho que ver, salvo una pequenna vitrina con lo que parece ser una lanza. \nEspera, algo grande se mueve...", 2);
    Habitacion* celda = new Habitacion("Celda Decrepita", "Si hay guardias, hay prisioneros, y este sitio lo demuestra. Filas y filas de rejas esconden los restos \nde aventureros menos afortunados...pero algunos no estan del todo muertos.",2);
    Habitacion* cementerio = new Habitacion("Cementerio", "Al parecer hay mas muertos aqui de lo que pensabas. Sales del pasillo a una crater boscoso al aire libre, rodeado por riscos que impiden tu escape, donde tumbas yacen a la luz de la luna. Ten cuidado con el ejercito de esqueletos!",3);
    Habitacion* laberinto = new Habitacion("Laberinto Interminable", "Pasando el cementerio, el calabozo vuelve a apoderarse del lugar, cerrando el camino a una serie de pasillos interminables con enemigos que aun vagan, perdidos.",4);

    Habitacion* salaMala1 = new Habitacion("Callejon sin Salida", "El laberinto no perdona, y te ha arrojado a una sala sin avance, pero repleta de enemigos sedientos de sangre.",5);
    Habitacion* salaMala2 = new Habitacion("Punto sin Avance", "El laberinto no perdona, y te ha arrojado a una sala sin avance, pero repleta de enemigos sedientos de sangre.",5);

    Habitacion* salaFinal = new Habitacion("Trono de la Engendra", "Pasando el cementerio, el calabozo vuelve a apoderarse del lugar, cerrando el camino a una serie de pasillos interminables con enemigos que aun vagan, perdidos.",5);

    Habitacion* salaTrono = new Habitacion("Sala del Trono", "El aire es pesado aqui. El Jefe espera.", 3);
    mapaGlobal.clear();
    mapaGlobal.push_back(entrada);
    mapaGlobal.push_back(pasillo);
    mapaGlobal.push_back(armeria);
    mapaGlobal.push_back(salaFinal);
    mapaGlobal.push_back(celda);
    mapaGlobal.push_back(cementerio);
    mapaGlobal.push_back(laberinto);
    mapaGlobal.push_back(salaMala1);
    mapaGlobal.push_back(salaMala2);

    // Conexiones entre Habitaciones
    entrada->agregarSalida("Norte", pasillo);

    pasillo->agregarSalida("Sur", entrada);
    pasillo->agregarSalida("Este", armeria);
    pasillo->agregarSalida("Norte", cementerio);
    pasillo->agregarSalida("Oeste", celda);

    celda->agregarSalida("Este", pasillo);

    armeria->agregarSalida("Oeste", pasillo);

    cementerio->agregarSalida("Sur", pasillo);
    cementerio->agregarSalida("Norte", laberinto);

    laberinto->agregarSalida("Sur", cementerio);
    laberinto->agregarSalida("Este", salaMala1);
    laberinto->agregarSalida("Norte", salaMala2);
    laberinto->agregarSalida("Oeste", salaFinal);

    salaMala1->agregarSalida("Oeste", laberinto);

    salaMala2->agregarSalida("Sur", laberinto);


    //Agregamos Enemigos
    pasillo->agregarEnemigo(new Esqueleto("Esqueleto Errante", "Un monton de huesos vivientes.", 20, 5, 1));

    armeria->agregarEnemigo(new Guardia("Guardia Grotesco", "Un guardia que olvido su juramento.", 40, 15, 5));

    celda->agregarEnemigo(new Esqueleto("Esqueleto Aventurero", "Un aventurero del pasado.", 20, 5, 1));
    celda->agregarEnemigo(new Guardia("Guardia Enfurecido", "No debiste molestar a sus prisioneros.", 40, 15, 5));

    cementerio->agregarEnemigo(new Esqueleto("Esqueleto (1/5)", "Se aproxima un ejercito.", 30, 10, 3));
    cementerio->agregarEnemigo(new Esqueleto("Esqueleto (2/5)", "Se aproxima un ejercito.", 30, 10, 3));
    cementerio->agregarEnemigo(new Esqueleto("Esqueleto (3/5)", "Se aproxima un ejercito.", 30, 10, 3));
    cementerio->agregarEnemigo(new Esqueleto("Esqueleto (4/5)", "Se aproxima un ejercito.", 30, 10, 3));
    cementerio->agregarEnemigo(new Esqueleto("Jefe Esqueleto (5/5)", "Se aproxima un ejercito.", 50, 20, 6));

    salaMala1->agregarEnemigo(new Guardia("Guardia Gigante", "Dificil de esquivar.", 100, 70, 20));

    salaMala2->agregarEnemigo(new Esqueleto("Esqueleto de Oro", "No se rompe el maldito.", 150, 50, 30));

    salaFinal->agregarEnemigo(new Jefe("Chameni, Engendra del Calabozo", "Una entidad maligna hecha mujer, personificacion del calabozo.", 200, 85, 30));

    //Agregamos Interacciones
    // Caja en la entrada y carta
    Item* hierbas1 = new Curativo("Hierbas", "Curacion baja. +5HP.", 5);
    entrada->agregarInteraccion(new LugarDeInteraccion("Caja", "Una caja de cargamento antigua, no se sabe quien la dejo ahi.", hierbas1, 0));
    entrada->agregarInteraccion(new LugarDeInteraccion("Papel", "Ves un pedazo de papel, al acercarte, descubres que en realidad es una hoja arrancada de un diario.\n'Los que entran aqui no salen iguales. Da la vuelta.'", nullptr, 0));

    //Letrero en el pasillo
    pasillo->agregarInteraccion(new LugarDeInteraccion("Letreros Grabados", "Dos letreros yacen en lo alto del pasillo, uno apuntando al Este y otro al Oeste.\nHacia el Este: Un dibujo de una espada.\nHacia el Oeste: Un dibujo de una puerta con barrotes.", nullptr, 0));

    // Vitrina en la armería
    Item* lanzaArmeria = new Arma("Lanza","Una lanza de caballeria, ideal para atravesar enemigos que se acercan demasiado. +5ATK.",  5);
    armeria->agregarInteraccion(new LugarDeInteraccion("Expositor de Armas", "Vitrina rota, una vieja lanza yace dentro.", lanzaArmeria, 0));

    // Curacion en el cementerio
    cementerio->agregarInteraccion(new LugarDeInteraccion("Fuente Sagrada", "Un cenotafio imponente proyecta una sombra sobre el cementerio, sin embargo, en su base hay luz. \nTe acercas, y ves que es una fuente con agua cristalina. Al beber de ella, sientes como te rejuveneces. +80HP.", nullptr, 80));

    //Cofre en el laberinto
    Item* invocacionLab = new Curativo("Libro de Invocaciones", "Curacion extremadamente alta, guardalo bien. +100HP.", 100);
    laberinto->agregarInteraccion(new LugarDeInteraccion("Cofre Antiguo", "Se ve que nadie ha tocado esto en anios, con dificultad, logras abrirlo, y adentro...algo brilla.", invocacionLab, 0));

    //Funda en el laberinto
    Item* espadaSupremaLab = new Arma("Espada Suprema", "Un arma que parece puesta a proposito para ti. Usala, es tu unica esperanza. +50ATK.", 50);
    laberinto->agregarInteraccion(new LugarDeInteraccion("Funda de Espada", "Una esquina del laberinto te llama...algo poderoso te espera. Esta espada sera tu mejor esperanza.", espadaSupremaLab, 0));

    //Soporte de armadura Laberinto
    Item* armaduraSuprema = new Armadura("Armadura Suprema", "Una armadura que parece puesta a proposito para ti. Usala, es tu unica esperanza. +30DEF.", 30);
    laberinto->agregarInteraccion(new LugarDeInteraccion("Soporte de Armadura", "Una armadura maciza cuelga de un soporte viejo. Quien la dejo ahi? No se sabe, pero ahora te protegera.", armaduraSuprema, 0));

    // Curacion en salaMala1
    salaMala1->agregarInteraccion(new LugarDeInteraccion("Pilar de Deseos", "Un altar a un dios desconocido. No eres religioso, pero rezar es tu unica opcion contra la locura. \nTe acercas, e invocas al dios antiguo. +150HP.", nullptr, 150));

    // Curacion en salaMala2
    salaMala2->agregarInteraccion(new LugarDeInteraccion("Pacto de Sangre", "Un pentagrama de sangre en el piso de la sala. Te asusta, pero estas dispuesto a hacer lo que sea para sobrevivir. \nTe acercas, y cortas tu mano con tu espada, dejando fluir sangre al circulo. La sala retumba, el circulo te acepta. +150HP.", nullptr, 150));

    // Definir inicio
    this->habitacionActual = entrada;
}

void Controlador::iniciar() {
    vista.mostrarBienvenida();
    // PREGUNTA DE CARGA
    vista.mostrarMensaje("\n1. Nueva Partida");
    vista.mostrarMensaje("2. Cargar Partida");
    int op = vista.pedirOpcion();
    std::cin.ignore();

    inicializarMapa(); // Primero creamos el mundo

    if (op == 2) {
        cargarPartida();
        // Si la carga falló (no había archivo), creamos un héroe por defecto
        if (heroe == nullptr) {
            vista.mostrarMensaje("No se encontro partida guardada. Iniciando una nueva.");

            vista.mostrarMensaje("Ingresa el nombre de tu Heroe: ");
            std::string nombre;
            std::getline(std::cin, nombre);

            if (nombre.empty()) nombre = "Aventurero"; // Nombre por defecto si da Enter vacío
            heroe = new Heroe(nombre, "Un valiente aventurero, en busca de su hija perdida en la oscuridad.", 100, 10, 1);
        }
    } else {
        // Nueva Partida normal
        vista.mostrarMensaje("Ingresa el nombre de tu Heroe: ");

        std::string nombre;
        std::getline(std::cin, nombre); // Leemos el nombre con espacios

        if (nombre.empty()) nombre = "Aventurero"; // Protección contra nombre vacío
        heroe = new Heroe(nombre, "Un valiente aventurero, en busca de su hija perdida en la oscuridad.", 100, 10, 1);
    }

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
        std::cin.ignore(); //Para limpiar buffer

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

    // === NUEVO BUCLE EXTERNO (LA OLA DE ENEMIGOS) ===
    // Este bucle no te deja salir hasta que mates a TODOS o mueras/huyas
    while (!habitacionActual->estaDespejada() && heroe->getPuntosDeVida() > 0) { //EL punto de exclamacion es un not, invierte lo q le pedimos

        // 1. Seleccionamos SIEMPRE al primer enemigo de la fila.
        // Como al matar al anterior lo borramos del vector, el siguiente ocupa su lugar (índice 0).
        std::vector<Entidad*> listaEnemigos = habitacionActual->getEnemigos();
        Entidad* enemigo = listaEnemigos.front(); // .front() es igual a [0]

        while (enemigo->getPuntosDeVida() > 0 && heroe->getPuntosDeVida() > 0) {
            vista.mostrarHUD(heroe);
            vista.mostrarMensaje("\nVS.: " + enemigo->getNombre() + " (HP: " + std::to_string(enemigo->getPuntosDeVida()) + ")");
            vista.mostrarMenuCombate();
            int op = vista.pedirOpcion();

            // Turno Jugador
            if (op == 1) {
                heroe->movimiento1(*enemigo); // Atacar
            } else if (op == 2) {
                procesarInventario(); // Usar item en combate
            } else if (op == 3) {
                // Antes de permitir escape, vemos si es el jefe final (que no escapen da mas susto)
                // Usamos dynamic_cast para ver si el enemigo es de la clase Jefe
                if (dynamic_cast<Jefe*>(enemigo) != nullptr) {
                    vista.mostrarMensaje("¡Es inútil! La oscuridad no permite marcha atras. No puedes huir de Chameni, la Engendra del Calabozo.");
                    // No hay return para que el jugador pierda el turno por cobarde!!!
                }
                else {
                    // Calculamos la probabilidad de que escape el jugador
                    int suerte = std::rand() % 100; // Genera 0 a 99

                    if (suerte < 50) {
                        // FRACASO
                        vista.mostrarMensaje("¡Intentaste correr pero te tropezaste! El enemigo aprovecha tu error.");
                        // No hay return para que se pierda turno y recibir daño
                    } else {
                        // EXITO DE ESCAPE
                        if (habitacionAnterior == nullptr) {
                            // NO HAY SALIDA
                            vista.mostrarMensaje("¡Logras esquivar, pero la salida está bloqueada! No hay a dónde correr.");
                            // NO ponemos 'return' para que el combate siga
                            // Al no salir, el código sigue bajando y el enemigo te atacará.
                        }
                        else {
                            // SI HAY SALIDA
                            habitacionActual = habitacionAnterior;
                            vista.mostrarMensaje("¡Logras evitar los golpes y sales ileso. Escapaste a " + habitacionActual->getNombre());
                            vista.mostrarHUD(heroe);
                            return;

                        }
                        vista.mostrarHUD(heroe);
                    }
                }
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
            //Con dynamic_cast se revisa si el enemigo es jefe
            if (dynamic_cast<Jefe*>(enemigo) != nullptr) {
                vista.mostrarMensaje("\n**************************************************");
                vista.mostrarMensaje("   ¡VICTORIA! HAS LIBERADO EL CALABOZO DE ERELIS   ");
                vista.mostrarMensaje("\nChameni pierde vigor y cae al piso, desangrada. Su vida se le escapa. Alrederor, el calabozo se recupera, los guardias y esqueletos mueren, el sol sale. ");
                std::cout << heroe->getNombre() << " saca su espada untada de sangre negra del cuerpo de la aterradora mujer." << std::endl;
                vista.mostrarMensaje("El cuerpo de la mujer malvada se retuerce, como si algo intentara escapar. Sus unnas se tornan negras, su pelo se acorta...");
                vista.mostrarMensaje("Su piel cambia, de arrugada y amarilla a...blanca y suave");
                vista.mostrarMensaje("Su altura...se encoge.");
                vista.mostrarMensaje("Ya no es un monstruo en cuerpo de mujer...Chameni es...");
                vista.mostrarMensaje("\n 'Hija!' ");
                std::cout << heroe->getNombre() << " corre a poner a Carlotta en sus piernas, sosteniendo su cabeza palida." << std::endl;
                vista.mostrarMensaje("\n 'NO, NO, NO! QUEDATE CONMIGO, LOTTIE. POR FAVOR' ");
                vista.mostrarMensaje("\n La luz abandona los ojos de Carlotta, y una sombra oscura escapa de su cuerpo, una entidad antigua...mas antigua que el calabozo. ");
                std::cout << heroe->getNombre() << " se desploma, llorando." << std::endl;
                vista.mostrarMensaje("\n N A D I E    N U N C A    S A L E    I G U A L   D E L    C A L A B O Z O");









                juegoTerminado = true; // Esto rompe el bucle while principal
                return; // Salimos del combate
            }

            heroe->ganarExperiencia(50);
        }
    } //Aqui se acaba el bucle grandote
    if (heroe->getPuntosDeVida() > 0) {
        vista.mostrarMensaje("\nLa sala esta en silencio. Has vencido a todos.");
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
        this->habitacionAnterior = this->habitacionActual; // Se guarda la habitacion anterior
        this->habitacionActual = destino;
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
    std::ofstream archivo("savegame.txt");

    if (archivo.is_open()) {
        // Datos del Héroe
        archivo << heroe->getNombre() << std::endl;
        archivo << heroe->getDescripcion() << std::endl;
        archivo << heroe->getNivel() << std::endl;
        archivo << heroe->getExperiencia() << std::endl;
        archivo << heroe->getPuntosDeVida() << std::endl;
        archivo << heroe->getPuntosDeVidaMax() << std::endl;
        archivo << heroe->getAtaque() << std::endl;
        archivo << heroe->getDefensa() << std::endl;

        // Ubicación
        archivo << habitacionActual->getNombre() << std::endl;

        // Guardado de inventario
        // Escribimos cuántos items tenemos para saber cuántos debe leer luego
        archivo << heroe->getInventario().size() << std::endl;

        for (Item* item : heroe->getInventario()) {
            // TIPO 1: Curativo | TIPO 2: Arma | TIPO 3: Armadura

            if (dynamic_cast<Curativo*>(item)) {
                archivo << 1 << std::endl; // Tipo
                archivo << item->getNombre() << std::endl; // Nombre completo
                archivo << item->getDescripcion() << std::endl; // Descripción original
                // Recuperamos el valor. Como item genérico no tiene getValorCuracion,
                // hacemos un cast temporal seguro:
                archivo << ((Curativo*)item)->getValorCuracion() << std::endl;
            }
            else if (dynamic_cast<Arma*>(item)) {
                archivo << 2 << std::endl;
                archivo << item->getNombre() << std::endl;
                archivo << item->getDescripcion() << std::endl;
                archivo << ((Arma*)item)->getPuntosAtaque() << std::endl;
            }
            else if (dynamic_cast<Armadura*>(item)) {
                archivo << 3 << std::endl;
                archivo << item->getNombre() << std::endl;
                archivo << item->getDescripcion() << std::endl;
                archivo << ((Armadura*)item)->getDefensaExtra() << std::endl;
            }
        }

        archivo.close();
        vista.mostrarMensaje(">>> Progreso guardado exitosamente. <<<");
    } else {
        vista.mostrarMensaje("Error al guardar.");
    }
}
    void Controlador::cargarPartida(){

    std::ifstream archivo("savegame.txt");

    if (archivo.is_open()) {
        std::string nombreGuardado;
        std::string descripcionGuardada;
        std::string nombreHabitacion;
        int nivel, exp, hp, hpMax, atk, def;

        // Lectura segura para evitar errores de buffer:
        std::getline(archivo, nombreGuardado); // Nombre Héroe
        std::getline(archivo, descripcionGuardada);
        archivo >> nivel;
        archivo >> exp;
        archivo >> hp;
        archivo >> hpMax;
        archivo >> atk;
        archivo >> def;

        //UBICACIÓN
        // Después de leer 'def' (int), queda un \n en el buffer.
        // Si no lo borramos, el getline de la habitación lee vacío.
        archivo.ignore(1000, '\n');
        std::getline(archivo, nombreHabitacion);
        if (!nombreHabitacion.empty() && nombreHabitacion.back() == '\r') {
            nombreHabitacion.pop_back();
        }

        // Reconstruir Héroe
        if (heroe != nullptr) delete heroe;
        heroe = new Heroe(nombreGuardado, descripcionGuardada, hpMax, atk, def);
        heroe->setNivel(nivel);
        heroe->setExperiencia(exp);
        heroe->setPuntosDeVida(hp);

        // Restaurar Ubicación
        bool encontrada = false;
        for (Habitacion* hab : mapaGlobal) {
            if (hab->getNombre() == nombreHabitacion) {
                habitacionActual = hab;
                encontrada = true;
                break;
            }
        }

        if (!encontrada) {
            // Fallback de seguridad
            habitacionActual = mapaGlobal[0];
        }

        // 2. LEER INVENTARIO
        int cantidadItems;
        archivo >> cantidadItems;

        // === CORRECCIÓN 2: INVENTARIO ===
        // Después de leer la cantidad, limpiar el buffer antes de leer nombres de items
        archivo.ignore();

        for (int i = 0; i < cantidadItems; i++) {
            int tipo;
            std::string nombreItem;
            std::string descItem;
            int valor;

            // A. Leer TIPO
            archivo >> tipo;

            // === CORRECCIÓN 3: DENTRO DEL BUCLE ===
            // Después del número 'tipo', limpiar para leer 'nombreItem'
            archivo.ignore();

            // B. Leer TEXTOS
            std::getline(archivo, nombreItem);
            std::getline(archivo, descItem);

            // C. Leer VALOR
            archivo >> valor;
            // (Opcional) Limpiar si hubiera más cosas, pero el >> del siguiente 'tipo' se salta los espacios.

            // D. Crear Objeto
            Item* nuevoItem = nullptr;
            if (tipo == 1) nuevoItem = new Curativo(nombreItem, descItem, valor);
            else if (tipo == 2) nuevoItem = new Arma(nombreItem, descItem, valor);
            else if (tipo == 3) nuevoItem = new Armadura(nombreItem, descItem, valor);

            if (nuevoItem != nullptr) {
                heroe->agregarItemInventario(nuevoItem);
            }
        }

        archivo.close();
        vista.mostrarMensaje(">>> Partida cargada correctamente. ¡Bienvenido de nuevo, " + nombreGuardado + "! <<<");
    } else {
        vista.mostrarMensaje("No existe ningun archivo de guardado.");
    }
}
