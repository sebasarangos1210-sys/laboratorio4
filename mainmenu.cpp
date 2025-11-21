#include "mainmenu.h"
#include "menu.h"          // showMainMenu, showTopologyMenu, showQueryMenu
#include "network.h"
#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::string;

// --- Flujo Topología ---
int flowTopology(Network &net)
{
    int op;
    while ((op = showTopologyMenu()) != 0)
    {
        switch (op)
        {
        case 1: {  // Cargar desde archivo
            cout << "Archivo de topologia: ";
            string fname; cin >> fname;
            if (!net.loadFromFile(fname))
                cout << "Error cargando: " << fname << "\n";
            break;
        }
        case 2: {  // Agregar router
            cout << "ID nuevo router: ";
            string id; cin >> id;
            if (!net.addRouter(id))
                cout << "El router ya existe.\n";
            break;
        }
        case 3: {  // Eliminar router
            cout << "ID router a eliminar: ";
            string id; cin >> id;
            if (!net.removeRouter(id))
                cout << "No existe ese router.\n";
            break;
        }
        case 4: {  // Agregar enlace
            cout << "Router origen, destino y costo: ";
            string a, b; int cost;
            cin >> a >> b >> cost;
            if (!net.addLink(a, b, cost))
                cout << "Error al agregar enlace.\n";
            break;
        }
        case 5: {  // Eliminar enlace
            cout << "Router origen y destino: ";
            string a, b;
            cin >> a >> b;
            if (!net.removeLink(a, b))
                cout << "Error al eliminar enlace.\n";
            break;
        }
        }
    }
    return 0;
}

// --- Flujo Consulta ---
int flowQuery(Network &net)
{
    int op;
    while ((op = showQueryMenu()) != 0)
    {
        switch (op)
        {
        case 1: {  // Mostrar tabla de un router
            cout << "ID del router: ";
            string id; cin >> id;
            const Router* r = net.getRouter(id);
            if (r) r->printRoutingTable();
            else  cout << "Router no encontrado.\n";
            break;
        }
        case 2: {  // Consultar costo mínimo
            cout << "Origen y Destino: ";
            string s, d; cin >> s >> d;
            int c = net.queryMinCost(s, d);
            if (c >= 0) cout << "Costo min " << s << "→" << d << " = " << c << "\n";
            else        cout << "Ruta no disponible.\n";
            break;
        }
        case 3: {  // Mostrar camino mínimo
            cout << "Origen y Destino: ";
            string s, d; cin >> s >> d;
            auto path = net.queryPath(s, d);
            if (!path.empty()) {
                cout << "Ruta: ";
                for (auto& hop : path) cout << hop << " ";
                cout << "\n";
            } else {
                cout << "Ruta no disponible.\n";
            }
            break;
        }
        }
    }
    return 0;
}

int readInt(const string &prompt) {
    int x;
    while (true) {
        cout << prompt;
        cin >> x;
        if (!cin.fail()) {
            // lectura correcta
            return x;
        }
        // lectura fallida: limpia error y descarta la entrada inválida
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "  Entrada inválida. Por favor, ingresa un número entero.\n";
    }
}
