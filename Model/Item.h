//
// Created by jpfra on 11/11/25.
//

#ifndef PROYECTOFINALPOO_ITEM_H
#define PROYECTOFINALPOO_ITEM_H

#include <string>
#include <iostream>

#include "Entidad.h"

class Item {
protected:
    // Atributos base que comparten todos los objetos
    std::string nombre;
    std::string descripcion;
    bool esConsumible; // Para saber si se elimina del inventario después de usarlo.

public:
    // Constructor
    Item(std::string nombre, std::string descripcion, bool esConsumible);

    // Destructor virtual
    virtual ~Item() = default;

    // Metodo abstracto (puro virtual) clave del diseño:
    // Define el efecto del ítem. Fuerza a las subclases a implementarlo.
    // Recibe un puntero a Entidad (el Heroe) para modificar sus stats.
    virtual void funcion(Entidad* objetivo) = 0;

    // ======================= GETTERS =========================

    std::string getNombre() const;
    std::string getDescripcion() const;
    int getValor() const;
    bool getEsConsumible() const;
};


#endif //PROYECTOFINALPOO_ITEM_H