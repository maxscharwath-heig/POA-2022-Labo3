#ifndef POA_LABO3_PERSON_HPP
#define POA_LABO3_PERSON_HPP

#include <string>
#include <list>

/**
 * Defines a person
 *
 * @author Nicolas Crausaz
 * @author Maxime Scharwath
 * @date 10.05.2022
 */
class Person {
public:
   virtual ~Person() = default;

   /**
    * Check if a person is able to drive a boat
    * @return
    */
   virtual bool canDrive() const = 0;

   /**
    * Display a person
    * @param os output stream
    * @return modified output stream
    */
   virtual std::ostream& toStream(std::ostream& os) const;

   virtual bool checkConstraint(std::list<Person*> context) const = 0;

   /**
    * Get the person's name
    * @return person's name
    */
   const std::string& getName() const;

protected:
   /**
    * Creates a new person
    * @param name person's name
    */
   explicit Person(const std::string& name);

private:
   const std::string _name;
};


#endif //POA_LABO3_PERSON_HPP
