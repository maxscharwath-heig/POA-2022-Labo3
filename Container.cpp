#include "Container.hpp"

std::ostream& operator<<(std::ostream& os, const Container& container) {
   return container.toStream(os);
}

Container::Container(const std::string& name) : name(name) {}

Container::~Container() {
   while (!onBoard.empty()) {
      delete onBoard.front();
      onBoard.pop_front();
   }
}

bool Container::add(Person* person) {
   onBoard.push_back(person);
   return true;
}

const std::string& Container::getName() const {
   return name;
}

std::list<Person*>& Container::getPeople() {
   return onBoard;
}

void Container::add(std::initializer_list<Person*> people) {
   for (Person* p: people) {
      add(p);
   }
}

void Container::remove(Person* person) {
   onBoard.remove(person);
}
