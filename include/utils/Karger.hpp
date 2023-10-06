#ifndef KARGER_HPP
#define KARGER_HPP

#include "Edge.hpp"
class Karger {
protected:
    std::vector<Edge*> graphEdge;
public:
    Karger();
    int randomize();
    void merge(int);
};

#endif // KARGER_HPP