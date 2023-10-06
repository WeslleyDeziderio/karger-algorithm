#include "../../include/utils/Vertex.hpp"

Vertex::Vertex() {}

Vertex::Vertex(int vtx){
    this->vertex.push_back(vtx);
}

Vertex::Vertex(std::vector<int> v1, std::vector<int> v2){
    this->vertex.insert(vertex.begin(), v1.begin(), v1.end());
    this->vertex.insert(vertex.end(), v2.begin(), v2.end());
}

std::vector<int> Vertex::getVertex() const {
    return vertex;
}

void Vertex::setVertex(std::vector<int> superNode){
    std::cout << "antes: " << this->vertex.size() << std::endl;
    this->vertex.clear();
    this->vertex = superNode;
    std::cout << "depois: " << this->vertex.size() << std::endl;

}