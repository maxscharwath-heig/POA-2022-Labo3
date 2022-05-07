#ifndef POA_LABO3_UNCONSTRAINEDPERSON_H
#define POA_LABO3_UNCONSTRAINEDPERSON_H

#include "Person.hpp"

class UnconstrainedPerson : public Person {
public:
   explicit UnconstrainedPerson(const std::string& name);

   bool canDrive() const override;

   bool checkConstraint(std::list<Person*> context) const override;
};


#endif //POA_LABO3_UNCONSTRAINEDPERSON_H
