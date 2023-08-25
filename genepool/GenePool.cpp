#include "GenePool.h"
#include <sstream>

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
        std::string name, genderStr;
        std::stringstream ss(line);

        std::getline(ss, name, '\t');
        std::getline(ss, genderStr, '\t');

        Gender gender = (genderStr == "Male" ? Gender::MALE : Gender::FEMALE);
        
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

        if (!motherName.empty() && people_.find(motherName) != people_.end()) {
            people_[name]->setMother(people_[motherName]);
            std::cout << name << "'s mother is set to: " << motherName << std::endl;  // debug output
        } else if (!motherName.empty()) {
            std::cout << "Could not find mother: " << motherName << " for person: " << name << std::endl;  // debug output
        }

        if (!fatherName.empty() && people_.find(fatherName) != people_.end()) {
            people_[name]->setFather(people_[fatherName]);
            std::cout << name << "'s father is set to: " << fatherName << std::endl;  // debug output
        } else if (!fatherName.empty()) {
            std::cout << "Could not find father: " << fatherName << " for person: " << name << std::endl;  // debug output
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
