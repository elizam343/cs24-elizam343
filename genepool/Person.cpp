#include "Person.h"

// Constructor
Person::Person(const std::string& name, Gender gender, Person* mother, Person* father)
    : p_Name(name), p_Gender(gender), p_Mother(mother), p_Father(father) {}

// Destructor
Person::~Person() {
    // any cleanup logic, if necessary
}

const std::string& Person::name() const {
    return p_Name;
}

Gender Person::gender() const {
    return p_Gender;
}

Person* Person::mother() {
    return p_Mother;
}

Person* Person::father() {
    return p_Father;
}

void Person::addChild(Person* child) {
    kids.insert(child);
}

void Person::setMother(Person* mother) {
    p_Mother = mother;
}

void Person::setFather(Person* father) {
    p_Father = father;
}

std::set<Person*> Person::children() {
    return kids;
}

void Person::findAncestors(std::set<Person*>& ancestorsSet, PMod pmod) const {
    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if (p_Mother) {
            ancestorsSet.insert(p_Mother);
            p_Mother->findAncestors(ancestorsSet, pmod);
        }
    }
    if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if (p_Father) {
            ancestorsSet.insert(p_Father);
            p_Father->findAncestors(ancestorsSet, pmod);
        }
    }
}

std::set<Person*> Person::ancestors(PMod pmod) {
    std::set<Person*> ancestorsSet;
    findAncestors(ancestorsSet, pmod);
    return ancestorsSet;
}

// Here's a basic outline for siblings, as an example:
std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
    std::set<Person*> siblingSet;
    if (p_Mother) {
        siblingSet.insert(p_Mother->children().begin(), p_Mother->children().end());
    }
    if (p_Father) {
        siblingSet.insert(p_Father->children().begin(), p_Father->children().end());
    }
    siblingSet.erase(this); // Remove self from the set of siblings

    // Further logic needed for SMod differentiation (FULL, HALF, ANY)
    return siblingSet;
}

std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    std::set<Person*> auntSet;

    if (p_Mother) {
        for (auto sibling : p_Mother->siblings(PMod::ANY, smod)) {
            if (sibling->gender() == Gender::FEMALE) {
                auntSet.insert(sibling);
            }
        }
    }

    if (pmod != PMod::MATERNAL && p_Father) {
        for (auto sibling : p_Father->siblings(PMod::ANY, smod)) {
            if (sibling->gender() == Gender::FEMALE) {
                auntSet.insert(sibling);
            }
        }
    }

    return auntSet;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    std::set<Person*> brotherSet;

    auto siblingsSet = siblings(pmod, smod);
    for (auto sibling : siblingsSet) {
        if (sibling->gender() == Gender::MALE) {
            brotherSet.insert(sibling);
        }
    }

    return brotherSet;
}

std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
    std::set<Person*> cousinSet;

    if (p_Mother) {
        for (auto auntOrUncle : p_Mother->siblings(PMod::ANY, smod)) {
            for (auto child : auntOrUncle->children()) {
                cousinSet.insert(child);
            }
        }
    }

    if (pmod != PMod::MATERNAL && p_Father) {
        for (auto auntOrUncle : p_Father->siblings(PMod::ANY, smod)) {
            for (auto child : auntOrUncle->children()) {
                cousinSet.insert(child);
            }
        }
    }

    return cousinSet;
}
