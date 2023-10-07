#ifndef KARGER_HPP
#define KARGER_HPP

#include <algorithm>
#include <random>

#include "Edge.hpp"
#include "Vertex.hpp"
#include "Data.hpp"

class Karger {
protected:
    Data kargerData;
    std::vector<Edge> graphEdge;
public:
    Karger();
    Karger(int, char*);
    int edgesSize();
    int randomize();
    void merge(int);
    void setGraphEdges(std::list<std::list<int>>);
    void showGraphEdges();
    auto findMinCut(Vertex, int, int);
};

#endif // KARGER_HPP