#include <iostream>
#include "../include/utils/Data.hpp"
#include "../include/utils/Vertex.hpp"
#include "../include/utils/Karger.hpp"

int main(int argc, char** argv) {
    Karger karger(argc, argv[1], argv[2]);
    // karger.findMinCut(1000);
    karger.calculateMinKarger(50);

    return 0;
}