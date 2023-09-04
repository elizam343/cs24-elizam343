#include "GenePool.h"
#include <sstream>
#include <iostream>

GenePool::GenePool(std::istream& stream) {
    readFromStream(stream);
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
        std::string name, genderStr, motherName, fatherName;
        std::stringstream ss(line);

        std::getline(ss, name, '\t');
        std::getline(ss, genderStr, '\t');
        std::getline(ss, motherName, '\t');
        std::getline(ss, fatherName, '\t');

        Gender gender;
        if (genderStr == "female") {
            gender = Gender::FEMALE;
        } else if (genderStr == "male") {
            gender = Gender::MALE;
        } else {
            gender = Gender::ANY;
        }

        // Create and insert the Person object into the people map
        Person* person = new Person(name, gender);
        people_[name] = person;

        // Handle unknown mother
        if (motherName != "???") {
            if (people_.find(motherName) != people_.end()) {
                person->setMother(people_[motherName]);
                people_[motherName]->addChild(person);
            } else {
                // Create a placeholder Person for unknown mother
                Person* unknownMother = new Person(motherName, Gender::ANY);
                people_[motherName] = unknownMother;
                person->setMother(unknownMother);
                unknownMother->addChild(person);
            }
        }

        // Handle unknown father
        if (fatherName != "???") {
            if (people_.find(fatherName) != people_.end()) {
                person->setFather(people_[fatherName]);
                people_[fatherName]->addChild(person);
            } else {
                // Create a placeholder Person for unknown father
                Person* unknownFather = new Person(fatherName, Gender::ANY);
                people_[fatherName] = unknownFather;
                person->setFather(unknownFather);
                unknownFather->addChild(person);
            }
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