#include "../../include/utils/Karger.hpp"

Karger::Karger() {}

Karger::Karger(int params, char* instance) : kargerData(params, instance) {
    kargerData.readData();
    setGraphEdges(kargerData.getAdjacencyList());
}

int Karger::randomize() {
    const int numVertices = kargerData.getNumVertices();

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0, numVertices-1);

    int randomValue = distr(gen);

    return randomValue;
}

// void Karger::contractionLoop() {
//     while (this->edgesSize() > 2) {
//         merge(randomize());
//         getSizeBetweenSets();
//     }
// }

bool Karger::isCutFound(std::vector<Edge> auxEdges){
    std::vector<Vertex> uniqueVertices;
    for(int i = 0 ; i < this->kargerData.getNumVertices(); i++){
        Vertex auxVertex = auxEdges[i].getVertex1();
        if(!(std::find(auxEdges.begin(), auxEdges.end(), auxVertex) != auxEdges.end())){
            uniqueVertices.push_back(auxVertex);
        }
        auxVertex = auxEdges[i].getVertex2();
        if(!(std::find(auxEdges.begin(), auxEdges.end(), auxVertex) != auxEdges.end())){
            uniqueVertices.push_back(auxVertex);
        }
        if(uniqueVertices.size() > 2){
            std::cout << "tamanho: " << getSizeBetweenSets() << std::endl;
            return false;
        }
    }
    return true;
}

int Karger::getSizeBetweenSets() {
    std::cout << "tamanho entre os dois conjuntos: " << this->graphEdge.size() << std::endl;

    return this->graphEdge.size();
}

auto Karger::findMinCut(int iterations) {
    Vertex tempVertex;
    int tempCutSize = MAX;
    int cutSize = MIN;

    for (int i = 0; i < iterations; ++i) {
        if (cutSize < tempCutSize) {
            tempCutSize = cutSize;
        }
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

void Karger::showGraphEdges(std::vector<Edge>){
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