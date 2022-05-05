#include "Police.hpp"

Police::Police(const std::string& name) : Person(name) {}

bool Police::canDrive() const {
    return true;
}
