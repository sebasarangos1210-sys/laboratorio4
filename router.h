#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;
using std::pair;

class Router {
private:
    // Atributos
    string id;                                    // ID unico del router
    vector<pair<string,int>> neighbors;           // Lista de vecinos directos y coste de enlace
    map<string,int> dist;                         // Coste minimo conocido a cada destino
    map<string,string> prev;                      // Predecesor en la ruta optima

    // Metodos internos (si fueran necesarios)
    // (por ahora no hay métodos auxiliares privados)

public:
    // Constructor
    explicit Router(const string& id);

    // Atributos públicos (si se necesitan exponer directamente)
    // (normalmente mantenemos los atributos privados y solo exponemos métodos)

    // Métodos públicos
    string getId() const;

    // Gestión de vecinos
    void addNeighbor(const string& neighborId, int cost);
    void removeNeighbor(const string& neighborId);
    const vector<pair<string,int>>& getNeighbors() const;

    // Carga de resultados de enrutamiento
    void setRoutingData(map<string,int> distances,
                        map<string,string> predecessors);

    // Consultas sobre rutas ya calculadas
    int getDistance(const string& destination) const;
    vector<string> getPath(const string& destination) const;
    const map<string,int>& getDistances() const;
    const map<string,string>& getPredecessors() const;

    // Impresión de información
    void printNeighbors() const;
    void printRoutingTable() const;
};

#endif // ROUTER_H
