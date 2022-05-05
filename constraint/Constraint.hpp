//
// Created by Maxime Scharwath on 05.05.2022.
//

#ifndef POA_LABO3_CONSTRAINT_HPP
#define POA_LABO3_CONSTRAINT_HPP


#include <list>
#include "../person/Person.hpp"

class Constraint {
public:
    virtual ~Constraint() = default;
    bool execute(Person* person, std::list<Person*>& context);
};


#endif //POA_LABO3_CONSTRAINT_HPP
