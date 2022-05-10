#include <iostream>
#include <limits>
#include <algorithm>
#include "Controller.hpp"
#include "person/UnconstrainedPerson.h"
#include "person/ConstrainedPerson.h"

const static char DISPLAY_KEY = 'p';
const static char LOAD_KEY = 'e';
const static char UNLOAD_KEY = 'd';
const static char MOVE_KEY = 'm';
const static char RESET_KEY = 'r';
const static char QUIT_KEY = 'q';
const static char HELP_KEY = 'h';

Controller::Controller() {
   leftBank = new Bank("Gauche");
   rightBank = new Bank("Droite");
   boat = new Boat("Bateau", leftBank);
   turn = 0;
   boatSide = LEFT;

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
   for (Person* p : persons) {
      delete p;
   }
   delete leftBank;
   delete boat;
   delete rightBank;
}

void Controller::showMenu() {
   std::cout << "p : afficher" << std::endl
             << "e <nom>: embarquer <nom>" << std::endl
             << "d <nom>: debarquer <nom>" << std::endl
             << "m: deplacer bateau" << std::endl
             << "r: reinitialiser" << std::endl
             << "q: quitter" << std::endl
             << "h: menu" << std::endl;
}

void Controller::display() {
   std::cout << *leftBank << std::endl;
   if (boatSide == LEFT) {
      std::cout << *boat << std::endl;
   }
   else {
      std::cout << std::endl;
   }
   std::cout << "=========================================================="
             << std::endl; // TODO: utiliser les setfill et set width
   if (boatSide == RIGHT) {
      std::cout << *boat;
   }

   std::cout << std::endl << *rightBank;
}

void Controller::nextTurn() {
   ++turn;
}

void Controller::getInput() {
   bool invalid;
   do {
      invalid = false;

      if (checkWin()) {
         std::cout << "Vous avez reussi en " << turn << " coups !" << std::endl;
         exit(EXIT_SUCCESS);
      }

      display();
      std::cout << std::endl << turn << ">\t";
      char command;
      std::cin >> command;
      // TODO: constantes pour les cases
      // TODO: regler le cas ou on ecrit "epolicier" sans espace, et faire une méthode privée pour la recup de la saisie
      switch (command) {
         case DISPLAY_KEY:
            display();
            break;
         case QUIT_KEY:
            exit(EXIT_SUCCESS);
         case RESET_KEY:
            reset();
            break;
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
         }
            break;
         case UNLOAD_KEY: {
            std::string name;
            std::cin >> name;

            Bank* bankSide = boatSide == LEFT ? leftBank : rightBank;

            if (validatePersonMove(boat, bankSide, name)) {
               std::cout << "Debarquement de " << name << std::endl;
            }

            nextTurn();
         }
            break;

         case HELP_KEY: {
            showMenu();
         }
            break;
         default:
            std::cout << "### Commande invalide" << std::endl;
            invalid = true;
            break;
      }
      if (std::cin.fail()) {
         invalid = true;
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   } while (invalid);
}

void Controller::reset() {
   std::cout << "Reinitialisation du jeu" << std::endl;

   leftBank->clear();
   boat->clear();
   rightBank->clear();
   turn = 0;
   leftBank->add(persons);
}

void Controller::start() {
   showMenu();
   while (true) {
      getInput();
   }
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
   // TODO: A voir si ce n'est pas mieux de changer les listes courante et de rollback en cas
   // d'erreur

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

   if (boatSide == LEFT) {
      boat->setCurrentBank(rightBank);
   }
   else {
      boat->setCurrentBank(leftBank);
   }
   return true;
}

bool Controller::checkWin() const {
   return rightBank->getPeople().size() == persons.size();
}




