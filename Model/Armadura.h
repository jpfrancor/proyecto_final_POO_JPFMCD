//
// Created by marti on 19/11/2025.
//

#ifndef ARMADURA_H
#define ARMADURA_H

#include "Item.h"

class Armadura : public Item {
private:
    int defensaExtra;

public:
    // Asegúrate que pida 3 cosas:
    Armadura(std::string nombre, std::string descripcion, int defensa);

    void usar(Entidad* usuario) override;

    int getDefensaExtra() const { return defensaExtra; }
};

#endif
