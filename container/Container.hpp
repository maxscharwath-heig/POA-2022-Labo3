#ifndef POA_LABO3_CONTAINER_HPP
#define POA_LABO3_CONTAINER_HPP

#include <string>
#include <list>
#include "../person/Person.hpp"

class Container;

std::ostream& operator<<(std::ostream& os, const Container& container);

class Container {
public:
   virtual ~Container() = default;

   virtual std::ostream& toStream(std::ostream& os) const = 0;

   virtual bool add(Person* person);

   void add(std::initializer_list<Person*> people);

   void add(const std::list<Person*>& people);

   void remove(Person* person);

   void clear();

   const std::list<Person*>& getPeople() const;

   const std::string& getName() const;

protected:
   explicit Container(const std::string& name);

protected:
   const std::string name;
   std::list<Person*> onBoard;
};


#endif //POA_LABO3_CONTAINER_HPP
