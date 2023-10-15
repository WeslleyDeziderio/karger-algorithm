#include <iostream>
#include "../include/utils/Data.hpp"
#include "../include/utils/Vertex.hpp"
#include "../include/utils/Karger.hpp"
#include <chrono>

int main(int argc, char** argv) {
    Karger instance(argc, argv[1], argv[2]);

    auto startTime = std::chrono::high_resolution_clock::now();
    instance.calculateMinCutNaive(1000);
    auto finalTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> timeTaken = finalTime-startTime;
    std::cout << "\nFinal time: " << (timeTaken.count()/1000) << " s\n" << std::endl;

    Karger karger(argc, argv[1], argv[2]);
    // karger.findMinCut(1000);
    karger.calculateMinKarger(50);

    return 0;
}