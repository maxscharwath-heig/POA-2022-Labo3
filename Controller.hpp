#ifndef POA_LABO3_CONTROLLER_HPP
#define POA_LABO3_CONTROLLER_HPP

#include "container/Bank.hpp"
#include "container/Boat.hpp"

/**
 * The main controller for the river game
 *
 * @author Nicolas Crausaz
 * @author Maxime Scharwath
 * @date 10.05.2022
 */
class Controller {
public:
   Controller();

   ~Controller();

   Controller(const Controller&) = delete;

   Controller& operator=(const Controller&) = delete;

   void start();

private:
   std::list<Person*> persons;
   unsigned turn;
   Bank* leftBank;
   Bank* rightBank;
   Boat* boat;
   BoatSide boatSide;

   void reset();

   static void showMenu();

   void display();

   void nextTurn();

   bool getInput();

   std::list<Person*> getFromFutureState(std::list<Person*>& list, Person* person) const;

   std::list<Person*> getToFutureState(std::list<Person*>& list, Person* person) const;

   bool validatePersonMove(Container* from, Container* to, const std::string& name);

   bool validateBoatMove();
};


#endif //POA_LABO3_CONTROLLER_HPP
