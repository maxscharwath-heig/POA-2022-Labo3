#include "GenderedPerson.hpp"

GenderedPerson::GenderedPerson(const std::string& name, Gender gender): Person(name), gender(gender) {}

Gender GenderedPerson::getGender() {
    return gender;
}

bool GenderedPerson::canDrive() const {
    return true;
}
