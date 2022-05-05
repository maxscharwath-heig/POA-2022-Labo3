//
// Created by Maxime Scharwath on 05.05.2022.
//

#ifndef POA_LABO3_CHILDCONSTRAINT_HPP
#define POA_LABO3_CHILDCONSTRAINT_HPP


#include "Constraint.hpp"
#include "../person/Child.hpp"

class ChildConstraint: public Constraint {
public:
    bool execute(Child *person, std::list<Person *>&context);
};


#endif //POA_LABO3_CHILDCONSTRAINT_HPP
