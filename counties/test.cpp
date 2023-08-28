#include "CountyMap.h"
#include "County.h"
#include <iostream>

void printBool(bool value) {
    if (value) {
        std::cout << "True";
    } else {
        std::cout << "False";
    }
}

int main() {
    // Create some counties
    County county1 = {50000, "County1"};
    County county2 = {30000, "County2"};
    County county3 = {40000, "County3"};
    County county4 = {70000, "County4"};
    
    // Make a list of these counties
    std::vector<County> counties = {county1, county2, county3, county4};
    
    // Create an adjacency matrix for the counties
    // Assume: 1 is adjacent to 2, 2 is adjacent to 3, 3 is adjacent to 4, and 4 is not adjacent to 1
    std::vector<std::vector<bool>> adjMatrix = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}
    };
    
    // Create a CountyMap
    CountyMap countyMap(counties, adjMatrix);
    
    // Test cases
    std::cout << "Number of counties: " << countyMap.getNumCounties() << std::endl;
    
    County fetchedCounty = countyMap.getCounty(2);
    std::cout << "County at index 2: " << fetchedCounty.name << " with population: " << fetchedCounty.population << std::endl;
    
    std::cout << "Is county 1 adjacent to county 2? ";
    printBool(countyMap.countyAdjacency(0, 1));
    std::cout << std::endl;

    std::cout << "Is county 1 adjacent to county 4? ";
    printBool(countyMap.countyAdjacency(0, 3));
    std::cout << std::endl;

    std::vector<int> itinerary = {0, 1, 2, 3};
    std::cout << "Is the itinerary 0 -> 1 -> 2 -> 3 valid? ";
    printBool(countyMap.checkValidItinerary(itinerary));
    std::cout << std::endl;

    std::vector<int> badItinerary = {0, 3, 2, 1};
    std::cout << "Is the itinerary 0 -> 3 -> 2 -> 1 valid? ";
    printBool(countyMap.checkValidItinerary(badItinerary));
    std::cout << std::endl;

    std::vector<int> adjacentTo2 = countyMap.getAdjacentCounties(1);
    std::cout << "Counties adjacent to 2: ";
    for(int index : adjacentTo2) {
        std::cout << counties[index].name << " ";
    }
    std::cout << std::endl;

    return 0;
}
