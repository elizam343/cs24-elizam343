#include "GenePool.h"
#include <sstream>
#include <iostream>

GenePool::GenePool(std::istream& stream) {
    std::string line;

    while (std::getline(stream, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }
        std::string name;
        std::string genderStr; // Assuming Gender is represented as a string
        std::string fatherName;
        std::string motherName;

        std::istringstream lineStream(line);

        // Extract tab-separated values from the line
        std::getline(lineStream, name, '\t');
        std::getline(lineStream, genderStr, '\t');
        std::getline(lineStream, motherName, '\t');
        std::getline(lineStream, fatherName);

        Gender gender; 

        if (genderStr == "male") {
            gender = Gender::MALE;
        } else if (genderStr == "female") {
            gender = Gender::FEMALE;
        } else {
            gender = Gender::ANY;
        }

        // Create and insert the Person object into the people set
        Person* mother = find(motherName);
        Person* father = find(fatherName);
        Person* new_person = new Person(name, gender);
        people_[name] = new_person;

        if (mother) {
            new_person->setMother(mother);
            mother->addChild(new_person);
        }
        if (father) {
            new_person->setFather(father);
            father->addChild(new_person);
        }
    }
}

GenePool::~GenePool() {
    // Delete the people allocated on the heap.
    for (auto& pair : people_) {
        delete pair.second;
    }
}

void GenePool::readFromStream(std::istream& stream) {
    std::string line;
    // First pass: Create Person objects for everyone
    while (std::getline(stream, line)) {
        std::string name, genderStr;
        std::stringstream ss(line);

        std::getline(ss, name, '\t');
        std::getline(ss, genderStr, '\t');

        Gender gender;
        if (genderStr == "female") {
            gender = Gender::FEMALE;
        } else if (genderStr == "male") {
            gender = Gender::MALE;
        } else {
            gender = Gender::ANY;
        }


        
        if (people_.find(name) == people_.end()) {
            Person* person = new Person(name, gender);
            people_[name] = person;
        } else {
            // Handle duplicate person or simply skip
            // For now, we'll just skip.
        }
    }

    // Reset stream position to beginning for second pass
    stream.clear();  // Clear EOF flag
    stream.seekg(0, std::ios::beg); 

    // Second pass: Establish parent-child relationships
    while (std::getline(stream, line)) {
        std::string name, genderStr, motherName, fatherName;
        std::stringstream ss(line);

        std::getline(ss, name, '\t');
        std::getline(ss, genderStr, '\t');
        std::getline(ss, motherName, '\t');
        std::getline(ss, fatherName, '\t');

        if (people_.find(motherName) != people_.end()) {
            people_[name]->setMother(people_[motherName]);
        }

        if (people_.find(fatherName) != people_.end()) {
            people_[name]->setFather(people_[fatherName]);
        }
    }
}


std::set<Person*> GenePool::everyone() const {
    std::set<Person*> result;
    for (const auto& pair : people_) {
        result.insert(pair.second);
    }
    return result;
}

Person* GenePool::find(const std::string& name) const {
    auto it = people_.find(name);
    if (it != people_.end()) {
        return it->second;
    }
    return nullptr;
}