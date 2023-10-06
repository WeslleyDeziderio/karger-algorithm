#ifndef KARGER_HPP
#define KARGER_HPP

#include "Edge.hpp"
#include "Vertex.hpp"

class Karger {
protected:
    std::vector<Edge> graphEdge;
public:
    Karger();
    int randomize();
    void merge(int);
    void setGraphEdges(std::list<std::list<int>>);
    void showGraphEdges();
    int edgesSize();
};

#endif // KARGER_HPP