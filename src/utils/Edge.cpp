#include "../../include/utils/Edge.hpp"

Edge::Edge() {}

Edge::Edge(Vertex v1, Vertex v2){
    this->vertex1 = v1;
    this->vertex2 = v2;
}

Vertex Edge::getVertex1(){
    return vertex1;
}

Vertex Edge::getVertex2(){
    return vertex2;
}

Vertex* Edge::getPointerVertex1(){
    return &this->vertex1;
}

Vertex* Edge::getPointerVertex2(){
    return &this->vertex2;
}
