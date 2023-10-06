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
    Vertex* getVertex1();
    Vertex* getVertex2();
    bool operator==(Edge edge) const {
        return ((this->vertex1.getVertex() == edge.getVertex1()->getVertex() && this->vertex2.getVertex() == edge.getVertex2()->getVertex()));
    }


};

#endif // EDGE_GPP