#include "../../include/utils/Edge.hpp"

Edge::Edge() {}

Vertex* Edge::getVertex1(){
    return &this->vertex1;
}

Vertex* Edge::getVertex2(){
    return &this->vertex2;
}
