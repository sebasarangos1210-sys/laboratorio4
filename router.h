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
    string id;
    vector<pair<string,int>> neighbors;
    map<string,int> dist;
    map<string,string> prev;

public:
    explicit Router(const string& id);

    string getId() const;

    void addNeighbor(const string& neighborId, int cost);
    void removeNeighbor(const string& neighborId);
    const vector<pair<string,int>>& getNeighbors() const;

    void setRoutingData(map<string,int> distances, map<string,string> predecessors);

    int getDistance(const string& destination) const;
    vector<string> getPath(const string& destination) const;
    const map<string,int>& getDistances() const;
    const map<string,string>& getPredecessors() const;

    void printNeighbors() const;
    void printRoutingTable() const;
};

#endif // ROUTER_H
