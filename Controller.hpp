#ifndef POA_LABO3_CONTROLLER_HPP
#define POA_LABO3_CONTROLLER_HPP

#include "Bank.hpp"
#include "Boat.hpp"

class Controller {
public:
   Controller();

   ~Controller();

   Controller(const Controller&) = delete;

   Controller& operator=(const Controller&) = delete;

   void showMenu();

   void display();

   void nextTurn();

   void getInput();

   void start();

private:
   std::list<Person*> persons;
   unsigned turn;
   Bank* leftBank;
   Bank* rightBank;
   Boat* boat;
   BoatSide boatSide;

   void reset();

   std::list<Person*> getFutureState();

   bool validatePersonMove(Container* from, Container* to, const std::string& name);

   bool validateBoatMove();

   bool validatePerson(const std::string& name) const;
};


#endif //POA_LABO3_CONTROLLER_HPP
