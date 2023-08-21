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

void Person::addMother(Person* mother) {
    if (mother_ != nullptr) {
        // Remove this child from the old mother's set of children
        mother_->children_.erase(this);
    }
    
    mother_ = mother;
    if (mother != nullptr) {
        mother->children_.insert(this);
    }
}

void Person::addFather(Person* father) {
    if (father_ != nullptr) {
        // Remove this child from the old father's set of children
        father_->children_.erase(this);
    }
    
    father_ = father;
    if (father != nullptr) {
        father->children_.insert(this);
    }
}

void Person::addChild(Person* child) {
    children_.insert(child);
}


std::set<Person*> Person::ancestors(PMod pmod) {
    std::set<Person*> result;
    
    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if (mother_) {
            result.insert(mother_);
            auto maternalAncestors = mother_->ancestors(PMod::ANY);
            result.insert(maternalAncestors.begin(), maternalAncestors.end());
        }
    }
    
    if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if (father_) {
            result.insert(father_);
            auto paternalAncestors = father_->ancestors(PMod::ANY);
            result.insert(paternalAncestors.begin(), paternalAncestors.end());
        }
    }

    return result;
}

std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    std::set<Person*> result;

    // Fetch siblings of parents (i.e., aunts from maternal/paternal side)
    if (mother_ && (pmod == PMod::MATERNAL || pmod == PMod::ANY)) {
        auto maternalAunts = mother_->siblings(PMod::MATERNAL, smod);
        result.insert(maternalAunts.begin(), maternalAunts.end());
    }

    if (father_ && (pmod == PMod::PATERNAL || pmod == PMod::ANY)) {
        auto paternalAunts = father_->siblings(PMod::PATERNAL, smod);
        result.insert(paternalAunts.begin(), paternalAunts.end());
    }

    return result;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    // You've already got a siblings function. Use it.
    return siblings(PMod::PATERNAL, smod);
}

std::set<Person*> Person::children() {
    return children_;
}

std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
    std::set<Person*> result;
    
    // Cousins are children of aunts and uncles
    auto auntsAndUncles = this->aunts(pmod, smod);
    for (auto auntOrUncle : auntsAndUncles) {
        auto theirChildren = auntOrUncle->children();
        result.insert(theirChildren.begin(), theirChildren.end());
    }

    return result;
}

std::set<Person*> Person::daughters() {
    std::set<Person*> result;
    for (auto child : children_) {
        if (child->gender() == Gender::FEMALE) {
            result.insert(child);
        }
    }
    return result;
}

std::set<Person*> Person::descendants() {
    std::set<Person*> result;
    for (auto child : children_) {
        result.insert(child);
        auto grandDescendants = child->descendants();
        result.insert(grandDescendants.begin(), grandDescendants.end());
    }
    return result;
}

std::set<Person*> Person::grandchildren() {
    std::set<Person*> result;
    for (auto child : children_) {
        auto childChildren = child->children();
        result.insert(childChildren.begin(), childChildren.end());
    }
    return result;
}

std::set<Person*> Person::granddaughters() {
    std::set<Person*> result;
    for (auto grandchild : grandchildren()) {
        if (grandchild->gender() == Gender::FEMALE) {
            result.insert(grandchild);
        }
    }
    return result;
}

std::set<Person*> Person::grandfathers(PMod pmod) {
    std::set<Person*> result;
    if ((pmod == PMod::MATERNAL || pmod == PMod::ANY) && mother_) {
        if (mother_->father()) {
            result.insert(mother_->father());
        }
    }
    if ((pmod == PMod::PATERNAL || pmod == PMod::ANY) && father_) {
        if (father_->father()) {
            result.insert(father_->father());
        }
    }
    return result;
}

std::set<Person*> Person::grandmothers(PMod pmod) {
    std::set<Person*> result;
    if ((pmod == PMod::MATERNAL || pmod == PMod::ANY) && mother_) {
        if (mother_->mother()) {
            result.insert(mother_->mother());
        }
    }
    if ((pmod == PMod::PATERNAL || pmod == PMod::ANY) && father_) {
        if (father_->mother()) {
            result.insert(father_->mother());
        }
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
    for (auto grandchild : grandchildren()) {
        if (grandchild->gender() == Gender::MALE) {
            result.insert(grandchild);
        }
    }
    return result;
}

std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
    std::set<Person*> result;
    for (auto sibling : siblings(PMod::ANY, smod)) {
        for (auto child : sibling->children()) {
            if (child->gender() == Gender::MALE) {
                result.insert(child);
            }
        }
    }
    return result;
}

std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
    std::set<Person*> result;
    for (auto sibling : siblings(PMod::ANY, smod)) {
        for (auto child : sibling->children()) {
            if (child->gender() == Gender::FEMALE) {
                result.insert(child);
            }
        }
    }
    return result;
}

std::set<Person*> Person::parents(PMod pmod) {
    std::set<Person*> result;
    if ((pmod == PMod::MATERNAL || pmod == PMod::ANY) && mother_) {
        result.insert(mother_);
    }
    if ((pmod == PMod::PATERNAL || pmod == PMod::ANY) && father_) {
        result.insert(father_);
    }
    return result;
}

std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
    return siblings(PMod::MATERNAL, smod);
}

std::set<Person*> Person::sons() {
    std::set<Person*> result;
    for (auto child : children_) {
        if (child->gender() == Gender::MALE) {
            result.insert(child);
        }
    }
    return result;
}

std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
    std::set<Person*> result;

    if (mother_ && (pmod == PMod::MATERNAL || pmod == PMod::ANY)) {
        auto maternalUncles = mother_->siblings(PMod::PATERNAL, smod);
        result.insert(maternalUncles.begin(), maternalUncles.end());
    }

    if (father_ && (pmod == PMod::PATERNAL || pmod == PMod::ANY)) {
        auto paternalUncles = father_->siblings(PMod::PATERNAL, smod);
        result.insert(paternalUncles.begin(), paternalUncles.end());
    }

    return result;
}

std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
    std::set<Person*> result;

    // Helper lambda to filter siblings based on gender and parent.
    auto filterSiblings = [&](Person* parent, Gender gender) {
        for (Person* sibling : parent->children()) {
            if (sibling != this) {
                if ((gender == Gender::ANY) ||
                    (sibling->gender() == gender)) {
                    result.insert(sibling);
                }
            }
        }
    };

    if (mother_ && (pmod == PMod::MATERNAL || pmod == PMod::ANY)) {
        filterSiblings(mother_, Gender::ANY);
    }

    if (father_ && (pmod == PMod::PATERNAL || pmod == PMod::ANY)) {
        // To avoid adding duplicates.
        std::set<Person*> paternalSiblings;
        filterSiblings(father_, Gender::ANY);
        for (Person* sibling : paternalSiblings) {
            if (result.find(sibling) == result.end()) {
                result.insert(sibling);
            }
        }
    }

    if (smod != SMod::ANY) {
        std::set<Person*> filteredResult;
        for (Person* sibling : result) {
            if (smod == SMod::FULL && 
                ((sibling->mother() == mother_ && sibling->father() == father_) || 
                 (sibling->father() == mother_ && sibling->mother() == father_))) {
                filteredResult.insert(sibling);
            } else if (smod == SMod::HALF && 
                       (sibling->mother() != mother_ || sibling->father() != father_)) {
                filteredResult.insert(sibling);
            }
        }
        return filteredResult;
    }

    return result;
}
