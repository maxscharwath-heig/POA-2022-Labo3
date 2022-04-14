#include "Container.hpp"

Container::Container(const std::string& name): name(name) {}

void Container::add(Person* person) {
    onBoard.push_back(person);
}
