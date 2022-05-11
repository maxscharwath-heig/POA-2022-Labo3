#include <iostream>
#include <iomanip>
#include "Bank.hpp"
#include "../Constants.hpp"

Bank::Bank(const std::string& name) : Container(name) {}

std::ostream& Bank::toStream(std::ostream& os) const {
   os << std::setw(LINE_SIZE) << std::setfill(BANK_CHAR) << "" << std::endl
      << getName() << ": ";

   for (auto it = _onBoard.begin(); it != _onBoard.end(); ++it) {
      (*it)->toStream(os);
      if (it != std::prev(_onBoard.end())) {
         os << " ";
      }
   }
   return os << std::endl << std::setw(LINE_SIZE) << std::setfill(BANK_CHAR) << ""
             << std::endl;
}
