#include "menu.h"
#include <iostream>
#include <limits>

int showRangoMenu(int min, int max)
{
    int input = -1;
    bool inputValido = false;

    do {
        std::cout << "Ingrese 0 para salir, o un numero entre "
                  << min << " y " << max << ": " << std::endl;

        if (!(std::cin >> input)) {

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
                );
            std::cout << "Entrada no valida. Intente nuevamente." << std::endl;
        }
        else if (input == 0 || (input >= min && input <= max)) {

            inputValido = true;
        }
        else {
            std::cout << "Opcion fuera de rango. Intente nuevamente." << std::endl;
        }
    } while (!inputValido);

    return input;
}

int showMainMenu() {
    std::cout << "1 : Gestionar topologia"            << std::endl;
    std::cout << "2 : Consultar rutas/costos"          << std::endl;
    std::cout << "3 : Generar topologia aleatoria"     << std::endl;
    std::cout << "4 : Imprimir red completa"           << std::endl;
    std::cout << "0 : Salir"                           << std::endl;
    return showRangoMenu(1,4);
}




int showTopologyMenu() {
    std::cout << "1 : Cargar topologia desde archivo" << std::endl;
    std::cout << "2 : Agregar nodo"                   << std::endl;
    std::cout << "3 : Eliminar nodo"                  << std::endl;
    std::cout << "4 : Agregar enlace"                 << std::endl;
    std::cout << "5 : Eliminar enlace"                << std::endl;
    std::cout << "0 : Volver al menu principal"       << std::endl;
    return showRangoMenu(1,5);
}


int showQueryMenu() {
    std::cout << "1 : Mostrar tabla de enrutamiento de un nodo" << std::endl;
    std::cout << "2 : Consultar costo minimo entre dos nodos"   << std::endl;
    std::cout << "3 : Mostrar camino minimo entre dos nodos"   << std::endl;
    std::cout << "0 : Volver al menu principal"                 << std::endl;
    return showRangoMenu(1,3);
}
