#include "Parent.hpp"

Parent::Parent(const std::string& name, Gender gender) : GenderedPerson(name, gender) {
}

bool Parent::canDrive() const {
    return true;
}
