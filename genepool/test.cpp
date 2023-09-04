#include "Person.h"
#include "GenePool.h"
#include "Query.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <string>

void runQuery(const std::string& queryName, Person* person, GenePool& genePool) {
    std::cout << queryName << " (" << person->name() << "):" << std::endl;

    // Construct the query text based on the queryName and the person's name
    std::string queryText = person->name() + "'s " + queryName;

    // Create a Query object using the query text
    Query query(queryText);

    // Run the query using the genePool
    std::set<Person*> result = query.run(genePool);

    // Print the query results
    for (const auto& person : result) {
        std::cout << "+  - " << person->name() << std::endl;
    }

    std::cout << "-----------------------------" << std::endl;
}



void testPersonQueries(Person* person, GenePool& genePool) {
    std::vector<std::string> functionsToTest = {
        "ancestors", "aunts", "brothers", "cousins", "daughters",
        "granddaughters", "grandsons", "nephews", "nieces", "siblings",
        "sisters", "sons", "uncles"
    };

    for (const auto& function : functionsToTest) {
        runQuery(function, person, genePool);
    }
}

int main() {
    // Hardcode the path to the TSV file you want to test
    std::string filePath = "data/Olympians.tsv";

    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open " << filePath << std::endl;
        return 1;
    }

    GenePool genePool(inputFile);

    // Find a specific person in the gene pool
    Person* personToTest = genePool.find("Rhea"); // Change to the desired person's name

    if (personToTest) {
        testPersonQueries(personToTest, genePool);
    } else {
        std::cerr << "Person not found in gene pool." << std::endl;
    }

    return 0;
}
