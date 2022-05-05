#include "Person.hpp"

Person::Person(const std::string& name): name(name) {}

std::ostream& Person::toStream(std::ostream& os) const {
    return os << name;
}