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
    GenePool genePool("data/simpsons_family.tsv");
    Person* homer = genePool.find("Homer");
    assert(homer);
    std::set<Person*> homerBrothers = homer->brothers(PMod::ANY, SMod::ANY);

    std::cout << "Homer's brothers:" << std::endl;
    for (const auto& brother : homerBrothers) {
        std::cout << " - " << brother->name() << std::endl;
    }
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
