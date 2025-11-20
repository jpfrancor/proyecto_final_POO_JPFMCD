cmake_minimum_required(VERSION 3.10)
project(JuegoRPG)

set(CMAKE_CXX_STANDARD 17)

# Aquí le decimos a CLion que cree un ejecutable llamado "JuegoRPG"
# usando TODOS tus archivos .cpp
add_executable(JuegoRPG
        main.cpp
        Controlador.cpp
        Vista.cpp
        Entidad.cpp
        Heroe.cpp
        Guardia.cpp
        Esqueleto.cpp
        Jefe.cpp
        Item.cpp
        Arma.cpp
        Armadura.cpp
        Curativo.cpp
        Habitacion.cpp
        LugarDeInteraccion.cpp
)