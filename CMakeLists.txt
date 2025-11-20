cmake_minimum_required(VERSION 3.10)
project(JuegoRPG)

set(CMAKE_CXX_STANDARD 17)

# IMPORTANTE: Esto permite quelos .cpp encuentren los .h aunque estén en carpetas diferentes
include_directories(Controller Model View)

add_executable(JuegoRPG
        main.cpp

        # Archivos del Controlador
        Controller/Controlador.cpp

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