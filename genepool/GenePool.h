#ifndef GENEPOOL_H
#define GENEPOOL_H

#include "Person.h"

#include <istream>
#include <set>
#include <string>
#include <map>
#include <sstream>  // required for std::istringstream

class GenePool {
private:
    std::map<std::string, Person*> mPeople;

public:
    // Constructor to build a database of people from a TSV file.
    GenePool(std::istream& stream);

    // Destructor to clean up allocated memory.
    ~GenePool();

    // Function to list all the people in the database.
    std::set<Person*> everyone() const;

    // Function to find a person in the database by name.
    Person* find(const std::string& name) const;
};

#endif
