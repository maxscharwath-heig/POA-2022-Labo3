#include <iostream>
#include <algorithm>
#include "Boat.hpp"

const unsigned Boat::MAX_CAPACITY = 2;

Boat::Boat(const std::string& name, Bank* bank) : Container(name), _currentBank(bank) {}

void Boat::setCurrentBank(Bank* bank) {
   _currentBank = bank;
}

Bank* Boat::getCurrentBank() const {
   return _currentBank;
}

bool Boat::hasDriver() const {
   return std::find_if(_onBoard.begin(), _onBoard.end(), [](const Person* p) { return p->canDrive(); }) != _onBoard.end();
}

std::ostream& Boat::toStream(std::ostream& os) const {
   os << getName() << ": < ";
   for (auto it = _onBoard.begin(); it != _onBoard.end(); ++it) {
      (*it)->toStream(os);
      if (it != std::prev(_onBoard.end())) {
         os << " ";
      }
   }
   return os << " >";
}

bool Boat::add(Person* p) {
   if (_onBoard.size() == MAX_CAPACITY) {
      std::cout << "### Il n'y a plus de place dans le bateau" << std::endl;
      return false;
   }

   if (std::find(_onBoard.begin(), _onBoard.end(), p) != _onBoard.end()) {
      std::cout << "### " << p->getName() << "est déjà dans le bateau" << std::endl;
      return false;
   }

   _onBoard.push_back(p);
   return true;
}
