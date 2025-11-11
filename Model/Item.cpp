//
// Created by jpfra on 11/11/25.
//

#include "Item.h"

// Constructor
Item::Item(std::string nombre, std::string descripcion, bool esConsumible)
    : nombre(nombre),
      descripcion(descripcion),
      esConsumible(esConsumible)
{
    // Cuerpo vacío: tutti se inicializa en la lista de inicialización
}

// ======================= GETTERS =========================

std::string Item::getNombre() const {
    return nombre;
}

std::string Item::getDescripcion() const {
    return descripcion;
}

bool Item::getEsConsumible() const {
    return esConsumible;
}

// NOTA: No incluimos Entidad.h aquí, ya que el metodo funcion() es abstracto y
// no se implementa en la clase base.

// NOTA: El metodo funcion(Entidad* objetivo) NO se implementa aquí,
// ya que es un metodo puro virtual (= 0). La implementación se deja
// a las clases hijas (Curativo, Arma, Armadura).//