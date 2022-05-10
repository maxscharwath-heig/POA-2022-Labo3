#include "Person.hpp"

Person::Person(const std::string& name) : _name(name) {}

std::ostream& Person::toStream(std::ostream& os) const {
    return os << _name;
}

const std::string& Person::getName() const {
    return _name;
}
