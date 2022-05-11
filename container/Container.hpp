#ifndef POA_LABO3_CONTAINER_HPP
#define POA_LABO3_CONTAINER_HPP

#include <string>
#include <list>
#include "../person/Person.hpp"

class Container;

/**
 * Display a container and its content
 * @param os output stream
 * @param container container to display
 * @return modified output stream
 */
std::ostream& operator<<(std::ostream& os, const Container& container);

/**
 * Define a container that allows people in it
 *
 * @author Nicolas Crausaz
 * @author Maxime Scharwath
 * @date 10.05.2022
 */
class Container {
public:
   virtual ~Container() = default;

   /**
    * Copy constructor is deleted
    */
   Container(const Container&) = delete;

   /**
    * Assign operator is deleted
    */
   Container& operator=(const Container&) = delete;

   /**
    * Display the container and its content
    * @param os output stream
    * @return modified output stream
    */
   virtual std::ostream& toStream(std::ostream& os) const = 0;

   /**
    * Add a person to the container
    * @param person person to add
    * @return true if the person has been added, else false
    */
   virtual bool add(const Person* person);

   /**
    * Add an initializer list of person to the container
    * @param person initializer list of person to add
    */
   virtual void add(std::initializer_list<const Person*> people);

   /**
    * Add a list of person to the container
    * @param person list of person to add
    */
   virtual void add(const std::list<const Person*>& people);

   /**
    * Remove a person from the container
    *
    * No effect if the person is not in the container
    * @param person person to remove
    */
   virtual void remove(const Person* person);

   /**
    * Empty the container
    */
   virtual void clear();

   /**
    * Get the people in container
    * @return list of people in container
    */
   const std::list<const Person*>& getPeople() const;

   /**
    * Get the container's name
    * @return container's name
    */
   const std::string& getName() const;

protected:
   /**
    * Created a new container
    * @param name container's name
    */
   explicit Container(const std::string& name);

   const std::string _name;

   std::list<const Person*> _onBoard;

private:
   bool isAlreadyOnBoard(const Person* p) const;
};


#endif //POA_LABO3_CONTAINER_HPP
