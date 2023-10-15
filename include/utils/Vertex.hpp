#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>

#include "../../include/utils/Data.hpp"

class Vertex {
protected:
    std::vector<int> vertex;
public:
    Vertex();
    Vertex(int);
    Vertex(std::vector<int>, std::vector<int>);
    std::vector<int> getVertex() const;
    void setVertex(std::vector<int>);

    bool operator==(const Vertex* v) const {
        return (this->vertex == v->getVertex());
    }
    bool operator!=(const Vertex* v) const {
        return (this->vertex != v->getVertex());
    }
    friend bool operator==(Vertex v1,Vertex v2) {
        return (v1.getVertex() == v2.getVertex());
    }
    friend bool operator!=(Vertex v1,Vertex v2) {
        return (v1.getVertex() != v2.getVertex());
    }
};

#endif // VERTEX_HPP