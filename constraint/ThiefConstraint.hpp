//
// Created by Maxime Scharwath on 05.05.2022.
//

#ifndef POA_LABO3_THIEFCONSTRAINT_HPP
#define POA_LABO3_THIEFCONSTRAINT_HPP


#include "Constraint.hpp"
#include "../person/Thief.hpp"

class ThiefConstraint: public Constraint {
    bool execute(Thief *person, std::list<Person *> &context);
};


#endif //POA_LABO3_THIEFCONSTRAINT_HPP
