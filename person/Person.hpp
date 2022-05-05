#ifndef POA_LABO3_PERSON_HPP
#define POA_LABO3_PERSON_HPP


#include <string>

class Person {

public:
    virtual ~Person() = default;
    virtual bool canDrive() const = 0;

    std::ostream& toStream(std::ostream& os) const;

protected:
    explicit Person(const std::string& name);

private:
    const std::string name;
};


#endif //POA_LABO3_PERSON_HPP