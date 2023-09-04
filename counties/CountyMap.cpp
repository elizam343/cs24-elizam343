
#include "CountyMap.h"
#include "County.h"
#include <vector>

CountyMap::CountyMap(vector<County> counties, vector<vector<bool>> adjMatrix) 
    : counties(counties), adjacencyMatrix(adjMatrix) {}


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