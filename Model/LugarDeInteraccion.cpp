//
// Created by jpfra on 19/11/25.
//

#include "LugarDeInteraccion.h"

// Constructor
LugarDeInteraccion::LugarDeInteraccion(std::string nombre, std::string descripcion, Item* item, int vida)
    : nombre(nombre), descripcion(descripcion), usado(false), itemOculto(item), puntosDeCuracion(vida) {
}

// Destructor
LugarDeInteraccion::~LugarDeInteraccion() {
  if (itemOculto != nullptr) {
    delete itemOculto; //Tambien se borra el objeto interno para evitar fugas de memoria
  }
}

void LugarDeInteraccion::ejecutarInteraccion(Heroe& heroe) {
  std::cout << "Interactuas con " << this->nombre << "..." << std::endl;
  std::cout << this->descripcion << std::endl;

  // Si ya se usó el sitio
  if (this->usado) {
    std::cout << "Ya no queda nada util aqui." << std::endl;
    return; // <--- IMPORTANTE: Salir aquí
  }

  // Si hay un Item
  if (this->itemOculto != nullptr) {
    std::cout << "¡Encontraste un objeto: " << itemOculto->getNombre() << "!" << std::endl;
    heroe.agregarItemInventario(itemOculto);

    this->itemOculto = nullptr;
    this->usado = true;
    return; // <--- AGREGA ESTO: Si encontró algo, termina la función YA.
  }

  // Si hay Curación
  if (this->puntosDeCuracion > 0) {
    std::cout << "Sientes una energia revitalizante." << std::endl;
    heroe.curarse(this->puntosDeCuracion);

    this->usado = true;
    return; // <--- AGREGA ESTO: Si curó, termina la función YA.
  }

  // Esto solo aparece si no hay NADA mas en el lugar
  std::cout << "Paila, al parecer no hay nada aqui." << std::endl;
}
