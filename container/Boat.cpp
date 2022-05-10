#include <iostream>
#include <algorithm>
#include "Boat.hpp"

const unsigned Boat::MAX_CAPACITY = 2;

Boat::Boat(const std::string& name, Bank* bank) : Container(name), currentBank(bank) {}

void Boat::setCurrentBank(Bank* bank) {
   currentBank = bank;
}

std::ostream& Boat::toStream(std::ostream& os) const {
   os << getName() << "< ";
   for (auto it = onBoard.begin(); it != onBoard.end(); ++it) {
      (*it)->toStream(os);
      if (it != std::prev(onBoard.end())) {
         os << " ";
      }
   }
   return os << " >";
}

bool Boat::hasDriver() const {
   return std::find_if(onBoard.begin(), onBoard.end(), [](const Person* p) { return p->canDrive(); }) != onBoard.end();
}

bool Boat::add(Person* p) {
   if (onBoard.size() == MAX_CAPACITY || std::find(onBoard.begin(), onBoard.end(), p) != onBoard.end()) {
      std::cout << "### Il n'y a plus de place dans le bateau" << std::endl;
      return false;
   }
   onBoard.push_back(p);
   return true;
}
