#include "mainmenu.h"
#include "network.h"
#include "menu.h"
#include <iostream>

int main() {

    Network net;
    int op;
    while ((op = showMainMenu()) != 0)
    {
        switch (op)
        {
        case 1: flowTopology(net);           break;
        case 2: flowQuery(net);              break;
        case 3:
        {
            int n = readInt("Número de routers: ");
            int m = readInt("Número de enlaces: ");
            int maxC = readInt("Costo máximo de enlace: ");

            net.generateRandomTopology(n, m, maxC);
            std::cout << "Topología aleatoria generada.\n";
            break;
        }
        case 4:
        {
            net.printTopologyFile();      // Primero los enlaces
            net.printAllRouters();        // Luego vecinos y tablas
            break;
        }
        }
    }
    return 0;
}
