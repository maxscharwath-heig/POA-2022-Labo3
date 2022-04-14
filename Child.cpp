#include "Child.hpp"

Child::Child(const std::string& name) : Person(name) {}

bool Child::canDrive() {
    return false;
}
