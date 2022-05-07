#ifndef POA_LABO3_CONSTRAINEDPERSON_H
#define POA_LABO3_CONSTRAINEDPERSON_H

#include <list>
#include "Person.hpp"

class ConstrainedPerson : public Person {

public:
   explicit ConstrainedPerson(const std::string& name);

   bool canDrive() const override;

   bool checkConstraint(std::list<Person*> context) const override;

   void setConstraint(Person* shouldBeWith, std::initializer_list<Person*> cannotBeWith);

private:
   Person* _shouldBeWith;
   std::list<Person*> _cannotBeWith;
};


#endif //POA_LABO3_CONSTRAINEDPERSON_H
