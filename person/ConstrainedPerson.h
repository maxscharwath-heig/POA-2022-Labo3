#ifndef POA_LABO3_CONSTRAINEDPERSON_H
#define POA_LABO3_CONSTRAINEDPERSON_H

#include <list>
#include "Person.hpp"

/**
 * Defines a person that must always be with another person and therefore cannot stay with certain people without them.
 *
 * @author Nicolas Crausaz
 * @author Maxime Scharwath
 * @date 10.05.2022
 */
class ConstrainedPerson : public Person {

public:
   /**
    * Creates a new constrained person
    * @param name person name
    */
   explicit ConstrainedPerson(const std::string& name);

   bool canDrive() const override;

   bool checkConstraint(std::list<Person*> context) const override;

   /**
    * Set a constraint of the person
    * @param shouldBeWith The person it should stays with
    * @param cannotBeWith The people that cannot be with, without shouldBeWith
    */
   void setConstraint(Person* shouldBeWith, std::initializer_list<Person*> cannotBeWith);

private:
   Person* _shouldBeWith;
   std::list<Person*> _cannotBeWith;
};


#endif //POA_LABO3_CONSTRAINEDPERSON_H
