#include "Person.h"

Person::Person(const std::string& name, Gender gender)
    : name_(name), gender_(gender), mother_(nullptr), father_(nullptr) {
}

Person::~Person() {
    // Handle any cleanup if necessary
}

const std::string& Person::name() const {
    return name_;
}

Gender Person::gender() const {
    return gender_;
}

Person* Person::mother() {
    return mother_;
}

Person* Person::father() {
    return father_;
}

// Implement other relationship functions...

// ...For example, siblings:
std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
    std::set<Person*> result;
    
    // Example logic: 
    // If mother exists and has children, add those children to the result 
    // (similar logic for father). Make sure to remove "this" person from the result.
    // Consider pmod and smod to filter the results further.

    return result;
}

