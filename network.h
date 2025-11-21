#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <map>
#include <vector>
#include <utility>
#include "router.h"

using std::string;
using std::map;
using std::vector;
using std::pair;

class Network {
private:
    // Atributos
    map<string, vector<pair<string,int>>> adjList;

    map<string, Router*> routers;   // Punteros a routers, gestionados manualmente

    // Métodos internos
    void clearTopology();           // Elimina todos los routers y libera memoria
    void buildAdjacency();          // Reconstruye estructuras internas para algoritmos

public:
    // Constructor y Destructor
    Network();                      // Inicializa red vacía
    ~Network();                     // Libera memoria de todos los routers

    // Gestión de topología
    bool loadFromFile(const string& filename);
    bool addRouter(const string& routerId);
    bool removeRouter(const string& routerId);
    bool addLink(const string& id1, const string& id2, int cost);
    bool removeLink(const string& id1, const string& id2);
    void generateRandomTopology(int numRouters, int numLinks, int maxCost);

    void printTopologyFile() const;

    // Cálculo y actualización de rutas
    void updateAllRoutingTables();

    // Consultas
    vector<string> getRouterIds() const;
    const Router* getRouter(const string& routerId) const;
    int queryMinCost(const string& srcId, const string& dstId) const;
    vector<string> queryPath(const string& srcId, const string& dstId) const;

    // Impresión de estado
    void printAllRouters() const;
};

#endif // NETWORK_H
