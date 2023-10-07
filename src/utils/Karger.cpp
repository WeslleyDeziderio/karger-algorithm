#include "../../include/utils/Karger.hpp"
#include <algorithm>
#include <random>

Karger::Karger(int params, char* instance) : kargerData(params, instance) {
    kargerData.readData();
    const int numVertices = kargerData.getNumVertices();
    
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0, numVertices-1);

    std::cout << "Random value: " << distr(gen) << std::endl;
}

void Karger::merge(int position){

    Edge* randomizedEdge = this->graphEdge[position];
    this->graphEdge.erase(this->graphEdge.begin() + position);
    Vertex superNode(randomizedEdge->getVertex1()->getVertex(), randomizedEdge->getVertex2()->getVertex() );
    
    for(int i = 0; i < this->graphEdge.size() ; i++){
        if(this->graphEdge[i] == randomizedEdge){
            this->graphEdge[i]->getVertex1()->setVertex(superNode.getVertex());
            this->graphEdge[i]->getVertex2()->setVertex(superNode.getVertex());

        }

    }
}