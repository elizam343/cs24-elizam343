#include "CountyMap.h"
#include "County.h"
#include <iostream>
#include <vector>

int main() {
    // 1. Create a few County objects.
    County county1("County1");
    County county2("County2");
    County county3("County3");
    County county4("County4");
    
    vector<County> counties = { county1, county2, county3, county4 };

    // 2. Define an adjacency matrix for these counties.
    // Let's assume:
    // County1 is adjacent to County2 and County3
    // County2 is adjacent to County1
    // County3 is adjacent to County1 and County4
    // County4 is adjacent to County3
    vector<vector<bool>> adjMatrix = {
        {false, true,  true,  false},
        {true,  false, false, false},
        {true,  false, false, true },
        {false, false, true,  false}
    };

    // 3. Create a CountyMap object.
    CountyMap countyMap(counties, adjMatrix);

    // 4. Check for valid itineraries.
    vector<int> itinerary1 = {0, 1}; // County1 -> County2
    vector<int> itinerary2 = {0, 2, 3}; // County1 -> County3 -> County4
    vector<int> itinerary3 = {0, 1, 2}; // County1 -> County2 -> County3 (invalid)

    std::cout << "Itinerary 1 is " << (countyMap.checkValidItinerary(itinerary1) ? "valid" : "invalid") << "\n";
    std::cout << "Itinerary 2 is " << (countyMap.checkValidItinerary(itinerary2) ? "valid" : "invalid") << "\n";
    std::cout << "Itinerary 3 is " << (countyMap.checkValidItinerary(itinerary3) ? "valid" : "invalid") << "\n";

    // 5. Fetch adjacent counties for a given county.
    std::cout << "Counties adjacent to County1: ";
    for (int idx : countyMap.getAdjacentCounties(0)) {
        std::cout << counties[idx].getName() << " ";
    }
    std::cout << "\n";

    return 0;
}
