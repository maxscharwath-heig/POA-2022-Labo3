#ifndef POA_LABO3_CONTAINER_HPP
#define POA_LABO3_CONTAINER_HPP

#include <string>
#include <list>
#include "person/Person.hpp"

class Container;

std::ostream& operator<<(std::ostream& os, const Container& container);

class Container {
public:
    virtual ~Container();

    virtual std::ostream& toStream(std::ostream& os) const = 0;

    void add(Person* person);

    std::list<Person*>& getPeople();

    const std::string& getName() const;

protected:
    explicit Container(const std::string& name);

protected:
    const std::string name;
    std::list<Person*> onBoard;
};


#endif //POA_LABO3_CONTAINER_HPP
