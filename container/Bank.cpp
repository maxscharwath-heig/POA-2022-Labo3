#include <iostream>
#include <iomanip>
#include "Bank.hpp"
#include "../Constants.h"

Bank::Bank(const std::string& name) : Container(name) {}

std::ostream& Bank::toStream(std::ostream& os) const {
   os << std::setw(LINE_SIZE) << std::setfill(BANK_CHAR) << "" << std::endl
      << getName() << ": " ;

   for (auto it = onBoard.begin(); it != onBoard.end(); ++it) {
      (*it)->toStream(os);
      if (it != std::prev(onBoard.end())) {
         os << " ";
      }
   }
   return os << std::endl << std::setw(60) << std::setfill('-') << "" << std::endl;
}
