#include <iostream>
#include "Bank.hpp"

Bank::Bank(const std::string& name): Container(name) { }

std::ostream& Bank::toStream(std::ostream& os) const {
    return os << "----------------------------------------------------------" << std::endl
              << getName() << "                                             " << std::endl
              << " ---------------------------------------------------------";
}
