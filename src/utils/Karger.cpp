#include "../../include/utils/Karger.hpp"

#include <map>
#include <unordered_map> 
#include <chrono>

Karger::Karger() {}

// Karger::Karger(int params, char* instance, char* instance2) : kargerData(params, instance) {
//     kargerData.readData();
//     setGraphEdges(kargerData.getAdjacencyList());
//     setMinCut(instance2);    
// }

Karger::Karger(int params, char* instance, char* instanceOut) : kargerData(params, instance, instanceOut) {
    kargerData.readData();
    setMinCut(instanceOut);
    setGraphEdges(kargerData.getAdjacencyList());
}

int Karger::edgesSize(){
    return this->graphEdge.size();
}

int Karger::randomize() {
    const int numVertices = kargerData.getNumVertices();

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0, numVertices-1);

    int randomValue = distr(gen);

    return randomValue;
}

int Karger::randomize(int lowerBound, int upperBound) {
    const int numVertices = kargerData.getNumVertices();

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(lowerBound, upperBound);

    int randomValue = distr(gen);

    return randomValue;
}

int Karger::calculateNaiveKager(int iterations){

    std::map<int, int> n_exec;
    int qEdges = this->graphEdge.size();
    int qVertices = this->kargerData.getNumVertices();
    for(int e = 0 ; e < iterations; e++){

        int firstCutSize = randomize(1,qVertices-2);
        std::vector<int> firstCut;
        std::vector<int> secondCut;

        int countEdges = 0;

        for(int i = 1; i <= qVertices; i++){
            secondCut.push_back(i);
        }

        for(int i = 0 ; i < firstCutSize ; i++){
            int randomizedVertex = randomize(0,(secondCut.size()-1));
            int auxVertex = secondCut[randomizedVertex];
            secondCut.erase( secondCut.begin() + randomizedVertex);
            firstCut.push_back(auxVertex);
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
        int edgesBetween = qEdges - countEdges;

        if(n_exec.count(edgesBetween) != 0 ){
            n_exec[edgesBetween] = n_exec[edgesBetween] + 1;
        }else{
            n_exec[edgesBetween] = 1;
        }
        if(edgesBetween == this->minimunCut){
            break;
        }
    }
    std::map<int, int>::iterator it = n_exec.begin();
    return it->first;
}

void Karger::calculateMinCutNaive(int executions){
    std::map<int, float> cuts;
    std::cout << "minumin: " << this->minimunCut << std::endl;
    int increment = 10;
    bool findProb = false;
    for(int i = 1 ; i <= 91 ; i += increment){
        float count = 0;
        auto startTime = std::chrono::high_resolution_clock::now();
        for(int j = 0; j < executions ; j++){
            int min = calculateNaiveKager(i);
            if(min == this->minimunCut){
                count++;
            }
        }
        auto finalTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> timeTaken = finalTime-startTime;
        cuts[i] = (float)(count/executions);
        if((i-increment) > 0){
            std::cout << "iter(" << i-1 <<") prob: " << cuts[i] << " Time: " << (timeTaken.count()/1000) << "s" <<std::endl;
        }else{
            std::cout << "iter(" << i <<") prob: " << cuts[i] << " Time: " << (timeTaken.count()/1000) << "s" <<std::endl;
        }
        if(cuts[i] >= 0.98){
            findProb = true;
            break;
        }
    }
    if(!findProb){
        increment = 100;
        for(int i = 101 ; i <= 2001 ; i += increment){
            float count = 0;
            auto startTime = std::chrono::high_resolution_clock::now();
            for(int j = 0; j < executions ; j++){
                int min = calculateNaiveKager(i);
                if(min == this->minimunCut){
                    count++;
                }
            }
            auto finalTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> timeTaken = finalTime-startTime;
            cuts[i] = (float)(count/executions); 
            
            std::cout << "iter(" <<  i-1 <<") prob: " << cuts[i] << " Time: " << (timeTaken.count()/1000) << "s" <<std::endl;
         
            if(cuts[i] >= 0.98){
                break;
            }
        }
    }
}

void Karger::merge(int position){
    Edge randomizedEdge(this->auxGraph[position]);
    this->auxGraph.erase(this->auxGraph.begin() + position);
    Vertex superNode(randomizedEdge.getVertex1().getVertex(), randomizedEdge.getVertex2().getVertex() );

    for (int i = 0; i < this->auxGraph.size(); i++){
        if(this->auxGraph[i].getVertex1() == randomizedEdge.getVertex1() || this->auxGraph[i].getVertex1() == randomizedEdge.getVertex2()){
            this->auxGraph[i].getPointerVertex1()->setVertex(superNode.getVertex());
        }

        if(this->auxGraph[i].getVertex2() == randomizedEdge.getVertex2() || this->auxGraph[i].getVertex2() == randomizedEdge.getVertex1()){
            this->auxGraph[i].getPointerVertex2()->setVertex(superNode.getVertex());
        }
        if(this->auxGraph[i].getVertex1() == this->auxGraph[i].getVertex2()){
            this->auxGraph.erase(this->auxGraph.begin()+i);
        }
    }
    auto startTime = std::chrono::high_resolution_clock::now();

    removeDuplicates();
	
	auto finalTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> timeTaken = finalTime-startTime;
    std::cout << "\nTime taken remove duplicates: " << timeTaken.count() << " ms\n" << std::endl;
}

bool Karger::calculateKarger(std::vector<Edge> auxEdges){
    std::vector<Vertex> uniqueVertices;
    for(int i = 0 ; i < auxEdges.size(); i++){
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

void Karger::calculateMinKarger(int executions){
    std::map<int, float> cuts;
    std::cout << "minimum: " << this->minimunCut << std::endl;
    int increment = 10;
    bool findProb = false;
    for(int i = 1 ; i <= 91 ; i += increment){
        float count = 0;
        auto startTime = std::chrono::high_resolution_clock::now();
        for(int j = 0; j < executions ; j++){
            int min = findMinCut(i);
            if(min == this->minimunCut){
                count++;
            }
        }
        auto finalTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> timeTaken = finalTime-startTime;
        cuts[i] = (float)(count/executions);
        if((i-increment) > 0){
            std::cout << "iter(" << i-1 <<") prob: " << cuts[i] << " Time: " << (timeTaken.count()/1000) << "s" <<std::endl;
        }else{
            std::cout << "iter(" << i <<") prob: " << cuts[i] << " Time: " << (timeTaken.count()/1000) << "s" <<std::endl;
        }
        if(cuts[i] >= 0.98){
            findProb = true;
            break;
        }
    }
    if(!findProb){
        increment = 100;
        for(int i = 101 ; i <= 2001 ; i += increment){
            float count = 0;
            auto startTime = std::chrono::high_resolution_clock::now();
            for(int j = 0; j < executions ; j++){
                int min = findMinCut(i);
                if(min == this->minimunCut){
                    count++;
                }
            }
            auto finalTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> timeTaken = finalTime-startTime;
            cuts[i] = (float)(count/executions); 

            std::cout << "iter(" <<  i-1 <<") prob: " << cuts[i] << " Time: " << (timeTaken.count()/1000) << "s" <<std::endl;

            if(cuts[i] >= 0.98){
                break;
            }
        }
    }
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

int Karger::findMinCut(int executions) {
    std::map<int, int> numExec;

    for (int e = 0; e < executions; e++) {
        this->auxGraph = this->graphEdge;
        
        auto startTime = std::chrono::high_resolution_clock::now();

         while (auxGraph.size() > 1) {
            int pos = randomize(0, this->auxGraph.size()-1);
            auto startTime3 = std::chrono::high_resolution_clock::now();

            merge(pos);

            auto finalTime3 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> timeTaken3 = finalTime3-startTime3;
            std::cout << "\nTime taken merge: " << timeTaken3.count() << " ms\n" << std::endl;
        }

        auto finalTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> timeTaken = finalTime-startTime;
        std::cout << "\nTime taken karger: " << timeTaken.count() << " ms\n" << std::endl;

        auto startTime2 = std::chrono::high_resolution_clock::now();

        std::vector<int> firstCut(this->auxGraph[0].getVertex1().getVertex());
        std::vector<int> secondCut(this->auxGraph[0].getVertex2().getVertex());

        int countEdges = 0;
        int qEdges = this->graphEdge.size();
        for(int i = 0; i < (firstCut.size()); i++){
            for(int j = i+1; j < (firstCut.size()); j++){
                if (kargerData.isAdjacency(firstCut[i], firstCut[j])){
                    countEdges++;
                }
            }
        }

        for (int i = 0; i < (secondCut.size()); i++){
            for (int j = i+1; j < (secondCut.size()); j++){
                if (kargerData.isAdjacency(secondCut[i], secondCut[j])){
                    countEdges++;
                }
            }
        }

        int edgesBetween = qEdges - countEdges;

        if(numExec.count(edgesBetween) != 0 ){
            numExec[edgesBetween] = numExec[edgesBetween] + 1;
        }else{
            numExec[edgesBetween] = 1;
        }
        if(edgesBetween == this->minimunCut){
            break;
        }


        auto finalTime2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> timeTaken2 = finalTime2-startTime2;
        std::cout << "\nTime taken corte: " << timeTaken2.count() << " ms\n" << std::endl;
    }

    std::map<int, int>::iterator it = numExec.begin();

    return it->first;
}

void Karger::removeDuplicates(){

    if(this->auxGraph.size() == 1){
        return;
    }
    for(int i = 0; i < (this->auxGraph.size()); i++){
        Edge oppositeDirection(this->auxGraph[i].getVertex2(),this->auxGraph[i].getVertex1());
        if(this->auxGraph[i].getVertex2() == this->auxGraph[i].getVertex1()){
            this->auxGraph.erase(this->auxGraph.begin()+i);
        }
        for(int j = i+1; j < (this->auxGraph.size()); j++){
            if (this->auxGraph[i] == this->auxGraph[j]){
                this->auxGraph.erase(this->auxGraph.begin()+j);
            }else if(oppositeDirection == this->auxGraph[j]){
                this->auxGraph.erase(this->auxGraph.begin()+j);
            }
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
