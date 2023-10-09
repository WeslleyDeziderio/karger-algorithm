#include <iostream>
#include "../include/utils/Data.hpp"
#include "../include/utils/Vertex.hpp"
#include "../include/utils/Karger.hpp"

int main(int argc, char** argv) {
    // Data data(argc, argv[1]);
    // data.readData();
    // data.printAdjacencyMatrix();
    // data.printAdjacencyList();
 
    Karger instance(argc, argv[1], argv[2]);
    instance.calculateMinCutNaive(10);



    return 0;
}