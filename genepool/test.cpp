#include "Person.h"
#include "GenePool.h"
#include <iostream>
#include <fstream>
#include <cassert>

void printAncestors(const std::set<Person*>& ancestors) {
    std::cout << "Ancestors:" << std::endl;
    for (const auto& ancestor : ancestors) {
        std::cout << " - " << ancestor->name() << std::endl;
    }
}

void testBrothers() {
    // Create the GenePool from a sample TSV file
    std::ifstream inputFile("sample_family_tree.tsv");
    GenePool genePool(inputFile);

    // Find the Person you want to test
    Person* homer = genePool.find("Homer");

    // Test brothers for Homer
    std::set<Person*> homerBrothers = homer->brothers(PMod::ANY, SMod::ANY);

    // Print out the results
    std::cout << "Brothers of Homer:" << std::endl;
    for (const auto& brother : homerBrothers) {
        std::cout << " - " << brother->name() << std::endl;
    }

    // You can now add assertions based on your expected results
    // For example:
    assert(homerBrothers.size() == 2); // Homer has two brothers: Herbert and Abbey
}

int main() {
    std::ifstream inputFile("data/Simpsons.tsv");

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        return 1;
    }

    GenePool genePool(inputFile);

    // Debugging specific functions
    Person* homer = genePool.find("Homer");
    if (homer) {
        std::set<Person*> homerAncestors = homer->ancestors(PMod::ANY);
        printAncestors(homerAncestors);
    } else {
        std::cerr << "Homer Simpson not found." << std::endl;
    }

    // Debug other functions here...
    testBrothers();

    return 0;
}
