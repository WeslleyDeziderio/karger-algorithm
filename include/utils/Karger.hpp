#ifndef KARGER_HPP
#define KARGER_HPP

#include <algorithm>
#include <random>
#include <map>
#include <string>
#include <chrono>

#include "Edge.hpp"
#include "Vertex.hpp"
#include "Data.hpp"

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
    std::vector<Edge> auxGraph;
    int minimunCut;
public:
    Karger();
    Karger(int, char*, char*);
    int edgesSize();
    void merge(int);
    int randomize();
    int randomize(int, int);
    bool calculateKarger(std::vector<Edge>);
    void calculateMinKarger(int);
    void setMinCut(std::string);
    int findMinCut(int);
    void setGraphEdges(std::list<std::list<int>>);
    void showGraphEdges(std::vector<Edge>);
    int edgesSize();
    void setMinCut(std::string);
    void removeDuplicates();
};

#endif // KARGER_HPP