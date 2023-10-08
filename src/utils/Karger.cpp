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

void Karger::calculateKarger(){
    this->auxGraphEdge = this->graphEdge;

}

int Karger::randomize(int inferiorLimit,int superiorLimit) {

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(inferiorLimit, superiorLimit);

    int randomValue = distr(gen);

    return randomValue;
}

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
            return false;
        }
    }
    return true;
}

std::vector<Edge> Karger::calculateNaiveKager(){

    int firstCutSize = randomize(1,this->kargerData.getNumVertices()-2);
    std::vector<Vertex> firstCut;
    std::vector<Vertex> secondCut;
    std::vector<Edge> naiveKarger(this->graphEdge);
    int countEdges = 0;

    for(int i = 0 ; i < firstCutSize ; i++){
        int randomizedVertex = randomize(1,this->kargerData.getNumVertices());
        if(!(std::find(firstCut.begin(),firstCut.end(), randomizedVertex) != firstCut.end())){
            Vertex auxVertex(randomizedVertex); 
            firstCut.push_back(auxVertex);
            std::cout << "Vertex G1: " << randomizedVertex << std::endl;
        }
    }
    for(int i = 1; i <= this->kargerData.getNumVertices(); i++){
        if(!(std::find(firstCut.begin(),firstCut.end(), i) != firstCut.end())){
            Vertex auxVertex(i); 
            secondCut.push_back(auxVertex);
            std::cout << "Vertex G2: " << i << std::endl;
        }
    }
    std::cout << "Quantidade de vertices: " << kargerData.getNumVertices() << std::endl;
    std::cout << "Tamanho grupo 1: " << firstCut.size() << std::endl;

    for(int i = 0; i < (firstCut.size() -1); i++){
        for(int j = i+1;j < (firstCut.size()); j++){
            Edge auxEdge(firstCut[i],firstCut[j]);
            for(int k = 0 ; k < naiveKarger.size(); k++){

                if(auxEdge == naiveKarger[k]){
                    std::vector<int> v1(firstCut[i].getVertex());
                    std::vector<int> v2(firstCut[j].getVertex());
                    std::cout << "G1 V: " << v1[0] << "V: " << v2[0] << std::endl;
                    countEdges++;
                }
            }
        }
    }
    std::cout << "Tamanho grupo 2: " << secondCut.size() << std::endl;
    for(int i = 0; i < (secondCut.size() -1); i++){
        for(int j = i+1;j < (secondCut.size()); j++){
            Edge auxEdge(secondCut[i],secondCut[j]);
            for(int k = 0 ; k < naiveKarger.size(); k++){
                if(auxEdge == naiveKarger[k]){
                    std::vector<int> v1(secondCut[i].getVertex());
                    std::vector<int> v2(secondCut[j].getVertex());
                    std::cout << "G2 V: " << v1[0] << "V: " << v2[0] << std::endl;
                    countEdges++;
                }
            }
        }
    }
    std::cout << "Arestas entre os dois conjuntos: " << (naiveKarger.size() - countEdges) << std::endl;
    return naiveKarger;
}

void Karger::minCut(int iterations){

    for(int i = 0 ; i < iterations ; i++){
        calculateKarger();
    }

}
void Karger::merge(std::vector<Edge>& auxGraphEdges, Edge randomizedEdge){


    Vertex superNode(randomizedEdge.getVertex1().getVertex(), randomizedEdge.getVertex2().getVertex() );

    for(int i = 0; i < auxGraphEdges.size() ; i++){

        if(auxGraphEdges[i] == randomizedEdge){
            auxGraphEdges.erase(auxGraphEdges.begin() + i);
        }
        if(auxGraphEdges[i].getVertex1() == randomizedEdge.getVertex1() || auxGraphEdges[i].getVertex1() == randomizedEdge.getVertex2()){
            auxGraphEdges[i].getPointerVertex1()->setVertex(superNode.getVertex());
        }

        if(auxGraphEdges[i].getVertex2() == randomizedEdge.getVertex2() || auxGraphEdges[i].getVertex2() == randomizedEdge.getVertex1()){
            auxGraphEdges[i].getPointerVertex2()->setVertex(superNode.getVertex());
        }
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