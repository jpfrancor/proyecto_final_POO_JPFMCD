//
// Created by jpfra on 11/11/25.
//

#ifndef PROYECTOFINALPOO_ENTIDAD_H
#define PROYECTOFINALPOO_ENTIDAD_H

#include <string>
#include <vector>
#include <iostream>

// Forward Declarations (La solución mágica)
class Item;
class Heroe;

class Entidad {
protected: //Van con protectec para que sólo los hijos puedan acceder a estos atributos
    //Atributos privados
    std::string nombre;
    std::string descripcion;
    int puntosDeVidaMax;
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
    virtual void movimiento1(Entidad& objetivo) = 0;

    //Se crea virtual ya que el héroe muere de forma distinta a los enemigos (los cuales botan objetos)
    virtual void morir(Heroe& heroe);

    //Metodo para añadir objetos al inventario de la entidad
    void agregarItemInventario(Item* item); //Esto es un pushback

    void recibirDanio(int cantidad);

    void modificarEstadisticas(int hp, int atk, int def);

    void eliminarItem(int indice);

    // Getters
    std::string getNombre() const;
    std::string getDescripcion() const;
    int getPuntosDeVida() const;
    int getAtaque() const;
    int getDefensa() const;
    int getPuntosDeVidaMax() const;
    const std::vector<Item*>& getInventario() const;
};

#endif //PROYECTOFINALPOO_ENTIDAD_H