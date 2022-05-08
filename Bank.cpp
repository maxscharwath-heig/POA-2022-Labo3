#include <iostream>
#include "Bank.hpp"

Bank::Bank(const std::string& name) : Container(name) {}
// TODO: utiliser les setfill et set width
std::ostream& Bank::toStream(std::ostream& os) const {
    os << "----------------------------------------------------------" << std::endl
       << getName() << ": ";
    for (auto it = onBoard.begin(); it != onBoard.end(); ++it) {
        (*it)->toStream(os);
        if (it != std::prev(onBoard.end())) {
            os << " ";
        }
    }
    return os << std::endl <<  "----------------------------------------------------------";
}
