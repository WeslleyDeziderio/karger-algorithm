#include <iostream>
#include "../include/utils/Data.hpp"
#include "../include/utils/Vertex.hpp"
#include "../include/utils/Karger.hpp"

int main(int argc, char** argv) {
    Data data(argc, argv[1]);
    data.readData();
    // data.printAdjacencyMatrix();
    // data.printAdjacencyList();
 
    Karger instance;
    instance.setGraphEdges(data.getAdjacencyList());
    instance.showGraphEdges();

    while(instance.edgesSize() > 3){
        instance.merge(0);
    }
    instance.showGraphEdges();

    return 0;
}