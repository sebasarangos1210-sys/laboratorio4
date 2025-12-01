#include "mainmenu.h"
#include "menu.h"
#include "network.h"
#include "router.h"
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
        case 1: {
            cout << "Archivo de topología: ";
            string fname;
            cin >> fname;
            if (!net.loadFromFile(fname))
                cout << "Error cargando: " << fname << "\n";
            else
                cout << "Topología cargada exitosamente.\n";
            break;
        }
        case 2: {
            cout << "ID nuevo router: ";
            string id;
            cin >> id;
            if (!net.addRouter(id))
                cout << "El router ya existe.\n";
            else
                cout << "Router agregado: " << id << "\n";
            break;
        }
        case 3: {
            cout << "ID router a eliminar: ";
            string id;
            cin >> id;
            if (!net.removeRouter(id))
                cout << "No existe ese router.\n";
            else
                cout << "Router eliminado: " << id << "\n";
            break;
        }
        case 4: {
            cout << "Router origen, destino y costo: ";
            string a, b;
            int cost;
            cin >> a >> b >> cost;
            if (!net.addLink(a, b, cost))
                cout << "Error al agregar enlace.\n";
            else
                cout << "Enlace agregado: " << a << " <-> " << b << " (costo: " << cost << ")\n";
            break;
        }
        case 5: {
            cout << "Router origen y destino: ";
            string a, b;
            cin >> a >> b;
            if (!net.removeLink(a, b))
                cout << "Error al eliminar enlace.\n";
            else
                cout << "Enlace eliminado: " << a << " <-> " << b << "\n";
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
        case 1: {
            cout << "ID del router: ";
            string id;
            cin >> id;
            const Router* r = net.getRouter(id);
            if (r) {
                r->printRoutingTable();
            } else {
                cout << "Router no encontrado.\n";
            }
            break;
        }
        case 2: {
            cout << "Origen y Destino: ";
            string s, d;
            cin >> s >> d;
            int c = net.queryMinCost(s, d);
            if (c >= 0) {
                cout << "Costo mínimo " << s << " -> " << d << " = " << c << "\n";
            } else {
                cout << "Ruta no disponible.\n";
            }
            break;
        }
        case 3: {
            cout << "Origen y Destino: ";
            string s, d;
            cin >> s >> d;
            auto path = net.queryPath(s, d);
            if (!path.empty()) {
                cout << "Ruta: ";
                for (size_t i = 0; i < path.size(); i++) {
                    cout << path[i];
                    if (i < path.size() - 1) cout << " -> ";
                }
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
            return x;
        }
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "  Entrada inválida. Por favor, ingresa un número entero.\n";
    }
}
