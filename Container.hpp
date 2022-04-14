#ifndef POA_LABO3_CONTAINER_HPP
#define POA_LABO3_CONTAINER_HPP

#include <string>
#include <list>
#include "Person.hpp"

/**
 *
 */
class Container {
public:

protected:
    explicit Container(const std::string& name);

    virtual ~Container() = default;

    void add(Person* person);

private:
    const std::string name;
    std::list<Person*> onBoard;
};


#endif //POA_LABO3_CONTAINER_HPP
