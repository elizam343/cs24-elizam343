#include "GenePool.h"

#include "GenePool.h"

GenePool::GenePool(std::istream& stream) {
    std::map<std::string, std::pair<std::string, std::string>> parentNames;  // to store mother and father names for each person

    std::string line;
    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        std::string name, genderStr, motherName, fatherName;
        Gender gender;

        std::getline(iss, name, '\t');
        std::getline(iss, genderStr, '\t');
        std::getline(iss, motherName, '\t');
        std::getline(iss, fatherName, '\t');

        if (genderStr == "MALE") {
            gender = Gender::MALE;
        } else if (genderStr == "FEMALE") {
            gender = Gender::FEMALE;
        } else {
            // Error handling or skip
            continue;
        }

        Person* person = new Person(name, gender);  // Assuming Person has this constructor
        mPeople[name] = person;
        
        parentNames[name] = {motherName, fatherName};  // store mother and father names for linkage later
    }

    // Link parents after populating all persons
    for (const auto& [name, person] : mPeople) {
        const auto& [motherName, fatherName] = parentNames[name];  // extract mother and father names

        if (mPeople.find(motherName) != mPeople.end()) {
            person->setMother(mPeople[motherName]);  // set mother
        }
        if (mPeople.find(fatherName) != mPeople.end()) {
            person->setFather(mPeople[fatherName]);  // set father
        }
    }
}

GenePool::~GenePool() {
    for (auto& [name, person] : mPeople) {
        delete person;
    }
}

std::set<Person*> GenePool::everyone() const {
    std::set<Person*> result;
    for (const auto& [name, person] : mPeople) {
        result.insert(person);
    }
    return result;
}

Person* GenePool::find(const std::string& name) const {
    if (mPeople.find(name) != mPeople.end()) {
        return mPeople.at(name);
    }
    return nullptr;
}


GenePool::~GenePool() {
    for (auto& [name, person] : mPeople) {
        delete person;
    }
}

std::set<Person*> GenePool::everyone() const {
    std::set<Person*> result;
    for (const auto& [name, person] : mPeople) {
        result.insert(person);
    }
    return result;
}

Person* GenePool::find(const std::string& name) const {
    if (mPeople.find(name) != mPeople.end()) {
        return mPeople.at(name);
    }
    return nullptr;
}
