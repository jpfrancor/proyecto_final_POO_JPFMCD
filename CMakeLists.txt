cmake_minimum_required(VERSION 4.0)
project(proyectoFinalPOO)

set(CMAKE_CXX_STANDARD 20)

add_executable(proyectoFinalPOO main.cpp
        Model/Entidad.cpp
        Model/Entidad.h
        Model/Item.cpp
        Model/Item.h
        Model/Heroe.cpp
        Model/Heroe.h
        Model/Habitacion.cpp
        Model/Habitacion.h
)
