#ifndef COUNTYMAP_H
#define COUNTYMAP_H

#include <vector>
#include <string>
#include "County.h"

using namespace std;

class CountyMap {
private:
    vector<County> counties;
    vector<vector<int>> adjacencyList; // Using adjacency list representation
    std::string name;

    // Private helper functions
    int findNodeWithFewestNeighbors(const vector<vector<bool>>& adjMatrix);
    bool allNodesProcessed(const vector<vector<bool>>& adjMatrix);

public:
    // Constructors
    CountyMap(vector<County> _counties, vector<vector<bool>> adjMatrix);

    CountyMap(const CountyMap& other);

    // Destructor
    ~CountyMap();

    // Member Functions
    County getCounty(int index);

    bool countyAdjacency(int index1, int index2);

    int getNumCounties();
    
    vector<int> getAdjacentCounties(int index);

    bool checkValidItinerary(vector<int> itinerary);

    std::string getName() const { return name; }
};

#endif
