#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>

#include "../../include/utils/Data.hpp"

class Vertex {
protected:
    std::vector<int> vertex;
public:
    Vertex();
    Vertex(std::vector<int>, std::vector<int>);
    std::vector<int> getVertex();
    void setVertex(std::vector<int>);
};

#endif // VERTEX_HPP