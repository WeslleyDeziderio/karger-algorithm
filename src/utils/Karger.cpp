#include "../../include/utils/Karger.hpp"
#include <algorithm>

Karger::Karger() {}

void Karger::calculateKarger(){
    this->auxGraphEdge = this->graphEdge;

}

void Karger::minCut(int iterations){

    for(int i = 0 ; i < iterations ; i++){
        calculateKarger();
    }

}

void Karger::merge(int position){

    Edge randomizedEdge(this->auxGraphEdge[position]);
    this->auxGraphEdge.erase(this->auxGraphEdge.begin() + position);
    Vertex superNode(randomizedEdge.getVertex1().getVertex(), randomizedEdge.getVertex2().getVertex() );

    for(int i = 0; i < this->auxGraphEdge.size() ; i++){

        if(this->auxGraphEdge[i].getVertex1() == randomizedEdge.getVertex1() || this->auxGraphEdge[i].getVertex1() == randomizedEdge.getVertex2()){
            this->auxGraphEdge[i].getPointerVertex1()->setVertex(superNode.getVertex());
        }

        if(this->auxGraphEdge[i].getVertex2() == randomizedEdge.getVertex2() || this->auxGraphEdge[i].getVertex2() == randomizedEdge.getVertex1()){
            this->auxGraphEdge[i].getPointerVertex2()->setVertex(superNode.getVertex());
        }
    }
}

void Karger::setGraphEdges(std::list<std::list<int>> adjacencyList){

    int count = 1;
    for(auto const& i : adjacencyList){
        Vertex auxVertex1(count);
        for(auto const& j : i){
            if( j > count){
                Vertex auxVertex2(j);
                Edge auxEdge(auxVertex1, auxVertex2);
                this->graphEdge.push_back(auxEdge);
            }
        }
        count++;
    }

}

void Karger::showGraphEdges(std::vector<Edge> auxGraph){
    int i = 0;
    for(auto &it : auxGraph){
        std::vector<int> v1(it.getVertex1().getVertex());
        std::vector<int> v2(it.getVertex2().getVertex());
        std::cout << "Edge(" << i << "): Vertex1: ";

        for(int j = 0; j < v1.size() ; j++){
            std::cout << v1[j] << " ";
        }
        std::cout << "Vertex2: ";
        for(int j = 0; j < v2.size() ; j++){
            std::cout << v2[j] << " ";
        }
        std::cout << std::endl;
        i++;
    }
    std::cout << std::endl;
}

int Karger::edgesSize(){
    return this->auxGraphEdge.size();
}