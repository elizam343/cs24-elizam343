#include "Person.h"
#include "GenePool.h"
#include "Query.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <set> 
#include <filesystem>
namespace fs = std::filesystem;

// Helper class to sort person pointers by name:
struct Compare {
  bool operator () (const Person* a, const Person* b) const {
    return a->name() < b->name();
  }
};

void testGenePool(const std::string& filepath) {

    std::ifstream inputFile(filepath);
    
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open " << filepath << std::endl;
        return;
    }

    GenePool genePool(inputFile);

    // Print out all the people parsed from the file
    std::cout << "Contents of " << filepath << ":" << std::endl;
    for (const auto& personPtr : genePool.getAllPersons()) {
        std::cout << "Name: " << personPtr->name() 
                  << ", Gender: " << static_cast<int>(personPtr->gender()) 
                  << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
    // Open the file from the provided path
    std::ifstream inputFile(filepath);

    // Check if the file opened correctly
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open " << filepath << std::endl;
        return;
    }

    GenePool genePool(inputFile);

    // Testing basic functionality
    Person* alice = genePool.find("Alice");
    Person* bob = genePool.find("Bob");
    Person* charlie = genePool.find("Charlie");
    Person* dana = genePool.find("Dana");

    // Basic assertions
    if (alice) {
        std::cout << "Alice exists. Gender: " << static_cast<int>(alice->gender()) << std::endl;
    } else {
        std::cerr << "Alice does not exist." << std::endl;
        return;
    }

    // Assertions
    assert(alice && alice->gender() == Gender::FEMALE);
    assert(bob && bob->gender() == Gender::MALE);
    assert(charlie && charlie->gender() == Gender::MALE);
    assert(dana && dana->gender() == Gender::FEMALE);

    // Test parental relationships
    assert(charlie->mother() == alice);
    assert(charlie->father() == bob);
    assert(dana->mother() == alice);
    assert(dana->father() == bob);

    // Test children relationships
    std::set<Person*> aliceChildren = alice->children();
    assert(aliceChildren.find(charlie) != aliceChildren.end());
    assert(aliceChildren.find(dana) != aliceChildren.end());

    // Test siblings
    std::set<Person*> charlieSiblings = charlie->siblings();
    assert(charlieSiblings.find(dana) != charlieSiblings.end());

    std::set<Person*> danaSiblings = dana->siblings();
    assert(danaSiblings.find(charlie) != danaSiblings.end());

    // Extended tests for other relations
    assert(charlie->sons().empty());

    std::cout << "All tests passed for " << filepath << "!" << std::endl;
}

int main() {
    if (fs::exists("data") && fs::is_directory("data")) {
        for (const auto& entry : fs::directory_iterator("data")) {
            if (entry.path().extension() == ".tsv") {
                testGenePool(entry.path().string());
            }
        }
    } else {
        std::cerr << "Directory 'data' does not exist or is not accessible." << std::endl;
    }
    return 0;
}
