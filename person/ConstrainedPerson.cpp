#include <algorithm>
#include "ConstrainedPerson.h"

ConstrainedPerson::ConstrainedPerson(const std::string& name) : Person(name), _shouldBeWith(nullptr) {}

bool ConstrainedPerson::canDrive() const {
   return false;
}

bool ConstrainedPerson::checkConstraint(const std::list<const Person*>& context) const {
   // Check if the strongly related person is present
   if (std::find(context.begin(), context.end(), _shouldBeWith) != context.end()) {
      return true;
   }

   // If not, check if can stay with all person
   for (const Person* p: context) {
      if (std::find(_cannotBeWith.begin(), _cannotBeWith.end(), p) != _cannotBeWith.end()) {
         return false;
      }
   }
   return true;
}

void ConstrainedPerson::setConstraint(const Person* shouldBeWith, std::initializer_list<const Person*> cannotBeWith) {
   if (shouldBeWith == this) return;

   _shouldBeWith = shouldBeWith;
   for (const Person* p: cannotBeWith) {
      if (p != nullptr && p != this && p != shouldBeWith && std::find(_cannotBeWith.begin(), _cannotBeWith.end(), p) == _cannotBeWith.end()) {
         _cannotBeWith.push_back(p);
      }
   }
}
