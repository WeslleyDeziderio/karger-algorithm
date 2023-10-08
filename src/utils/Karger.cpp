#include "../../include/utils/Karger.hpp"

Karger::Karger() {}

Karger::Karger(int params, char* instance) : kargerData(params, instance) {
    kargerData.readData();
}

int Karger::randomize() {
    const int numVertices = kargerData.getNumVertices();

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0, numVertices-1);

    int randomValue = distr(gen);

    return randomValue;
}

auto Karger::contractionLoop() {
    while (this->edgesSize() > 2) {
        merge(randomize());
    }
}

auto Karger::findMinCut(Vertex v, int iterations, int numVertices) {
    Vertex tempVertex;

    for (int i = 0; i < iterations; ++i) {

    }
}

void Karger::merge(int position){
    Edge randomizedEdge(this->graphEdge[position]);
    this->graphEdge.erase(this->graphEdge.begin() + position);
    Vertex superNode(randomizedEdge.getVertex1().getVertex(), randomizedEdge.getVertex2().getVertex() );

    for (int i = 0; i < this->graphEdge.size(); i++){

        if(this->graphEdge[i].getVertex1() == randomizedEdge.getVertex1() || this->graphEdge[i].getVertex1() == randomizedEdge.getVertex2()){
            this->graphEdge[i].getPointerVertex1()->setVertex(superNode.getVertex());
        }

        if(this->graphEdge[i].getVertex2() == randomizedEdge.getVertex2() || this->graphEdge[i].getVertex2() == randomizedEdge.getVertex1()){
            this->graphEdge[i].getPointerVertex2()->setVertex(superNode.getVertex());
        }

    }
}

void Karger::setGraphEdges(std::list<std::list<int>> adjacencyList){

    int count = 1;
    for (auto const& i : adjacencyList){
        Vertex auxVertex1(count);
        for (auto const& j : i){
            if (j > count){
                Vertex auxVertex2(j);
                Edge auxEdge(auxVertex1, auxVertex2);
                this->graphEdge.push_back(auxEdge);
            }
        }
        count++;
    }

}

void Karger::showGraphEdges(){
    int i = 0;
    for(auto &it : this->graphEdge){
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
    return this->graphEdge.size();
}