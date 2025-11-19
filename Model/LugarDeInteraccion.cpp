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

  // Si ya se busco en el sitio, no hacemos nada mas
  if (this->usado) {
    std::cout << "No parece haber nada mas de interes aqui." << std::endl;
    return;
  }

  // 1. Lógica si hay un Item
  if (this->itemOculto != nullptr) {
    std::cout << "¡Encontraste un objeto: " << itemOculto->getNombre() << "!" << std::endl;
    heroe.agregarItemInventario(itemOculto);

    // IMPORTANTE: El héroe ahora es dueño del item.
    // Ponemos el puntero a nullptr para que el destructor de LugarDeInteraccion no lo borre por error.
    this->itemOculto = nullptr;
    this->usado = true; // Un solo uso para evitar...abusoooo
  }

  // 2. Lógica si hay Curación
  if (this->puntosDeCuracion > 0) {
    std::cout << "Sientes una energia revitalizante." << std::endl;
    heroe.curarse(this->puntosDeCuracion);
    this->usado = true; // Los altares se agotan
  }

  // 3. Si no había nada (bromita)
  if (this->itemOculto == nullptr && this->puntosDeCuracion == 0) {
    std::cout << "Paila, al parecer no hay nada aqui." << std::endl;
    // No lo volvemos usado para que el mensaje pueda seguir apareciendo indefinidamente.
  }
}
