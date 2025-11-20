//
// Created by jpfra on 19/11/25.
//

#ifndef PROYECTOFINALPOO_ARMA_H
#define PROYECTOFINALPOO_ARMA_H


#include "Item.h"
#include "Entidad.h"
#include <string>

// Heredamos de Item
class Arma : public Item {
private:
    int puntosDeAtaque; // Cuánto daño añade esta arma

public:
    // Constructor simplificado para coincidir con "new Arma(nombre, daño)"
    Arma(std::string nombre, std::string descripcion, int danio);

    // Sobrescribimos el metodo usar (asegúrate de haber cambiado 'funcion' por 'usar' en Item.h)
    void usar(Entidad* objetivo) override;

    //Getter
    int getPuntosAtaque() const { return puntosDeAtaque; }
};

#endif //PROYECTOFINALPOO_ARMA_H