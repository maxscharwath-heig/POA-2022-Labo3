#include "Boat.hpp"

Boat::Boat(const std::string& name, Bank* bank) : Container(name), currentBank(bank) {}

void Boat::setCurrentBank(Bank* bank) {
    currentBank = bank;
}


