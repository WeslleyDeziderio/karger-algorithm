#include <iostream>
#include "../include/utils/Data.hpp"
#include "../include/utils/Vertex.hpp"
#include "../include/utils/Karger.hpp"

int main(int argc, char** argv) {
    Karger instance(argc, argv[1], argv[2]);
    std::cout << "Executing Naive Karger..." << std::endl;

    auto startTime = std::chrono::high_resolution_clock::now();
    instance.calculateMinCutNaive(1000);
    auto finalTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> timeTaken = finalTime-startTime;
    std::cout << "\nFinal time: " << (timeTaken.count()/1000) << " s\n" << std::endl;

    std::cout << "Executing Karger..." << std::endl;
    
    Karger karger(argc, argv[1], argv[2]);
    auto startTimeKarger = std::chrono::high_resolution_clock::now();
    karger.calculateMinKarger(1000);
    auto finalTimeKarger = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> timeTakenKarger = finalTimeKarger-startTimeKarger;
    std::cout << "\nFinal time: " << (timeTaken.count()/1000) << " s\n" << std::endl;

    return 0;
}