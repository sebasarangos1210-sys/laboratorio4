#include "router.h"
#include <iostream>
#include <algorithm>
#include <limits>

// Constructor
Router::Router(const string& id)
    : id(id), neighbors(), dist(), prev() {}

// Obtener identificador
string Router::getId() const {
    return id;
}

// Añadir vecino
void Router::addNeighbor(const string& neighborId, int cost) {
    neighbors.emplace_back(neighborId, cost);
}

// Eliminar vecino
void Router::removeNeighbor(const string& neighborId) {
    neighbors.erase
        (
            std::remove_if
            (
                neighbors.begin(),
                neighbors.end(),
                [&](const pair<string,int>& p) { return p.first == neighborId; }
                ),
            neighbors.end()
            );
}

// Obtener lista de vecinos
const vector<pair<string,int>>& Router::getNeighbors() const {
    return neighbors;
}

// Configurar datos tras cálculo de rutas
void Router::setRoutingData(map<string,int> distances,
                            map<string,string> predecessors) {
    dist = std::move(distances);
    prev = std::move(predecessors);
}

// Obtener distancia mínima a un destino
int Router::getDistance(const string& destination) const {
    auto it = dist.find(destination);
    if (it != dist.end()) {
        return it->second;
    }
    return -1; // Indica destino inalcanzable o no existente
}

// Reconstruir ruta hasta un destino
vector<string> Router::getPath(const string& destination) const {
    vector<string> path;
    // Si no existe registro de dist o prev, ruta vacía
    if (dist.find(destination) == dist.end()) {
        return path;
    }
    string curr = destination;
    // Retroceder usando prev hasta el origen (id)
    while (curr != id) {
        path.push_back(curr);
        auto it = prev.find(curr);
        if (it == prev.end()) {
            // No hay camino completo
            path.clear();
            return path;
        }
        curr = it->second;
    }
    path.push_back(id);
    std::reverse(path.begin(), path.end());
    return path;
}

// Acceso directo a mapas completos
const map<string,int>& Router::getDistances() const {
    return dist;
}

const map<string,string>& Router::getPredecessors() const {
    return prev;
}

// Imprimir vecinos
void Router::printNeighbors() const {
    std::cout << "Vecinos del router " << id << ":\n";
    for (const auto& p : neighbors) {
        std::cout << "  " << p.first << " (costo: " << p.second << ")\n";
    }
}

// Imprimir tabla de enrutamiento
void Router::printRoutingTable() const {
    const int INF = std::numeric_limits<int>::max();
    std::cout << "Tabla de enrutamiento para enrutador " << id << ":\n";
    std::cout << "Destino\tCosto\tNextHop\n";
    for (const auto& entry : dist) {
        const string& dest = entry.first;
        int cost = entry.second;
        // 1) Mostrar costo o “infinito”
        if (cost == INF) {
            std::cout << dest << "\t" << "infinito";
        } else {
            std::cout << dest << "\t" << cost;
        }
        // 2) Mostrar NextHop o “-”
        std::cout << "\t";
        auto it = prev.find(dest);
        if (it != prev.end() && cost != INF) {
            std::cout << it->second;
        } else {
            std::cout << "-";
        }
        std::cout << "\n";
    }
}
