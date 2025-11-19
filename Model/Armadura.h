//
// Created by marti on 19/11/2025.
//

#ifndef PROYECTO_FINAL_POO_JPFMCD_ARMADURA_H
#define PROYECTO_FINAL_POO_JPFMCD_ARMADURA_H

#include "Item.h"
#include <string>
#include "entidad.h"


class Armadura : public Item {
private:
    int defensaAdicional; // La cantidad de defensa que suma

public:
    // Constructor
    Armadura(std::string nombre, int defensaExtra);

    // Sobrescritura del método usar (definido en Item.h)
    void usar(Entidad* objetivo) override;

    // Getter
    int getDefensaAdicional() const;
};




#endif //PROYECTO_FINAL_POO_JPFMCD_ARMADURA_H