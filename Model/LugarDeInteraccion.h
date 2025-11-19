//
// Created by jpfra on 19/11/25.
//

#ifndef PROYECTOFINALPOO_LUGARDEINTERACCION_H
#define PROYECTOFINALPOO_LUGARDEINTERACCION_H


#include <string>
#include <iostream>

class Heroe; // Declaración adelantada, ya que la interacción modificará al Heroe

class LugarDeInteraccion {
protected:
    std::string nombre;
    std::string descripcion;
    bool usado = false; // Indica si el sitio ya fue interactuado (Cofre vacío, Altar usado)

public:
    // Constructor base
    LugarDeInteraccion(std::string nombre, std::string descripcion);

    // Destructor virtual: Siempre debe ser virtual en clases base
    virtual ~LugarDeInteraccion() = default;

    // ========= MeTODO PURO VIRTUAL =========
    // Este es el contrato: obliga a las subclases a implementar su lógica.
    // Recibe el héroe por referencia para modificar sus stats.
    virtual void ejecutarInteraccion(Heroe& heroe) = 0;

    // Metodos de utilidad
    std::string getNombre() const { return nombre; }
    bool isUsado() const { return usado; }
    void marcarComoUsado() { usado = true; }
};


#endif //PROYECTOFINALPOO_LUGARDEINTERACCION_H