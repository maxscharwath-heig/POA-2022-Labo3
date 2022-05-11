#include "UnconstrainedPerson.h"

UnconstrainedPerson::UnconstrainedPerson(const std::string& name) : Person(name) {}

bool UnconstrainedPerson::canDrive() const {
   return true;
}

bool UnconstrainedPerson::checkConstraint(const std::list<const Person*>& context) const {
   return true;
}

std::ostream&
UnconstrainedPerson::printErrorMessageToStream(std::ostream& os) const {
   return os;
}
