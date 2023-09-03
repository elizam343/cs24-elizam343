#include "Query.h"
#include "Person.h"
#include "Enums.h"

#include <iostream>
#include <vector>

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
    mother->kids.insert(this);
}

void Person::setFather(Person* father) {
    p_Father = father;
    father->kids.insert(this);
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
    ancestorsSet.erase(this); // Remove self from the set of ancestors
    return ancestorsSet;
}


std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
    std::set<Person*> siblingSet;

    // Fetch maternal siblings if applicable
    if (p_Mother && (pmod == PMod::MATERNAL || pmod == PMod::ANY)) {
        for (const auto& sibling : p_Mother->children()) {
            if (sibling != this) {  // Exclude the person from the set of siblings
                siblingSet.insert(sibling);
            }
        }
    }

    // Fetch paternal siblings if applicable
    if (p_Father && (pmod == PMod::PATERNAL || pmod == PMod::ANY)) {
        for (const auto& sibling : p_Father->children()) {
            if (sibling != this) {  // Exclude the person from the set of siblings
                siblingSet.insert(sibling);
            }
        }
    }

    // Handle HALF siblings if necessary
    if (smod == SMod::HALF) {
        std::set<Person*> maternalSiblings, paternalSiblings;
        
        if (p_Mother && (pmod == PMod::MATERNAL || pmod == PMod::ANY)) {
            maternalSiblings = p_Mother->children();
            maternalSiblings.erase(this); // Exclude the person from maternal siblings
        }

        if (p_Father && (pmod == PMod::PATERNAL || pmod == PMod::ANY)) {
            paternalSiblings = p_Father->children();
            paternalSiblings.erase(this); // Exclude the person from paternal siblings
        }

        for (const auto& sibling : maternalSiblings) {
            if (paternalSiblings.find(sibling) == paternalSiblings.end()) {
                siblingSet.insert(sibling);
            }
        }
        for (const auto& sibling : paternalSiblings) {
            if (maternalSiblings.find(sibling) == maternalSiblings.end()) {
                siblingSet.insert(sibling);
            }
        }
    }

    return siblingSet;
}




std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    std::set<Person*> auntSet;

    // Maternal aunts
    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if (p_Mother) {
            auto motherSisters = p_Mother->sisters(pmod, smod);
            auntSet.insert(motherSisters.begin(), motherSisters.end());
        }
    }

    // Paternal aunts
    if (pmod != PMod::MATERNAL && (pmod == PMod::PATERNAL || pmod == PMod::ANY)) {
        if (p_Father) {
            auto fatherSisters = p_Father->sisters(pmod, smod);
            auntSet.insert(fatherSisters.begin(), fatherSisters.end());
        }
    }

    return auntSet;
}



std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
    std::set<Person*> result;
    if (p_Mother && (pmod == PMod::MATERNAL || pmod == PMod::ANY)) {
        auto maternalUncles = p_Mother->brothers(pmod, smod);
        result.insert(maternalUncles.begin(), maternalUncles.end());
    }
    if (p_Father && (pmod == PMod::PATERNAL || pmod == PMod::ANY)) {
        auto paternalUncles = p_Father->brothers(pmod, smod);
        result.insert(paternalUncles.begin(), paternalUncles.end());
    }
    return result;
}



std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    std::set<Person*> siblingSet = siblings(pmod, smod);

    // Filter out female siblings
    for (auto it = siblingSet.begin(); it != siblingSet.end();) {
        if ((*it)->gender() != Gender::MALE) {
            it = siblingSet.erase(it);
        } else {
            ++it;
        }
    }

    return siblingSet;
}





std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
    std::set<Person*> cousinSet;

    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if (p_Mother) {
            for (auto auntOrUncle : p_Mother->siblings(pmod, smod)) {
                for (auto child : auntOrUncle->children()) {
                    cousinSet.insert(child);
                }
            }
        }
    }

    if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if (p_Father) {
            for (auto auntOrUncle : p_Father->siblings(pmod, smod)) {
                for (auto child : auntOrUncle->children()) {
                    cousinSet.insert(child);
                }
            }
        }
    }

    return cousinSet;
}


std::set<Person*> Person::daughters() {
    std::set<Person*> result;
    for (auto child : kids) {
        if (child->gender() == Gender::FEMALE) {
            result.insert(child);
        }
    }
    return result;
}

std::set<Person*> Person::descendants() {
    std::set<Person*> result;
    for (auto child : kids) {
        result.insert(child);
        auto grandChildren = child->descendants();
        result.insert(grandChildren.begin(), grandChildren.end());
    }
    return result;
}

std::set<Person*> Person::grandchildren() {
    std::set<Person*> result;
    for (auto child : kids) {
        auto grandChildren = child->children();
        result.insert(grandChildren.begin(), grandChildren.end());
    }
    return result;
}

std::set<Person*> Person::granddaughters() {
    std::set<Person*> result;
    for (auto child : kids) {
        auto childDaughters = child->daughters();
        result.insert(childDaughters.begin(), childDaughters.end());
    }
    return result;
}

std::set<Person*> Person::grandfathers(PMod pmod) {
    std::set<Person*> result;
    if (p_Mother && (pmod == PMod::MATERNAL || pmod == PMod::ANY)) {
        if (p_Mother->father()) result.insert(p_Mother->father());
    }
    if (p_Father && (pmod == PMod::PATERNAL || pmod == PMod::ANY)) {
        if (p_Father->father()) result.insert(p_Father->father());
    }
    return result;
}

std::set<Person*> Person::grandmothers(PMod pmod) {
    std::set<Person*> result;
    if (p_Mother && (pmod == PMod::MATERNAL || pmod == PMod::ANY)) {
        if (p_Mother->mother()) result.insert(p_Mother->mother());
    }
    if (p_Father && (pmod == PMod::PATERNAL || pmod == PMod::ANY)) {
        if (p_Father->mother()) result.insert(p_Father->mother());
    }
    return result;
}

std::set<Person*> Person::grandparents(PMod pmod) {
    std::set<Person*> result;
    auto gFathers = grandfathers(pmod);
    auto gMothers = grandmothers(pmod);
    result.insert(gFathers.begin(), gFathers.end());
    result.insert(gMothers.begin(), gMothers.end());
    return result;
}

std::set<Person*> Person::grandsons() {
    std::set<Person*> result;
    for (auto child : kids) {
        auto childSons = child->sons();
        result.insert(childSons.begin(), childSons.end());
    }
    return result;
}

std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
    std::set<Person*> result;
    auto sibs = siblings(pmod, smod);
    for (auto sibling : sibs) {
        auto sibSons = sibling->sons();
        result.insert(sibSons.begin(), sibSons.end());
    }
    return result;
}


std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
    std::set<Person*> result;
    auto sibs = siblings(pmod, smod);
    for (auto sibling : sibs) {
        auto sibDaughters = sibling->daughters();
        result.insert(sibDaughters.begin(), sibDaughters.end());
    }
    return result;
}


std::set<Person*> Person::parents(PMod pmod) {
    std::set<Person*> result;
    if (p_Mother && (pmod == PMod::MATERNAL || pmod == PMod::ANY)) {
        result.insert(p_Mother);
    }
    if (p_Father && (pmod == PMod::PATERNAL || pmod == PMod::ANY)) {
        result.insert(p_Father);
    }
    return result;
}

std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
    std::set<Person*> siblingSet = siblings(pmod, smod);

    // Filter out male siblings and exclude the person itself
    siblingSet.erase(this); // Remove self from the set of siblings
    for (auto it = siblingSet.begin(); it != siblingSet.end();) {
        if ((*it)->gender() != Gender::FEMALE) {
            it = siblingSet.erase(it);
        } else {
            ++it;
        }
    }

    return siblingSet;
}




std::set<Person*> Person::sons() {
    std::set<Person*> result;
    for (auto child : kids) {
        if (child->gender() == Gender::MALE) {
            result.insert(child);
        }
    }
    return result;
}
