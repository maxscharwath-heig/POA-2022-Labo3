#include "Container.hpp"

std::ostream& operator<<(std::ostream& os, const Container& container) {
   return container.toStream(os);
}

Container::Container(const std::string& name) : _name(name) {}

bool Container::add(Person* person) {
   _onBoard.push_back(person);
   return true;
}

void Container::add(std::initializer_list<Person*> people) {
   for (Person* p: people) {
      add(p);
   }
}

void Container::add(const std::list<Person*>& people) {
   for (Person* p: people) {
      add(p);
   }
}

const std::string& Container::getName() const {
   return _name;
}

const std::list<Person*>& Container::getPeople() const {
   return _onBoard;
}

void Container::remove(Person* person) {
   _onBoard.remove(person);
}

void Container::clear() {
   _onBoard.clear();
}


