#include <iostream>
// En main.cpp (o donde inicialices el Controlador)
#include <cstdlib> // Para srand()
#include <ctime>   // Para time()

int main() {
    srand(time(nullptr));
    std::cout << "Hello, World!" << std::endl;
    return 0;
}