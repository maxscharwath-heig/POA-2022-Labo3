#include "Container.hpp"

std::ostream& operator<<(std::ostream& os, const Container& container) {
   return container.toStream(os);
}

Container::Container(const std::string& name) : name(name) {}

bool Container::add(Person* person) {
   onBoard.push_back(person);
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
   return name;
}

const std::list<Person*>& Container::getPeople() const {
   return onBoard;
}

void Container::remove(Person* person) {
   onBoard.remove(person);
}

void Container::clear() {
   onBoard.clear();
}


