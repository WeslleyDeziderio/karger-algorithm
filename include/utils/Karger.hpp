#ifndef KARGER_HPP
#define KARGER_HPP

#include <algorithm>
#include <random>

#include "Edge.hpp"
#include "Vertex.hpp"
#include "Data.hpp"
#include <unordered_map>

const int MAX = (0x7FFFFFFF);
const int MIN = -1;
class Karger {
protected:
    Data kargerData;
    std::vector<Edge> graphEdge;
    std::vector<Edge> auxGraph;
public:
    Karger();
    Karger(int, char*);
    int edgesSize();
    int randomize();
    int randomize(int, int);
    int getSizeBetweenSets();
    bool calculateKarger(std::vector<Edge>);
    void merge(int);
    void setGraphEdges(std::list<std::list<int>>);
    void showGraphEdges(std::vector<Edge>);
    void findMinCut();
};

#endif // KARGER_HPP