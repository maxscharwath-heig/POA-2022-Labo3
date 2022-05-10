#include <algorithm>
#include "Container.hpp"

std::ostream& operator<<(std::ostream& os, const Container& container) {
    return container.toStream(os);
}

Container::Container(const std::string& name) : _name(name) {}

bool Container::add(const Person* person) {
    if (isAlreadyOnBoard(person)) {
        return false;
    }

    _onBoard.push_back(person);
    return true;
}

void Container::add(std::initializer_list<const Person*> people) {
    for (const Person* p: people) {
        add(p);
    }
}

void Container::add(const std::list<const Person*>& people) {
    for (const Person* p: people) {
        add(p);
    }
}

const std::string& Container::getName() const {
    return _name;
}

const std::list<const Person*>& Container::getPeople() const {
    return _onBoard;
}

void Container::remove(const Person* person) {
    _onBoard.remove(person);
}

void Container::clear() {
    _onBoard.clear();
}

bool Container::isAlreadyOnBoard(const Person* p) const {
    return std::find(_onBoard.begin(), _onBoard.end(), p) != _onBoard.end();
}


