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

std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
    std::set<Person*> result;

    if (mMother && (pmod == PMod::MATERNAL || pmod == PMod::ANY)) {
        for (auto sib : mMother->children()) {
            if (sib != this && 
                (smod == SMod::ANY || 
                 (smod == SMod::FULL && sib->father() == mFather) ||
                 (smod == SMod::HALF && sib->father() != mFather))) {
                result.insert(sib);
            }
        }
    }

    if (mFather && (pmod == PMod::PATERNAL || pmod == PMod::ANY)) {
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

    auto auntsAndUncles = this->aunts(pmod, SMod::ANY);
    auto unclesSet = this->uncles(pmod, SMod::ANY);
    auntsAndUncles.insert(unclesSet.begin(), unclesSet.end());

    for (auto relative : auntsAndUncles) {
        for (auto child : relative->children()) {
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

std::set<Person*> Person::descendants() {
    std::set<Person*> result = mChildren;
    for (auto child : mChildren) {
        auto grandChildren = child->descendants();
        result.insert(grandChildren.begin(), grandChildren.end());
    }
    return result;
}

std::set<Person*> Person::grandchildren() {
    std::set<Person*> result;
    for (auto child : mChildren) {
        result.insert(child->children().begin(), child->children().end());
    }
    return result;
}

std::set<Person*> Person::granddaughters() {
    std::set<Person*> result;
    auto allGrandchildren = grandchildren();
    for (auto grandchild : allGrandchildren) {
        if (grandchild->gender() == Gender::FEMALE) {
            result.insert(grandchild);
        }
    }
    return result;
}

std::set<Person*> Person::grandsons() {
    std::set<Person*> result;
    auto allGrandchildren = grandchildren();
    for (auto grandchild : allGrandchildren) {
        if (grandchild->gender() == Gender::MALE) {
            result.insert(grandchild);
        }
    }
    return result;
}

std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    std::set<Person*> result;

    if ((pmod == PMod::MATERNAL || pmod == PMod::ANY) && mMother) {
        auto maternalSiblings = mMother->siblings(PMod::ANY, SMod::ANY);
        for (auto sib : maternalSiblings) {
            if (sib->gender() == Gender::FEMALE) {
                result.insert(sib);
            }
        }
    }

    if ((pmod == PMod::PATERNAL || pmod == PMod::ANY) && mFather) {
        auto paternalSiblings = mFather->siblings(PMod::ANY, SMod::ANY);
        for (auto sib : paternalSiblings) {
            if (sib->gender() == Gender::FEMALE) {
                result.insert(sib);
            }
        }
    }

    return result;
}

std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
    std::set<Person*> result;

    if ((pmod == PMod::MATERNAL || pmod == PMod::ANY) && mMother) {
        auto maternalSiblings = mMother->siblings(PMod::ANY, SMod::ANY);
        for (auto sib : maternalSiblings) {
            if (sib->gender() == Gender::MALE) {
                result.insert(sib);
            }
        }
    }

    if ((pmod == PMod::PATERNAL || pmod == PMod::ANY) && mFather) {
        auto paternalSiblings = mFather->siblings(PMod::ANY, SMod::ANY);
        for (auto sib : paternalSiblings) {
            if (sib->gender() == Gender::MALE) {
                result.insert(sib);
            }
        }
    }

    return result;
}
