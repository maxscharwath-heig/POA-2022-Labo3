#ifndef POA_LABO3_POLICE_HPP
#define POA_LABO3_POLICE_HPP

#include "Person.hpp"

class Police: public Person {
public:
    explicit Police(const std::string& name);

    bool canDrive() const override;
};


#endif //POA_LABO3_POLICE_HPP
