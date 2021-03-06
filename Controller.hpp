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
    */
   Controller& operator=(const Controller&) = delete;

   /**
    * Start the game
    */
   void start();

private:
   std::list<const Person*> _persons;
   unsigned _turn;
   Bank* _leftBank;
   Bank* _rightBank;
   Boat* _boat;

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
    * @return true if game should continue, else false
    */
   bool getInput();

   /**
    * Checks if the move person move is valid, if so moves it
    * @param from Source container
    * @param to Destination container
    * @param name name of person
    * @return true if move is valid, else false
    */
   bool validatePersonMove(Container* from, Container* to, const std::string& name);

   /**
    * Check if the boat can be moved (has a driver), if so moves it
    * @return true is the boat can move, else false
    */
   bool validateBoatMove();
};

#endif //POA_LABO3_CONTROLLER_HPP
