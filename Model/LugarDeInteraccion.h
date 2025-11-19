//
// Created by jpfra on 19/11/25.
//

#ifndef PROYECTOFINALPOO_LUGARDEINTERACCION_H
#define PROYECTOFINALPOO_LUGARDEINTERACCION_H


#include <string>
#include <iostream>
#include "Heroe.h"




#include <string>
#include <iostream>
#include "Heroe.h"
#include "Item.h"

class LugarDeInteraccion {
protected:
    std::string nombre;
    std::string descripcion;
    bool usado;

    // Atributos opcionales (La "Navaja Suiza")
    Item* itemOculto;      // Si es nullptr, no hay item.
    int puntosDeCuracion;  // Si es 0, no cura.

public:
    // Constructor Único con valores por defecto
    // Si no pasas item ni vida, es solo un sitio para "mirar" (ej. un cartel).
    LugarDeInteraccion(std::string nombre, std::string descripcion, Item* item = nullptr, int vida = 0);

    virtual ~LugarDeInteraccion();

    // YA NO ES VIRTUAL PURA (= 0). Ahora tiene código.
    virtual void ejecutarInteraccion(Heroe& heroe);

    std::string getNombre() const { return nombre; }
    bool isUsado() const { return usado; }
};

#endif //PROYECTOFINALPOO_LUGARDEINTERACCION_H