#ifndef POA_LABO3_THIEF_HPP
#define POA_LABO3_THIEF_HPP


#include "Person.hpp"

class Thief: public Person {

public:
    explicit Thief(const std::string& name);

    bool canDrive() const override;
};


#endif //POA_LABO3_THIEF_HPP
