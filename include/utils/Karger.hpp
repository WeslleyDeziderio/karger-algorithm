#ifndef KARGER_HPP
#define KARGER_HPP

#include <algorithm>
#include <random>

#include "Edge.hpp"
#include "Vertex.hpp"

class Karger {
protected:
    Data kargerData;
    std::vector<Edge> graphEdge;
    std::vector<Edge> auxGraphEdge;
public:
    Karger();
    Karger(int, char*);
    bool isCutFound(std::vector<Edge>);
    int randomize();
    int randomize(int,int);
    void calculateKarger();
    int calculateNaiveKager(int);
    void minCut(int);
    void merge(int);
    void merge(std::vector<Edge>&, Edge);
    void setGraphEdges(std::list<std::list<int>>);
    void showGraphEdges(std::vector<Edge>);
    int edgesSize();
};

#endif // KARGER_HPP