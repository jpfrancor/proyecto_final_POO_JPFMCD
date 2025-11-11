//
// Created by jpfra on 11/11/25.
//

#ifndef PROYECTOFINALPOO_ENTIDAD_H
#define PROYECTOFINALPOO_ENTIDAD_H

#include <iostream>
#include <vector>
#include <string>

#include "Item.h" //Se incluye el item para que el programa sepa que se utiliza

class Entidad {
protected: //Van con protectec para que sólo los hijos puedan acceder a estos atributos
    //Atributos privados
    std::string nombre;
    std::string descripcion;
    int puntosDeVida;
    int ataque;
    int defensa;

    //Atributo inventario, usa un puntero al Item
    std::vector<Item*> inventario;
public:
    //Constructor
    Entidad(std::string nombre, std::string descripcion, int hp, int atk, int def);

    //Destructor virtual
    virtual ~Entidad() = default;

    //Ataques, serán modificados para cada clase heredada. Como Pokémon.
    virtual void movimiento1() = 0;
    virtual void movimiento2() = 0;
    virtual void movimiento3() = 0;
    virtual void movimiento4() = 0;

    //Se crea virtual ya que el héroe muere de forma distinta a los enemigos (los cuales botan objetos)
    virtual void morir(Heroe* heroe);

    //Metodo para añadir objetos al inventario de la entidad
    void agregarItemInventario(Item* item);

// ======================= GETTERS =========================

    std::string getNombre() const; // Se agrega const para que lo traiga sin modificarlo
    std::string getDescripcion() const;
    int getPuntosDeVida() const; // Se agrega const para que lo traiga sin modificarlo
    int getAtaque() const; // Se agrega const para que lo traiga sin modificarlo
    int getDefensa() const; // Se agrega const para que lo traiga sin modificarlo
};

#endif //PROYECTOFINALPOO_ENTIDAD_H