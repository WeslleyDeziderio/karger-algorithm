#include "../../include/utils/Data.hpp"

Data::Data() {}

Data::Data(int params, char* instance) {
    if (params != 2) {
        std::cerr << "ERROR: Missing parameters!" << std::endl;
        std::cout << "Usage: ./search <Instance>" << std::endl;
        exit(1);
    }

    instanceName = instance;
    numVertices = 0;
}

void Data::readData() {
	std::ifstream inputData(instanceName, std::ios::in);

	if (!inputData) {
		std::cerr << "ERROR: File not found!" << std::endl;
        exit(1);
	}

    inputData >> numVertices;
    std::cout << "Number of vertices: " << numVertices << std::endl;
    adjacencyMatrix.assign(numVertices, std::vector<int>(numVertices, 0));

    for (int i = 0; i < this->numVertices; ++i) {
        for (int j = 0; j < this->numVertices; ++j) {
            inputData >> this->adjacencyMatrix[i][j];
        }
    }

    inputData.close();
    std::cout << "Data read successfully! \n" << std::endl;
}

std::string Data::getInstanceName() {
    return instanceName;
}

int Data::getNumVertices() {
    return this->numVertices;
}

std::vector<std::vector<int>> Data::getAdjacencyMatrix() {
    return adjacencyMatrix;
}

void Data::printAdjacencyMatrix() {  
    std::cout << "Adjacency Matrix: \n";
    const std::vector<std::vector<int>>& matrix = getAdjacencyMatrix();
    
    for (const auto& row : matrix) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";
}

std::list<std::list<int>> Data::getAdjacencyList() {
    for (int i = 0; i < this->numVertices; ++i) {
        std::list<int> neighbors;
        for (int j = 0; j < this->numVertices; ++j) {
            if (this->adjacencyMatrix[i][j] == 1) {
                neighbors.push_back(j+1);
            }
        }

        adjacencyList.push_back(neighbors);
    }

    return adjacencyList;
}

void Data::printAdjacencyList() {
    const std::list<std::list<int>>& adjacencyList = getAdjacencyList();
    int vertex = 1;
    
    std::cout << "Adjacency List: \n";
    for (const auto& neighbors : adjacencyList) {
        std::cout << vertex << " --> ";
        for (int neighbor : neighbors) {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
        ++vertex;
    }
}

std::vector<int> Data::getNeighborhoodMatrix(int vertex) {
    std::vector<int> neighbors;

    vertex -= 1;
    for (int i = 0; i < this->numVertices; ++i) {
        if (this->adjacencyMatrix[vertex][i] == 1) {
            neighbors.push_back(i+1);
        }
    }

    return neighbors;
}