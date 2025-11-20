//
// Created by jpfra on 11/11/25.
//

#include "Item.h"

// Constructor
Item::Item(std::string nombre, std::string descripcion, bool esConsumible)
    : nombre(nombre),
      descripcion(descripcion),
      esConsumible(esConsumible),
      probabilidadDrop(100)
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

int Item::getProbabilidadDrop() const {
    return probabilidadDrop;
}
