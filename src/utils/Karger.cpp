#include "../../include/utils/Karger.hpp"
#include <algorithm>
#include <random>

Karger::Karger(int params, char* instance) : kargerData(params, instance) {
    kargerData.readData();
    const int numVertices = kargerData.getNumVertices();
    std::cout << "Número de vertices: " << numVertices;
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, numVertices); // define the range

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