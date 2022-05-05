#ifndef POA_LABO3_GENDEREDPERSON_HPP
#define POA_LABO3_GENDEREDPERSON_HPP


#include "Person.hpp"

enum Gender {
    MALE,
    FEMALE
};

class GenderedPerson : public Person {

public:
    Gender getGender();

protected:
    explicit GenderedPerson(const std::string& name, Gender gender);

private:
    Gender gender;
};


#endif //POA_LABO3_GENDEREDPERSON_HPP
