//
// Created by jpfra on 11/11/25.
//

#ifndef PROYECTOFINALPOO_ENTIDAD_H
#define PROYECTOFINALPOO_ENTIDAD_H

#include <iostream>

class Entidad {
protected:
    std::string nombre;
    int puntosDeVida;
public:
    Personaje(std::string nombre);
    Personaje(std::string nombre, int puntosDeVida);
    virtual ~Personaje() = default;

    virtual void atacar(Personaje& objetivo) const = 0;

    void recibirDanio(int danio);

    int getPuntosDeVida();

    std::string getNombre() const;
};

#endif //PROYECTOFINALPOO_ENTIDAD_H