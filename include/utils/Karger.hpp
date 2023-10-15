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
    int minimunCut;

public:
    Karger();
    Karger(int, char*, char*);
    int randomize();
    int randomize(int,int);
    int calculateNaiveKager(int);
    void calculateMinCutNaive(int);
    void merge(int);
    void setGraphEdges(std::list<std::list<int>>);
    void showGraphEdges(std::vector<Edge>);
    int edgesSize();
    void setMinCut(std::string);
};

#endif // KARGER_HPP