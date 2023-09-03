#ifndef COUNTYMAP_H
#define COUNTYMAP_H

#include <vector>
#include "County.h"

using namespace std;

class CountyMap {
private:
    vector<County> counties;
    vector<vector<int>> adjacencyList; // Changed to adjacency list representation

    // Private helper functions
    int findNodeWithFewestNeighbors(const vector<vector<bool>>& adjMatrix);
    bool allNodesProcessed(const vector<vector<bool>>& adjMatrix);
    int count(const vector<bool>& vec, bool value);

public:
    //constructor
    CountyMap(vector<County> counties, vector<vector<bool>> adjacencyMatrix);

    CountyMap(const CountyMap& other);

    ~CountyMap();

    County getCounty(int countyID);

    bool countyAdjacency(int countyID1, int countyID2);

    int getNumCounties();
    
    vector<int> getAdjacentCounties(int countyID);

    bool checkValidItinerary(vector<int> itinerary);
};

#endif
