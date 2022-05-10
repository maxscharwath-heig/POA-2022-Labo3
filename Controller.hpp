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
   /**
    * Creates a new controller
    */
   Controller();

   /**
    * Destroy the controller
    */
   ~Controller();

   /**
    * Copy constructor is deleted
    */
   Controller(const Controller&) = delete;

   /**
    * Assign operator is deleted
    * @return
    */
   Controller& operator=(const Controller&) = delete;

   /**
    * Start the game
    */
   void start();

private:
   std::list<Person*> persons;
   unsigned turn;
   Bank* leftBank;
   Bank* rightBank;
   Boat* boat;
   BoatSide boatSide;

   /**
    * Reset the game to its initial state
    */
   void reset();

   /**
    * Display the command list
    */
   static void showMenu();

   /**
    * Display the game state
    */
   void display();


   /**
    * Start the next round
    */
   void nextTurn();

   /**
    * Get the user input and handles it
    * @return true if game should continue, else false (quit or game over)
    */
   bool getInput();

   // TODO: refactor
   std::list<Person*> getFromFutureState(std::list<Person*>& list, Person* person) const;
   // TODO: refactor
   std::list<Person*> getToFutureState(std::list<Person*>& list, Person* person) const;

   /**
    * Checks if the move person move is valid
    * @param from Source container
    * @param to Destination container
    * @param name name of person
    * @return true if move is valid, else false
    */
   bool validatePersonMove(Container* from, Container* to, const std::string& name);

   /**
    * Check if the boat can be moved (has a driver)
    * @return true is the boat can move, else false
    */
   bool validateBoatMove();
};

#endif //POA_LABO3_CONTROLLER_HPP
