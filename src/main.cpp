#include <iostream>
#include "../include/utils/Data.hpp"
#include "../include/utils/Vertex.hpp"
#include "../include/utils/Karger.hpp"

int main(int argc, char** argv) {
    Data data(argc, argv[1]);
    data.readData();
    // data.printAdjacencyMatrix();
    // data.printAdjacencyList();

    // Karger instance;

    Karger karger(argc, argv[1]);
    karger.randomize();
    karger.setGraphEdges(data.getAdjacencyList());
    karger.showGraphEdges(karger.isCutFound());

    return 0;
}