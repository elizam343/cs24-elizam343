#include "County.h"

County::County(const std::string& _name) : name(_name) {}

std::string County::getName() const {
    return name;
}
