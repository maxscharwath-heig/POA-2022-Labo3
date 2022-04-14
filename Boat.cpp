#include <iostream>
#include "Boat.hpp"

Boat::Boat(const std::string& name, Bank* bank) : Container(name), currentBank(bank) {}

void Boat::setCurrentBank(Bank* bank) {
    currentBank = bank;
}

std::ostream& Boat::toStream(std::ostream& os) const {
    return Container::toStream(os)
            << "----------------------------------------------------------"
            << getName() << "< >                                             "
            << " ---------------------------------------------------------"
            << std::endl;
}


