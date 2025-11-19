//
// Created by jpfra on 14/11/25.
//

#include "Habitacion.h"
#include <algorithm> // Usado para std::find y std::remove_if
#include "Heroe.h"
#include "Item.h"

// ======================= CONSTRUCTOR Y DESTRUCTOR =========================

Habitacion::Habitacion(std::string nombre, std::string descripcion, int nivel)
    : nombre(nombre),
      descripcion(descripcion),
      nivel(nivel)
{
    // Los vectores y mapas se inicializan vacíos automáticamente
}


// Debe liberar la memoria de los punteros que "posee" (enemigos e interacciones).
Habitacion::~Habitacion() {
    // 1. Liberar la memoria de los enemigos
    for (Entidad* enemigo : enemigos) {
        delete enemigo;
    }
    enemigos.clear();

    // 2. Liberar la memoria de los LugaresDeInteraccion
    for (LugarDeInteraccion* lugar : interacciones) {
        delete lugar;
    }
    interacciones.clear();

    // NOTA: Los punteros a otras Habitaciones (salidas) NO se liberan aquí.
}

// ======================= MÉTODOS DE GESTIÓN DE JUEGO =========================

void Habitacion::agregarSalida(const std::string& direccion, Habitacion* destino) {
    // Añade la dirección (clave) y la habitación (valor) al mapa
    salidas[direccion] = destino;
}

void Habitacion::agregarEnemigo(Entidad* enemigo) {
    enemigos.push_back(enemigo); //Se usa el push back para meter enemigos al vector almacenador
}

void Habitacion::agregarInteraccion(LugarDeInteraccion* lugar) {
    interacciones.push_back(lugar);  //Se usa el push back para meter lugares de interaccion al lugar
}

void Habitacion::removerEnemigo(Entidad* enemigo) {
    // Usa std::remove y std::vector::erase para eliminar el puntero del vector
    auto it = std::remove(enemigos.begin(), enemigos.end(), enemigo); //Recorre desde el inicio al final del vector enemigos, revisando cada enemigo adentro
    //Aparte, mueve los enemigos que siguen vivos adelante en el vector para evitar huecos
    enemigos.erase(it, enemigos.end()); //it es un puntero que apunta al enemigo muerto que debe ser removido
}


// ======================= MOVIMIENTOS =========================

Habitacion* Habitacion::getSalida(const std::string& direccion) const {
    // Busca la dirección en el mapa
    auto it = salidas.find(direccion);

    // Si la dirección existe, devuelve el puntero a la Habitación; si no, devuelve nullptr.
    if (it != salidas.end()) {
        return it->second; // Retorna el puntero a la Habitacion
    }
    return nullptr;
}

bool Habitacion::estaDespejada() const {
    // La sala está despejada si no quedan enemigos
    return enemigos.empty();
}

bool Habitacion::interactuarCon(const std::string& nombreLugar, Heroe& heroe) {

    // Busca el lugar usando un bucle simple (ya no necesitamos manejar el borrado)
    for (LugarDeInteraccion* lugar : interacciones) {

        if (lugar->getNombre() == nombreLugar) {

            // Se encontró el lugar. Ejecuta la interacción.
            // La lógica para no dar loot si 'isUsado' es true DEBE estar dentro de este metodo
            lugar->ejecutarInteraccion(heroe);

            // El puntero permanece en el vector 'interacciones'.
            return true; // Interacción encontrada y ejecutada
        }
    }
    return false; // Lugar no encontrado
}

// ======================= GETTERS =========================

std::string Habitacion::getNombre() const {
    return nombre;
}

std::string Habitacion::getDescripcion() const {
    return descripcion;
}

int Habitacion::getNivel() const {
    return nivel;
}

const std::vector<Entidad*>& Habitacion::getEnemigos() const {
    return enemigos;
}

const std::map<std::string, Habitacion*>& Habitacion::getSalidas() const {
    return salidas;
}
