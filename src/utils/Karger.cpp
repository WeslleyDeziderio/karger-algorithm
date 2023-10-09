#include "../../include/utils/Karger.hpp"
#include <map>

Karger::Karger() {}

Karger::Karger(int params, char* instance, char* instance2) : kargerData(params, instance) {
    kargerData.readData();
    setGraphEdges(kargerData.getAdjacencyList());
    setMinCut(instance2);    
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

int Karger::calculateNaiveKager(int iterations){

    std::map<int, int> n_exec;
    for(int e = 0 ; e < iterations; e++){

        int firstCutSize = randomize(1,this->kargerData.getNumVertices()-2);
        std::vector<int> firstCut;
        std::vector<int> secondCut;
        int countEdges = 0;

        for(int i = 0 ; i < firstCutSize ; i++){
            int randomizedVertex = randomize(1,this->kargerData.getNumVertices());
            if(!(std::find(firstCut.begin(),firstCut.end(), randomizedVertex) != firstCut.end())){
                firstCut.push_back(randomizedVertex);
            }
        }
        for(int i = 1; i <= this->kargerData.getNumVertices(); i++){
            if(!(std::find(firstCut.begin(),firstCut.end(), i) != firstCut.end())){
                secondCut.push_back(i);
            }
        }

        for(int i = 0; i < (firstCut.size()); i++){
            for(int j = i+1;j < (firstCut.size()); j++){
                if(kargerData.isAdjacency(firstCut[i],firstCut[j])){
                    countEdges++;
                }
            }
        }

        for(int i = 0; i < (secondCut.size()); i++){
            for(int j = i+1;j < (secondCut.size()); j++){
                if(kargerData.isAdjacency(secondCut[i],secondCut[j])){
                    countEdges++;
                }
            }
        }
        int edgesBetween = this->graphEdge.size() - countEdges;
        if(n_exec.count(edgesBetween) != 0 ){
            n_exec[edgesBetween] = n_exec[edgesBetween] + 1;
        }else{
            n_exec[edgesBetween] = 1;
        }
    }

    if(n_exec.count(this->minimunCut) != 0){
        return n_exec[this->minimunCut];
    }else{
        return 0;
    }

}

void Karger::calculateMinCutNaive(int executions){
    std::map<int, float> cuts;
    std::cout << "minumin: " << this->minimunCut << std::endl;
    int increment = 100;
    for(int i = 0 ; i <= 10000 ; i += increment){
        int min = calculateNaiveKager(i);
        float aux = ((float)min/i);
        std::cout << "Found: " << min <<" P: " << aux << std::endl;
        cuts[i] = aux; 
        // if(cuts.count(i) != 0 ){
        //     cuts[i] = cuts[min] + 1;
        // }else{
        //     cuts[i] = 1;
        // }
    }
     std::map<int, float>::iterator it = cuts.begin();
    while(it != cuts.end()){
        std::cout << "iterações: " << it->first << " Probabilidade: " << it->second << std::endl;
        ++it;
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

void Karger::setMinCut(std::string filename){
    std::ifstream file;

    file.open(filename, std::ios::in);

    if(file.is_open()){
        std::string line;
        std::getline(file,line);

        this->minimunCut = std::stoi(line);
    }else{
        std::cout << "File not found!" << std::endl;
    }
    file.close();
}