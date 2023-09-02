#include "Person.h"

// Constructor
Person::Person(const std::string& name, Gender gender)
    : mName(name), mGender(gender), mMother(nullptr), mFather(nullptr) {}

const std::string& Person::name() const {
    return mName;
}

Gender Person::gender() const {
    return mGender;
}

Person* Person::mother() {
    return mMother;
}

Person* Person::father() {
    return mFather;
}

void Person::setMother(Person* mother) {
    mMother = mother;
}

void Person::setFather(Person* father) {
    mFather = father;
}

void Person::addChild(Person* child) {
    mChildren.insert(child);
}


std::set<Person*> Person::ancestors(PMod pmod) {
    std::set<Person*> result;

    if ((pmod == PMod::ANY || pmod == PMod::MATERNAL) && mMother) {
        result.insert(mMother);
        auto maternalAncestors = mMother->ancestors(PMod::ANY);
        result.insert(maternalAncestors.begin(), maternalAncestors.end());
    }

    if ((pmod == PMod::ANY || pmod == PMod::PATERNAL) && mFather) {
        result.insert(mFather);
        auto paternalAncestors = mFather->ancestors(PMod::ANY);
        result.insert(paternalAncestors.begin(), paternalAncestors.end());
    }

    return result;
}

// Siblings
std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
    std::set<Person*> result;

    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        for (auto sib : mMother->children()) {
            if (sib != this && 
                (smod == SMod::ANY || 
                 (smod == SMod::FULL && sib->father() == mFather) ||
                 (smod == SMod::HALF && sib->father() != mFather))) {
                result.insert(sib);
            }
        }
    }

    if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        for (auto sib : mFather->children()) {
            if (sib != this && 
                (smod == SMod::ANY || 
                 (smod == SMod::FULL && sib->mother() == mMother) ||
                 (smod == SMod::HALF && sib->mother() != mMother))) {
                result.insert(sib);
            }
        }
    }

    return result;
}

std::set<Person*> Person::children() {
    return mChildren;
}

std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
    std::set<Person*> result;

    // Using SMod::ANY to get all aunts and uncles, irrespective of FULL or HALF
    auto auntsAndUncles = this->aunts(pmod, SMod::ANY);
    auto uncles = this->uncles(pmod, SMod::ANY);
    auntsAndUncles.insert(uncles.begin(), uncles.end()); // Combine aunts and uncles

    for (auto relative : auntsAndUncles) {
        for (auto child : relative->children()) { // Assuming you have children function for Person class
            if (smod == SMod::ANY ||
                (smod == SMod::FULL && 
                 (child->mother() == relative->mother() && child->father() == relative->father())) ||
                (smod == SMod::HALF && 
                 !(child->mother() == relative->mother() && child->father() == relative->father()))) {
                result.insert(child);
            }
        }
    }

    return result;
}



std::set<Person*> Person::daughters() {
    std::set<Person*> result;
    for (auto child : mChildren) {
        if (child->gender() == Gender::FEMALE) {
            result.insert(child);
        }
    }
    return result;
}

std::set<Person*> Person::sons() {
    std::set<Person*> result;
    for (auto child : mChildren) {
        if (child->gender() == Gender::MALE) {
            result.insert(child);
        }
    }
    return result;
}

// Descendants (Direct children + descendants of children)
std::set<Person*> Person::descendants() {
    std::set<Person*> result = mChildren;
    for (auto child : mChildren) {
        auto grandChildren = child->descendants();
        result.insert(grandChildren.begin(), grandChildren.end());
    }
    return result;
}

// Grandchildren
std::set<Person*> Person::grandchildren() {
    std::set<Person*> result;
    for (auto child : mChildren) {
        result.insert(child->children().begin(), child->children().end());
    }
    return result;
}

// Granddaughters and Grandsons
std::set<Person*> Person::granddaughters() {
    std::set<Person*> result;
    for (auto grandchild : grandchildren()) {
        if (grandchild->gender() == Gender::FEMALE) {
            result.insert(grandchild);
        }
    }
    return result;
}

std::set<Person*> Person::grandsons() {
    std::set<Person*> result;
    for (auto grandchild : grandchildren()) {
        if (grandchild->gender() == Gender::MALE) {
            result.insert(grandchild);
        }
    }
    return result;
}

// Grandparents
std::set<Person*> Person::grandparents(PMod pmod) {
    std::set<Person*> result;
    if ((pmod == PMod::ANY || pmod == PMod::MATERNAL) && mMother) {
        result.insert(mMother->parents(PMod::ANY).begin(), mMother->parents(PMod::ANY).end());
    }
    if ((pmod == PMod::ANY || pmod == PMod::PATERNAL) && mFather) {
        result.insert(mFather->parents(PMod::ANY).begin(), mFather->parents(PMod::ANY).end());
    }
    return result;
}

// Specific Grandparents
std::set<Person*> Person::grandfathers(PMod pmod) {
    std::set<Person*> result;
    for (auto gp : grandparents(pmod)) {
        if (gp->gender() == Gender::MALE) {
            result.insert(gp);
        }
    }
    return result;
}

std::set<Person*> Person::grandmothers(PMod pmod) {
    std::set<Person*> result;
    for (auto gp : grandparents(pmod)) {
        if (gp->gender() == Gender::FEMALE) {
            result.insert(gp);
        }
    }
    return result;
}

// Aunts and Uncles
std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    std::set<Person*> result;
    auto sibs = siblings(pmod, smod);
    for (auto sib : sibs) {
        if (sib->gender() == Gender::FEMALE) {
            result.insert(sib);
        }
    }
    return result;
}

std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
    std::set<Person*> result;
    auto sibs = siblings(pmod, smod);
    for (auto sib : sibs) {
        if (sib->gender() == Gender::MALE) {
            result.insert(sib);
        }
    }
    return result;
}

// Nephews and Nieces
std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
    std::set<Person*> result;
    auto sibs = siblings(pmod, SMod::ANY); // Getting all siblings irrespective of FULL/HALF
    for (auto sib : sibs) {
        for (auto child : sib->children()) {
            if (child->gender() == Gender::MALE && 
                (smod == SMod::ANY || 
                 (smod == SMod::FULL && (child->mother() == sib->mother() && child->father() == sib->father())) ||
                 (smod == SMod::HALF && !(child->mother() == sib->mother() && child->father() == sib->father())))) {
                result.insert(child);
            }
        }
    }
    return result;
}

std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
    std::set<Person*> result;
    auto sibs = siblings(pmod, SMod::ANY); // Getting all siblings irrespective of FULL/HALF
    for (auto sib : sibs) {
        for (auto child : sib->children()) {
            if (child->gender() == Gender::FEMALE && 
                (smod == SMod::ANY || 
                 (smod == SMod::FULL && (child->mother() == sib->mother() && child->father() == sib->father())) ||
                 (smod == SMod::HALF && !(child->mother() == sib->mother() && child->father() == sib->father())))) {
                result.insert(child);
            }
        }
    }
    return result;
}

// Parents
std::set<Person*> Person::parents(PMod pmod) {
    std::set<Person*> result;
    if ((pmod == PMod::ANY || pmod == PMod::MATERNAL) && mMother) {
        result.insert(mMother);
    }
    if ((pmod == PMod::ANY || pmod == PMod::PATERNAL) && mFather) {
        result.insert(mFather);
    }
    return result;
}