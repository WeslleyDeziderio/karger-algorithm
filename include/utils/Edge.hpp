#ifndef EDGE_HPP
#define EDGE_HPP

#include "Vertex.hpp"

class Edge {
protected:
    Vertex vertex1;
    Vertex vertex2;
public:
    Edge();
    Edge(Vertex, Vertex);
    Vertex getVertex1();
    Vertex getVertex2();
    Vertex* getPointerVertex1();
    Vertex* getPointerVertex2();
    
    bool operator==(Edge edge) const {
        return ((this->vertex1 == edge.getVertex1() && this->vertex2 == edge.getVertex2()));
    }
};

#endif // EDGE_GPP