#ifndef POA_LABO3_CHILD_HPP
#define POA_LABO3_CHILD_HPP

#include "Person.hpp"
#include "GenderedPerson.hpp"

class Child: public GenderedPerson {
public:
    explicit Child(const std::string&name, Gender gender);

    bool canDrive() const override;
};


#endif //POA_LABO3_CHILD_HPP
