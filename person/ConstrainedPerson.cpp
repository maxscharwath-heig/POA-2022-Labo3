#include <algorithm>
#include "ConstrainedPerson.h"
#include "../Constants.h"

ConstrainedPerson::ConstrainedPerson(const std::string& name) : Person(name), _shouldBeWith(nullptr) {}

bool ConstrainedPerson::canDrive() const {
   return false;
}

bool ConstrainedPerson::checkConstraint(std::list<Person*> context) const {
   // Check if the strongly related person is present
   if (std::find(context.begin(), context.end(), _shouldBeWith) != context.end()) {
      return true;
   }

   // If not, check if can stay with all person
   for (Person* p: context) {
      if (std::find(_cannotBeWith.begin(), _cannotBeWith.end(), p) != _cannotBeWith.end()) {
         return false;
      }
   }
   return true;
}

void ConstrainedPerson::setConstraint(Person* shouldBeWith,
                                      std::initializer_list<Person*> cannotBeWith,
                                      const std::string& errorMsgConstraint) {
    _errorMsgConstraint = errorMsgConstraint;
   _shouldBeWith = shouldBeWith;
   for (Person* p: cannotBeWith) {
      if (p != nullptr && p != this && p != shouldBeWith) {
         _cannotBeWith.push_back(p);
      }
   }
}

std::ostream& ConstrainedPerson::printErrorMessageToStream(std::ostream& os) const {
    return os << ERROR_PREFIX << _errorMsgConstraint;
}