cmake_minimum_required(VERSION 3.10)
project(JuegoRPG)

set(CMAKE_CXX_STANDARD 17)

# IMPORTANTE: Esto permite que tus archivos .cpp encuentren los .h
# aunque estén en carpetas diferentes (Model, View, Controller)
include_directories(Controller Model View)

add_executable(JuegoRPG
        main.cpp

        # Archivos del Controlador
        Controller/Controlador.cpp
        # Si tienes Controlador.h, no es obligatorio ponerlo aquí pero ayuda a organizarse

        # Archivos de la Vista
        View/Vista.cpp

        # Archivos del Modelo (Entidades e Items)
        Model/Entidad.cpp
        Model/Heroe.cpp
        Model/Guardia.cpp
        Model/Esqueleto.cpp
        Model/Jefe.cpp
        Model/Item.cpp
        Model/Arma.cpp
        Model/Armadura.cpp
        Model/Curativo.cpp
        Model/Habitacion.cpp
        Model/LugarDeInteraccion.cpp
)