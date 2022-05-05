#include "Container.hpp"

std::ostream& operator<<(std::ostream& os, const Container& container) {
    return container.toStream(os);
}

Container::Container(const std::string& name): name(name) {}

void Container::add(Person* person) {
    onBoard.push_back(person);
}

const std::string& Container::getName() const {
    return name;
}

std::list<Person*>& Container::getPeople() {
    return onBoard;
}
