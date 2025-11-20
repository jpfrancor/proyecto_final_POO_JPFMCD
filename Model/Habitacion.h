//
// Created by jpfra on 14/11/25.
//

#ifndef PROYECTOFINALPOO_HABITACION_H
#define PROYECTOFINALPOO_HABITACION_H


#include <string>
#include <vector>
#include <map> // Necesario para std::map
#include "Entidad.h" // Para los enemigos de la habitación
#include "LugarDeInteraccion.h" // Para los "sitios buscables"

class Habitacion {
private:
    std::string nombre;
    std::string descripcion;
    int nivel; // Nivel del calabozo (1 al 5)

    std::vector<Entidad*> enemigos; //Vector que guarda los enemigos presentes en la sala

    std::vector<LugarDeInteraccion*> interacciones; //Vector que guarda los puntos de interaccion en la sala

    // Topología del calabozo: Asocia una dirección ("Norte") con otra Habitacion.
    std::map<std::string, Habitacion*> salidas;

public:
    // Constructor
    Habitacion(std::string nombre, std::string descripcion, int nivel);

    // Destructor virtual: Necesario para limpiar la memoria de enemigos e interacciones
    virtual ~Habitacion();

    // --- MÉTODOS DE GESTIÓN DE JUEGO ---

    // Añade una conexión de salida
    void agregarSalida(const std::string& direccion, Habitacion* destino); //Se necesita una direccion para saber a donde moverse, el destino es la habitacion a la que se apunta para llegar

    // Añade un enemigo a la habitación
    void agregarEnemigo(Entidad* enemigo);

    // Añade un punto de interés o "sitio buscable"
    void agregarInteraccion(LugarDeInteraccion* lugar);

    // Elimina un enemigo de la sala (llamado después de que muere)
    void removerEnemigo(Entidad* enemigo);

    // --- MÉTODOS DE CONSULTA Y NAVEGACIÓN ---

    // Devuelve la habitación destino para una dirección dada
    Habitacion* getSalida(const std::string& direccion) const;

    // Devuelve si la sala está despejada de enemigos
    bool estaDespejada() const;

    // Lógica para que el héroe interactúe con un "sitio buscable"
    bool interactuarCon(const std::string& nombreLugar, Heroe& heroe);

    // --- GETTERS ---

    std::string getNombre() const;
    std::string getDescripcion() const;
    int getNivel() const;
    const std::vector<Entidad*>& getEnemigos() const;
    const std::map<std::string, Habitacion*>& getSalidas() const;
    const std::vector<LugarDeInteraccion*>& getInteracciones() const;
};


#endif //PROYECTOFINALPOO_HABITACION_H