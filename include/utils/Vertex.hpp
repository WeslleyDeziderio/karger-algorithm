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
    bool operator==(Vertex* v)const{
        std::cout << "usedV" << std::endl;
        return (vertex == v->getVertex());
    }
};

#endif // VERTEX_HPP