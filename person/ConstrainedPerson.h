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

   bool checkConstraint(const std::list<const Person*>& context) const override;

    std::ostream& printErrorMessageToStream(std::ostream& os) const override;

   /**
    * Set a constraint of the person
    *
    * shouldBeWith cannot be the current person
    * cannotBeWith cannot contain twice the same person
    * shouldBeWith cannot be in cannotBeWith
    * Invalid cases are ignored
    *
    * @param shouldBeWith The person it should stays with
    * @param cannotBeWith The people that cannot be with, without shouldBeWith
    * @param errorMsgConstraint The message to show when constraint doesnt match
    */
   void setConstraint(const Person* shouldBeWith,
                      std::initializer_list<const Person*>cannotBeWith,
                      const std::string& errorMsgConstraint);

private:
   const Person* _shouldBeWith;
   std::list<const Person*> _cannotBeWith;
   std::string _errorMsgConstraint;
};


#endif //POA_LABO3_CONSTRAINEDPERSON_H
