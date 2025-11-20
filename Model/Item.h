#ifndef PROYECTOFINALPOO_ITEM_H
#define PROYECTOFINALPOO_ITEM_H

#include <string>
#include <iostream>
// BORRA EL #include "Entidad.h" DE AQUÍ SI LO TIENES

// AGREGA ESTO (Forward Declaration):
class Entidad;

class Item {
protected:
    std::string nombre;
    std::string descripcion;
    bool esConsumible;

public:
    Item(std::string nombre, std::string descripcion, bool esConsumible);
    virtual ~Item() = default;

    // Ahora el compilador ya no llorará aquí
    virtual void usar(Entidad* objetivo) = 0;

    // Getters...
    std::string getNombre() const;
    std::string getDescripcion() const;
    bool getEsConsumible() const;
    int getValor() const;
};

#endif //PROYECTOFINALPOO_ITEM_H