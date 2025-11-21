#include "network.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <limits>
#include <set>

using std::ifstream;
using std::string;
using std::vector;
using std::map;
using std::pair;

// Constructor: inicializa semilla para generar topologías aleatorias
Network::Network() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

// Destructor: libera todos los routers
Network::~Network() {
    clearTopology();
}

// Elimina todos los routers y limpia la topología
void Network::clearTopology() {
    for (auto &p : routers) {
        delete p.second;
    }
    routers.clear();
    adjList.clear();
}

// Reconstruye lista de adyacencia a partir de los vecinos de cada router
void Network::buildAdjacency() {
    adjList.clear();
    for (const auto &p : routers) {
        const string &id = p.first;
        const auto &neis = p.second->getNeighbors();
        adjList[id] = neis;
    }
}

// Carga topologia desde un fichero con formato: origen destino costo
bool Network::loadFromFile(const string &filename) {

    ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Error al abrir archivo: " << filename << std::endl;
        return false;
    }
    clearTopology();
    string id1, id2;
    int cost;
    while (in >> id1 >> id2 >> cost) {
        if (routers.find(id1) == routers.end()) addRouter(id1);
        if (routers.find(id2) == routers.end()) addRouter(id2);
        routers[id1]->addNeighbor(id2, cost);
        routers[id2]->addNeighbor(id1, cost);
    }
    in.close();
    updateAllRoutingTables();
    return true;
}

// Añade un router con ID único
bool Network::addRouter(const string &routerId) {
    if (routers.find(routerId) != routers.end()) return false;
    routers[routerId] = new Router(routerId);
    updateAllRoutingTables();
    return true;
}

// Elimina un router y todos sus enlaces
bool Network::removeRouter(const string &routerId) {
    auto it = routers.find(routerId);
    if (it == routers.end()) return false;
    delete it->second;
    routers.erase(it);
    // Quitar enlaces al router eliminado
    for (auto &p : routers) {
        p.second->removeNeighbor(routerId);
    }
    updateAllRoutingTables();
    return true;
}

// Añade un enlace bidireccional entre dos routers existentes
bool Network::addLink(const string &id1, const string &id2, int cost) {
    auto it1 = routers.find(id1);
    auto it2 = routers.find(id2);
    if (it1 == routers.end() || it2 == routers.end()) return false;
    it1->second->addNeighbor(id2, cost);
    it2->second->addNeighbor(id1, cost);
    updateAllRoutingTables();
    return true;
}

// Elimina un enlace bidireccional entre dos routers
bool Network::removeLink(const string &id1, const string &id2) {
    auto it1 = routers.find(id1);
    auto it2 = routers.find(id2);
    if (it1 == routers.end() || it2 == routers.end()) return false;
    it1->second->removeNeighbor(id2);
    it2->second->removeNeighbor(id1);
    updateAllRoutingTables();
    return true;
}

// Genera una topología aleatoria con N routers y M enlaces
void Network::generateRandomTopology(int numRouters, int numLinks, int maxCost) {
    clearTopology();
    // Crear routers R1, R2, ...
    for (int i = 1; i <= numRouters; ++i) {
        addRouter("R" + std::to_string(i));
    }
    // Lista de IDs para muestreo
    vector<string> ids;
    for (const auto &p : routers) ids.push_back(p.first);
    int possible = ids.size() * (ids.size() - 1) / 2;
    int m = std::min(numLinks, possible);
    int count = 0;
    while (count < m) {
        int i = std::rand() % ids.size();
        int j = std::rand() % ids.size();
        if (i == j) continue;
        const string &a = ids[i];
        const string &b = ids[j];
        // Verificar que no exista ya
        bool exists = false;
        for (auto &pr : routers[a]->getNeighbors()) {
            if (pr.first == b) { exists = true; break; }
        }
        if (exists) continue;
        int cost = std::rand() % maxCost + 1;
        // Usar addLink para recalcular tablas
        addLink(a, b, cost);
        ++count;
    }
}



void Network::printTopologyFile() const {
    std::cout << "Enlaces de la red (Origen Destino Coste):\n";
    // Evitamos imprimir cada enlace dos veces usando u < v
    for (const auto &p : adjList) {
        const auto &u = p.first;
        for (const auto &edge : p.second) {
            const auto &v = edge.first;
            int cost = edge.second;
            if (u < v) {
                std::cout << u << ' ' << v << ' ' << cost << '\n';
            }
        }
    }
    std::cout << std::endl;
}


// Ejecuta Dijkstra para cada router y actualiza sus tablas
void Network::updateAllRoutingTables() {
    buildAdjacency();
    // Parámetros de Dijkstra
    const int INF = std::numeric_limits<int>::max();
    using Pair = pair<int,string>;

    for (auto &p : routers) {
        const string &src = p.first;
        // Mapas provisionales
        map<string,int> dist;
        map<string,string> prev;
        // Inicialización
        for (auto &q : routers) dist[q.first] = INF;
        dist[src] = 0;
        // Cola de prioridad (min-heap)
        std::priority_queue<Pair, vector<Pair>, std::greater<Pair>> pq;
        pq.push({0, src});
        // Bucle principal
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            // Relajar aristas de u
            for (auto &edge : adjList[u]) {
                const string &v = edge.first;
                int w = edge.second;
                if (d != INF && d + w < dist[v]) {
                    dist[v] = d + w;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        // Volcar datos al router
        p.second->setRoutingData(std::move(dist), std::move(prev));
    }
}

// Obtener lista de IDs de todos los routers
vector<string> Network::getRouterIds() const {
    vector<string> ids;
    for (auto &p : routers) ids.push_back(p.first);
    return ids;
}

// Obtener puntero al router (o nullptr si no existe)
const Router* Network::getRouter(const string &routerId) const {
    auto it = routers.find(routerId);
    return (it != routers.end() ? it->second : nullptr);
}

// Consultar costo mínimo src->dst
int Network::queryMinCost(const string &srcId, const string &dstId) const {
    const Router* src = getRouter(srcId);
    if (!src) return -1;
    return src->getDistance(dstId);
}

// Consultar ruta óptima src->dst
vector<string> Network::queryPath(const string &srcId, const string &dstId) const {
    const Router* src = getRouter(srcId);
    if (!src) return {};
    return src->getPath(dstId);
}

// Imprimir vecinos y tabla de cada router
void Network::printAllRouters() const {
    for (auto &p : routers) {
        p.second->printNeighbors();
        p.second->printRoutingTable();
        std::cout << std::endl;
    }
}
