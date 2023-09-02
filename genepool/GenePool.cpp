#include "GenePool.h"

GenePool::GenePool(std::istream& stream) {
    std::string line;

    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        std::string name, genderStr;
        Gender gender;

        // Assuming the input format is: NAME GENDER
        if (!(iss >> name >> genderStr)) {
            // Error in parsing, handle or continue to next line
            continue;
        }

        if (genderStr == "MALE") {
            gender = Gender::MALE;
        } else if (genderStr == "FEMALE") {
            gender = Gender::FEMALE;
        } else {
            // Invalid gender, handle or continue to next line
            continue;
        }

        Person* person = new Person(name, gender);
        mPeople[name] = person;
    }

    // After all people are created, you can loop again to assign relationships if needed.
    // Example: If you have mother and father names in the file, you would loop through again 
    // and use `find` to locate and assign the mother and father to each person.
}

GenePool::~GenePool() {
    for (auto& entry : mPeople) {
        delete entry.second;
    }
}

std::set<Person*> GenePool::everyone() const {
    std::set<Person*> allPeople;
    for (const auto& pair : mPeople) {
        allPeople.insert(pair.second);
    }
    return allPeople;
}

Person* GenePool::find(const std::string& name) const {
    auto it = mPeople.find(name);
    if (it != mPeople.end()) {
        return it->second;
    }
    return nullptr;
}
