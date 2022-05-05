#include "Thief.hpp"

Thief::Thief(const std::string& name) : Person(name) {

}

bool Thief::canDrive() const {
    return false;
}
