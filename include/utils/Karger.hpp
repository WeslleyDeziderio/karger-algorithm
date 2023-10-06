#ifndef KARGER_HPP
#define KARGER_HPP

#include "Edge.hpp"
class Karger {
protected:
    std::vector<Edge> graphEdge;
public:
    Karger();
    int randomize();
    void merge(int);
    void setGraphEdges(std::list<std::list<int>>);
    void showGraphEdges();
};

#endif // KARGER_HPP