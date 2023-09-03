#include "CountyMap.h"
#include <algorithm> // for std::find, std::count
#include <climits>


// Constructors
CountyMap::CountyMap(std::vector<County> _counties, std::vector<std::vector<bool>> adjMatrix)
    : counties(_counties), adjacencyList(_counties.size()) {
    for(size_t i = 0; i < adjMatrix.size(); i++) {
        for(size_t j = 0; j < adjMatrix[i].size(); j++) {
            if(adjMatrix[i][j]) {
                adjacencyList[i].push_back(j);
            }
        }
    }
}

CountyMap::CountyMap(const CountyMap& other) {
    counties = other.counties;
    adjacencyList = other.adjacencyList;
}

CountyMap::~CountyMap() {
    // Nothing specific to destruct
}

// Member functions
County CountyMap::getCounty(int index) {
    return counties[index];
}

int CountyMap::getNumCounties() {
    return counties.size();
}

bool CountyMap::countyAdjacency(int index1, int index2) {
    return std::find(adjacencyList[index1].begin(), adjacencyList[index1].end(), index2) != adjacencyList[index1].end();
}

std::vector<int> CountyMap::getAdjacentCounties(int index) {
    return adjacencyList[index];
}

bool CountyMap::checkValidItinerary(std::vector<int> itinerary) {
    for(size_t i = 0; i < itinerary.size() - 1; i++) {
        if(!countyAdjacency(itinerary[i], itinerary[i + 1])) {
            return false;
        }
    }
    return true;
}

// Helper functions (if you decide to use them)
bool CountyMap::allNodesProcessed(const std::vector<std::vector<bool>>& adjMatrix) {
    for(const auto& row : adjMatrix) {
        for(bool val : row) {
            if(val) return false;  // Edge found
        }
    }
    return true;
}

int CountyMap::findNodeWithFewestNeighbors(const std::vector<std::vector<bool>>& adjMatrix) {
    int minNeighbors = INT_MAX;
    int minNode = -1;

    for(size_t i = 0; i < adjMatrix.size(); i++) {
        int neighbors = std::count(adjMatrix[i].begin(), adjMatrix[i].end(), true);
        if(neighbors < minNeighbors) {
            minNeighbors = neighbors;
            minNode = i;
        }
    }
    return minNode;
}
