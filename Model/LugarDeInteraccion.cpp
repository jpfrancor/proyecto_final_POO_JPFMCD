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
  std::cout << "\nInteractuas con " << this->nombre << "..." << std::endl;
  std::cout << this->descripcion << std::endl; // <--- AQUÍ SE MUESTRA EL MENSAJE DE LORE

  // Si ya se usó
  if (this->usado) {
    std::cout << "(Ya has tomado todo lo util de aqui)" << std::endl;
    return;
  }

  // Lógica si hay un Item
  if (this->itemOculto != nullptr) {
    std::cout << "¡Encontraste un objeto: " << itemOculto->getNombre() << "!" << std::endl;
    heroe.agregarItemInventario(itemOculto);

    this->itemOculto = nullptr;
    this->usado = true; // Marcamos como usado para que no de items infinitos
    return;
  }

  // Lógica si hay Curación
  if (this->puntosDeCuracion > 0) {
    // Verificamos si vale la pena curarse
    if (heroe.getPuntosDeVida() < heroe.getPuntosDeVidaMax()) {
      std::cout << "Sientes una energia revitalizante." << std::endl;
      heroe.curarse(this->puntosDeCuracion);
      this->usado = true; // La fuente se agota
    } else {
      std::cout << "Te sientes lleno de energia, mejor guardar esto para luego." << std::endl;
    }
    return;
  }

  // SI LLEGAMOS AQUÍ, ES UN LUGAR DE SOLO TEXTO
  // No imprimimos nada.
}
