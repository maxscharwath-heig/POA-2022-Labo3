#ifndef POA_LABO3_UNCONSTRAINEDPERSON_H
#define POA_LABO3_UNCONSTRAINEDPERSON_H

#include "Person.hpp"

/**
 * Defines a person that is not constrained
 *
 * @author Nicolas Crausaz
 * @author Maxime Scharwath
 * @date 10.05.2022
 */
class UnconstrainedPerson : public Person {
public:
    /**
     * Creates a new unconstrained person
     * @param name person's name
     */
    explicit UnconstrainedPerson(const std::string& name);

    bool canDrive() const override;

    bool checkConstraint(const std::list<const Person*>& context) const override;

    std::ostream& printErrorMessageToStream(std::ostream& os) const override;
};


#endif //POA_LABO3_UNCONSTRAINEDPERSON_H
