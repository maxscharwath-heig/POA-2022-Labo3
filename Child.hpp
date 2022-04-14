#ifndef POA_LABO3_CHILD_HPP
#define POA_LABO3_CHILD_HPP

#include "Person.hpp"

class Child: public Person {
public:
    explicit Child(const std::string&name);

    bool canDrive() override;
};


#endif //POA_LABO3_CHILD_HPP
