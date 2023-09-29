#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>

#include "../../include/utils/Data.hpp"

class Vertex {
protected:
    std::vector<int> vertex;
public:
    Vertex();
    std::vector<int> getVertex();
};

#endif // VERTEX_HPP