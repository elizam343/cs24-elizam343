#include "CountyMap.h"
#include "County.h"
#include <vector>

CountyMap::CountyMap(vector<County> counties, vector<vector<bool>> adjMatrix)
    : counties(counties) {
    // Initialize adjacencyList for each county.
    adjacencyList.resize(counties.size());

    while(!allNodesProcessed(adjMatrix)) {
        int node = findNodeWithFewestNeighbors(adjMatrix);
        for(size_t i = 0; i < adjMatrix[node].size(); i++) {
            if(adjMatrix[node][i]) {
                adjacencyList[node].push_back(i);
                // remove the edge
                adjMatrix[node][i] = false;
                adjMatrix[i][node] = false;
            }
        }
    }
}

int CountyMap::findNodeWithFewestNeighbors(const vector<vector<bool>>& adjMatrix) {
    int minNeighbors = INT_MAX;
    int minNode = -1;

    for(size_t i = 0; i < adjMatrix.size(); i++) {
        int neighbors = count(adjMatrix[i].begin(), adjMatrix[i].end(), true);
        if(neighbors < minNeighbors) {
            minNeighbors = neighbors;
            minNode = i;
        }
    }

    return minNode;
}

bool CountyMap::allNodesProcessed(const vector<vector<bool>>& adjMatrix) {
    for(const auto& row : adjMatrix) {
        for(bool val : row) {
            if(val) return false;  // Edge found
        }
    }
    return true;
}

CountyMap::CountyMap(const CountyMap& other) {
    counties = other.counties;
    adjacencyMatrix = other.adjacencyMatrix;
}


CountyMap::~CountyMap() {
    // TODO
}

County CountyMap::getCounty(int index) {
    return counties[index];
}


int CountyMap::getNumCounties() {
    return counties.size();
}


bool CountyMap::countyAdjacency(int index1, int index2) {
    return adjacencyMatrix[index1][index2];
}


bool CountyMap::checkValidItinerary(vector<int> itinerary) {
    for(size_t i = 0; i < itinerary.size() - 1; i++) {
        if(!adjacencyMatrix[itinerary[i]][itinerary[i + 1]]) {
            return false;
        }
    }
    return true;
}

vector<int> CountyMap::getAdjacentCounties(int index) {
    vector<int> adjacents;
    for(size_t i = 0; i < counties.size(); i++) {
        if(adjacencyMatrix[index][i]) {
            adjacents.push_back(i);
        }
    }
    return adjacents;
}



// helper functions may follow
