#ifndef KARGER_HPP
#define KARGER_HPP

#include "Edge.hpp"
#include "Vertex.hpp"

class Karger {
protected:
    std::vector<Edge> graphEdge;
    std::vector<Edge> auxGraphEdge;
public:
    Karger();
    int randomize();
    void calculateKarger();
    void minCut(int);
    void merge(int);
    void setGraphEdges(std::list<std::list<int>>);
    void showGraphEdges(std::vector<Edge>);
    int edgesSize();
};

#endif // KARGER_HPP