#include "../../include/utils/Karger.hpp"
#include <algorithm>

Karger::Karger() {}

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