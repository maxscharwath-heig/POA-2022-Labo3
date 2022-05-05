#include <iostream>
#include "Boat.hpp"

const unsigned Boat::MAX_CAPACITY = 2;

Boat::Boat(const std::string& name, Bank* bank) : Container(name), currentBank(bank) {}

void Boat::setCurrentBank(Bank* bank) {
    currentBank = bank;
}

std::ostream& Boat::toStream(std::ostream& os) const {
    return os << getName() << "< todo >";
}

bool Boat::isFull() {
    return onBoard.size() == MAX_CAPACITY;
}


