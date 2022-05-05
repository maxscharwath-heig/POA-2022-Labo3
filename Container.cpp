#include "Container.hpp"

std::ostream& operator<<(std::ostream& os, const Container& container) {
    return container.toStream(os);
}

Container::Container(const std::string& name): name(name) {}

Container::~Container() {
    while(!onBoard.empty()) {
        delete onBoard.front();
        onBoard.pop_front();
    }
}

void Container::add(Person* person) {
    onBoard.push_back(person);
}

const std::string& Container::getName() const {
    return name;
}
