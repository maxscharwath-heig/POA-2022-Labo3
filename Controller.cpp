#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>
#include "Controller.hpp"
#include "person/UnconstrainedPerson.h"
#include "person/ConstrainedPerson.h"
#include "Constants.h"

Controller::Controller() {
   leftBank = new Bank("Gauche");
   rightBank = new Bank("Droite");
   boat = new Boat("Bateau", leftBank);
   turn = 0;
   boatSide = LEFT; // TODO: use boat->getSideInstead ? le stocker ailleurs ?

   UnconstrainedPerson* pere = new UnconstrainedPerson("pere");
   UnconstrainedPerson* mere = new UnconstrainedPerson("mere");
   UnconstrainedPerson* policier = new UnconstrainedPerson("policier");
   ConstrainedPerson* paul = new ConstrainedPerson("paul");
   ConstrainedPerson* pierre = new ConstrainedPerson("pierre");
   ConstrainedPerson* julie = new ConstrainedPerson("julie");
   ConstrainedPerson* jeanne = new ConstrainedPerson("jeanne");
   ConstrainedPerson* voleur = new ConstrainedPerson("voleur");

   paul->setConstraint(pere, {mere});
   pierre->setConstraint(pere, {mere});
   julie->setConstraint(mere, {pere});
   jeanne->setConstraint(mere, {pere});
   voleur->setConstraint(policier, {pere, mere, paul, pierre, julie, jeanne});

   persons = {pere, mere, policier, paul, pierre, julie, jeanne, voleur};
   leftBank->add(persons);
}

Controller::~Controller() {
   for (Person* p: persons) {
      delete p;
   }
   delete leftBank;
   delete boat;
   delete rightBank;
}

void Controller::showMenu() {
   // TODO: setw
   std::cout << "p : afficher" << std::endl
             << "e <nom>: embarquer <nom>" << std::endl
             << "d <nom>: debarquer <nom>" << std::endl
             << "m: deplacer bateau" << std::endl
             << "r: reinitialiser" << std::endl
             << "q: quitter" << std::endl
             << "h: menu" << std::endl;
}

void Controller::display() {
   std::cout << std::endl << *leftBank;
   if (boatSide == LEFT) {
      std::cout << *boat;
   }

   std::cout << std::endl << std::setw(LINE_SIZE) << std::setfill(RIVER_CHAR) << "" << std::endl;

   if (boatSide == RIGHT) {
      std::cout << *boat;
   }

   std::cout << std::endl << *rightBank << turn << ">\t";
}

void Controller::nextTurn() {
   ++turn;
}

bool Controller::getInput() {
   // Check if the game is done
   if (rightBank->getPeople().size() == persons.size()) {
      std::cout << "Vous avez reussi en " << turn << " coups !" << std::endl;
      return false;
   }

   bool continueGame = true;
   display();
   char command;
   std::cin >> command;

   // TODO: regler le cas ou on ecrit "epolicier" sans espace, et faire une méthode privée pour la recup de la saisie si besoin
   switch (command) {
      case MOVE_KEY:
         if (validateBoatMove()) {
            boatSide = boatSide == LEFT ? RIGHT : LEFT;
            std::cout << "Deplacement du bateau" << std::endl;
         }
         nextTurn();
         break;

      case LOAD_KEY: {
         std::string name;
         std::cin >> name;

         Bank* bankSide = boatSide == LEFT ? leftBank : rightBank;

         if (validatePersonMove(bankSide, boat, name)) {
            std::cout << "Embarquement de " << name << std::endl;
         }
         nextTurn();
         break;
      }

      case UNLOAD_KEY: {
         std::string name;
         std::cin >> name;

         Bank* bankSide = boatSide == LEFT ? leftBank : rightBank;

         if (validatePersonMove(boat, bankSide, name)) {
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
         std::cout << "### Commande invalide" << std::endl;
   }

   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   return continueGame;
}

void Controller::reset() {
   std::cout << "Reinitialisation du jeu" << std::endl;
   leftBank->clear();
   boat->clear();
   rightBank->clear();
   turn = 0;
   leftBank->add(persons);
   boatSide = LEFT;
}

void Controller::start() {
   showMenu();
   while (getInput()) {}
}

std::list<Person*> Controller::getFromFutureState(std::list<Person*>& list, Person* person) const {
   std::list<Person*> state;
   state.splice(state.end(), list);
   state.remove(person);
   return state;
}

std::list<Person*> Controller::getToFutureState(std::list<Person*>& list, Person* person) const {
   std::list<Person*> state;
   state.splice(state.end(), list);
   state.push_back(person);
   return state;
}

bool Controller::validatePersonMove(Container* from, Container* to, const std::string& name) {

   if (from == nullptr || to == nullptr) {
      return false;
   }

   auto personIt = std::find_if(persons.begin(), persons.end(),
                                [&name](const Person* p) { return p->getName() == name; });

   if (personIt == persons.end()) {
      std::cout << "### Personne specifiee invalide" << std::endl;
      return false;
   }

   Person* person = *personIt;

   const std::list<Person*> peopleInFrom = from->getPeople();

   // Check if person is in "from"
   if (std::find(peopleInFrom.begin(), peopleInFrom.end(), person) == peopleInFrom.end()) {
      std::cout << "### " << person->getName() << " n'est pas sur " << from->getName() << std::endl;
      return false;
   }

   // NOTE: ici On travaille avec des copies pour pas changer les listes courantes
   // TODO: A voir si ce n'est pas mieux de changer les listes courante et de rollback en cas d'erreur

   // Check constraints on future state
   std::list<Person*> tmpFrom(from->getPeople());
   std::list<Person*> tmpTo(from->getPeople());

   const std::list<Person*> futureFromState = getFromFutureState(tmpFrom, person);
   const std::list<Person*> futureToState = getToFutureState(tmpTo, person);

   // Check from
   for (Person* p: futureFromState) {
      if (!p->checkConstraint(futureFromState)) {
         std::cout << "### Constraint not respected on " << p->getName() << std::endl; // TODO: display the exact error
         return false;
      }
   }

   // Check to
   for (Person* p: futureToState) {
      if (!p->checkConstraint(futureToState)) {
         std::cout << "### Constraint not respected on " << p->getName()
                   << std::endl; // TODO: display the exact error (overload in person ?)
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
   if (!boat->hasDriver()) {
      std::cout << "### Le bateau n'a pas de conducteur" << std::endl;
      return false;
   }

   Bank* bankSide = boatSide == LEFT ? rightBank : leftBank;
   boat->setCurrentBank(bankSide);
   return true;
}




