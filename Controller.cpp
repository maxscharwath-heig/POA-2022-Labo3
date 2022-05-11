#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>
#include "Controller.hpp"
#include "person/UnconstrainedPerson.h"
#include "person/ConstrainedPerson.h"
#include "Constants.h"

Controller::Controller() {
   _leftBank = new Bank("Gauche");
   _rightBank = new Bank("Droite");
   _boat = new Boat("Bateau", _leftBank);
   _turn = 0;

   UnconstrainedPerson* pere = new UnconstrainedPerson("pere");
   UnconstrainedPerson* mere = new UnconstrainedPerson("mere");
   UnconstrainedPerson* policier = new UnconstrainedPerson("policier");
   ConstrainedPerson* paul = new ConstrainedPerson("paul");
   ConstrainedPerson* pierre = new ConstrainedPerson("pierre");
   ConstrainedPerson* julie = new ConstrainedPerson("julie");
   ConstrainedPerson* jeanne = new ConstrainedPerson("jeanne");
   ConstrainedPerson* voleur = new ConstrainedPerson("voleur");

   paul->setConstraint(pere, {mere}, "Paul avec son pere sans sa mere");
   pierre->setConstraint(pere, {mere}, "Pierre avec son pere sans sa mere");
   julie->setConstraint(mere, {pere}, "Julie avec sa mere sans son pere");
   jeanne->setConstraint(mere, {pere}, "Jeanne avec sa mere sans son pere");
   voleur->setConstraint(policier, {pere, mere, paul, pierre, julie, jeanne},
                         "Voleur doit etre avec un policier");

   _persons = {pere, mere, policier, paul, pierre, julie, jeanne, voleur};
   _leftBank->add(_persons);
}

Controller::~Controller() {
   for (const Person* p: _persons) {
      delete p;
   }
   delete _leftBank;
   delete _boat;
   delete _rightBank;
}

void Controller::showMenu() {
   std::cout << std::setw(MENU_GAP) << std::left << "p" << ": afficher" << std::endl
             << std::setw(MENU_GAP) << std::left << "e <nom>" << ": embarquer <nom>"
             << std::endl
             << std::setw(MENU_GAP) << std::left << "d <nom>" << ": debarquer <nom>"
             << std::endl
             << std::setw(MENU_GAP) << std::left << "m" << ": deplacer bateau"
             << std::endl
             << std::setw(MENU_GAP) << std::left << "r" << ": reinitialiser"
             << std::endl
             << std::setw(MENU_GAP) << std::left << "q" << ": quitter" << std::endl
             << std::setw(MENU_GAP) << std::left << "h" << ": menu" << std::endl
             << std::setw(0) << std::setfill(' ') << std::right;
}

void Controller::display() {
   std::cout << std::endl << *_leftBank;

   if (_boat->getCurrentBank() == _leftBank) {
      std::cout << *_boat;
   }

   std::cout << std::endl << std::setw(LINE_SIZE) << std::setfill(RIVER_CHAR) << ""
             << std::endl;

   if (_boat->getCurrentBank() == _rightBank) {
      std::cout << *_boat;
   }

   std::cout << std::endl << *_rightBank << _turn << ">\t";

   std::cout << std::setw(0) << std::setfill(' ') << std::right;
}

void Controller::nextTurn() {
   ++_turn;
}

bool Controller::getInput() {
   bool continueGame = true;
   //using string instead of char to avoid this case: dpolice.
   std::string commandString;
   std::cin >> commandString;
   if (commandString.size() == 1) {
      switch (commandString[0]) {
         case MOVE_KEY:
            if (validateBoatMove()) {
               std::cout << "Deplacement du bateau" << std::endl;
            }
            nextTurn();
            break;

         case LOAD_KEY: {
            std::string name;
            std::cin >> name;

            if (validatePersonMove(_boat->getCurrentBank(), _boat, name)) {
               std::cout << "Embarquement de " << name << std::endl;
            }
            nextTurn();
            break;
         }

         case UNLOAD_KEY: {
            std::string name;
            std::cin >> name;

            if (validatePersonMove(_boat, _boat->getCurrentBank(), name)) {
               std::cout << "Debarquement de " << name << std::endl;
            }
            nextTurn();
            break;
         }

         case DISPLAY_KEY:
            display();
            break;

         case QUIT_KEY:
            continueGame = false;
            break;

         case RESET_KEY:
            reset();
            break;

         case HELP_KEY:
            showMenu();
            break;

         default:
            std::cout << ERROR_PREFIX << "Commande introuvable" << std::endl;
      }
   }
   else {
      std::cout << ERROR_PREFIX << " Format de commande invalide" << std::endl;
   }
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   return continueGame;
}

void Controller::reset() {
   std::cout << "Reinitialisation du jeu" << std::endl;
   _leftBank->clear();
   _boat->clear();
   _rightBank->clear();
   _turn = 0;
   _leftBank->add(_persons);
   _boat->setCurrentBank(_leftBank);
}

void Controller::start() {
   showMenu();
   do { //main game loop
      if (_rightBank->getPeople().size() == _persons.size()) {
         std::cout << "Vous avez reussi en " << _turn << " coups !" << std::endl;
         break;
      }
      display();
   } while (getInput());
}

bool Controller::validatePersonMove(Container* from, Container* to,
                                    const std::string& name) {

   if (from == nullptr || to == nullptr) {
      return false;
   }

   auto personIt = std::find_if(_persons.begin(), _persons.end(),
                                [&name](const Person* p) {
                                   return p->getName() == name;
                                });

   if (personIt == _persons.end()) {
      std::cout << ERROR_PREFIX << " Personne specifiee invalide" << std::endl;
      return false;
   }

   const Person* person = *personIt;

   const std::list<const Person*> peopleInFrom = from->getPeople();

   // Check if person is in "from"
   if (std::find(peopleInFrom.begin(), peopleInFrom.end(), person) ==
       peopleInFrom.end()) {
      std::cout << ERROR_PREFIX << person->getName() << " n'est pas sur "
                << from->getName() << std::endl;
      return false;
   }

   // Check constraints on future state (create copies to avoid changing the source list)
   std::list<const Person*> futureFromState(from->getPeople());
   futureFromState.remove(person);
   std::list<const Person*> futureToState(to->getPeople());
   futureToState.push_back(person);

   // Check from
   for (const Person* p: futureFromState) {
      if (!p->checkConstraint(futureFromState)) {
         p->printErrorMessageToStream(std::cout) << std::endl;
         return false;
      }
   }

   // Check to
   for (const Person* p: futureToState) {
      if (!p->checkConstraint(futureToState)) {
         p->printErrorMessageToStream(std::cout) << std::endl;
         return false;
      }
   }

   // Apply the move
   if (!to->add(person)) {
      return false;
   }

   from->remove(person);
   return true;
}

bool Controller::validateBoatMove() {
   if (!_boat->hasDriver()) {
      std::cout << ERROR_PREFIX << " Le bateau n'a pas de conducteur" << std::endl;
      return false;
   }

   Bank* bankSide = _boat->getCurrentBank() == _leftBank ? _rightBank : _leftBank;
   _boat->setCurrentBank(bankSide);
   return true;
}




