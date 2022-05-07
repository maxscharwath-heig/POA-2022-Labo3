#include "UnconstrainedPerson.h"

UnconstrainedPerson::UnconstrainedPerson(const std::string& name) : Person(name) {}

bool UnconstrainedPerson::canDrive() const {
   return true;
}

bool UnconstrainedPerson::checkConstraint(std::list<Person*> context) const {
   return true;
}
