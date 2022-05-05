#ifndef POA_LABO3_PARENT_HPP
#define POA_LABO3_PARENT_HPP

#include "GenderedPerson.hpp"

class Parent: public GenderedPerson {
public:
    Parent(const std::string& name, Gender gender);

    bool canDrive() const override;
};


#endif //POA_LABO3_PARENT_HPP
