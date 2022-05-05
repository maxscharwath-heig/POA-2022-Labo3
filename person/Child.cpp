#include "Child.hpp"

Child::Child(const std::string& name, Gender gender) : GenderedPerson(name, gender) {

}

bool Child::canDrive() const {
    return false;
}
