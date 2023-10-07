#ifndef KARGER_HPP
#define KARGER_HPP

#include "Data.hpp"
#include "Edge.hpp"
class Karger {
protected:
    Data kargerData;
    std::vector<Edge*> graphEdge;
public:
    Karger(int, char*);
    int randomize();
    void merge(int);
};

#endif // KARGER_HPP