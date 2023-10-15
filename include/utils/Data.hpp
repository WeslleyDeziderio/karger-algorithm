#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>

class Data {
protected:
    int paramsNumber;
    int numVertices;
    std::string instanceName;
    std::vector<std::vector<int>> adjacencyMatrix;
    std::list<std::list<int>> adjacencyList;
public:
    Data();
    Data(int, char*, char*);
    void readData();
    std::string getInstanceName();
    int getNumVertices();
    std::vector<std::vector<int>> getAdjacencyMatrix();
    void printAdjacencyMatrix();
    std::list<std::list<int>> getAdjacencyList();
    void printAdjacencyList();
    bool isAdjacency(int, int);
};

#endif // DATA_HPP