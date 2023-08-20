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
    while (std::getline(stream, line)) {
        // Parse the TSV lines and create new Person objects.
        // For simplicity, let's assume the format is "name\tgender".
        std::string name, genderStr;
        std::stringstream ss(line);

        std::getline(ss, name, '\t');
        std::getline(ss, genderStr, '\t');

        Gender gender = (genderStr == "Male" ? Gender::MALE : Gender::FEMALE);
        
        // For now, creating a new Person with just name and gender.
        Person* person = new Person(name, gender);
        
        people_[name] = person;
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
