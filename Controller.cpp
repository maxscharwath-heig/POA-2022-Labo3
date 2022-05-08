#include <iostream>
#include <limits>
#include <algorithm>
#include "Controller.hpp"
#include "person/UnconstrainedPerson.h"
#include "person/ConstrainedPerson.h"

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
   leftBank->add({pere, mere, policier, paul, pierre, julie, jeanne, voleur});
}

Controller::~Controller() {
   delete leftBank;
   delete rightBank;
   delete boat;
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
   std::cout << "==========================================================";
   if (boatSide == RIGHT) {
      std::cout << *boat << std::endl;
   }
   else {
      std::cout << std::endl;
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
      std::cout << std::endl << turn << ">\t";
      char command;
      std::cin >> command;
      // TODO: constantes pour les cases
      switch (command) {
         case 'p':
            display();
            break;
         case 'q':
            exit(0);
            break;
         case 'r':
            reset();
            break;
         case 'm':
            std::cout << "Deplacement du bateau" << std::endl;
            validateBoatMove();
            nextTurn();
            boatSide = boatSide == LEFT ? RIGHT : LEFT;
            break;
         case 'e': {
            std::string name;
            std::cin >> name;
            std::cout << "Embarquement de " << name << std::endl;

            if (boatSide == LEFT) {
               validatePersonMove(leftBank, boat, name);
            }
            else {
               validatePersonMove(rightBank, boat, name);
            }
            nextTurn();
         }
            break;
         case 'd': {
            std::string name;
            std::cin >> name;
            std::cout << "Debarquement de " << name << std::endl;

            if (boatSide == LEFT) {
               validatePersonMove(boat, leftBank, name);
            }
            else {
               validatePersonMove(boat, rightBank, name);
            }
            nextTurn();
         }
            break;
         default:
            std::cout << "Commande invalide" << std::endl;
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
}

void Controller::start() {
   showMenu();
   display();
   while (true) {
      getInput();
   }
}

std::list<Person*> Controller::getFutureState() {
   // We generate the list of person in the boat + on the other side of the river
   std::list<Person*> context;
   if (boatSide == LEFT) {
      context.splice(context.end(), rightBank->getPeople());
   }
   else {
      context.splice(context.end(), leftBank->getPeople());
   }
   context.splice(context.end(), boat->getPeople());
   return context;
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
      std::cout << "### " << person->getName() << " is not on " << from->getName() << std::endl;
      return false;
   }

   // Apply the move
   if (to->add(person)) {
      from->remove(person);
   }
   // ...

   return true;
}

bool Controller::validateBoatMove() {

   if (!boat->hasDriver()) {
      std::cout << "### Le bateau n'a pas de conducteur" << std::endl;
      return false;
   }

   const std::list<Person*> futureState = getFutureState();

   for (const Person* p: futureState) {
      if (!p->checkConstraint(futureState)) {
         std::cout << "### Constraint not respected" << std::endl; // TODO: display the exact error
         return false;
      }
   }

   if (boatSide == LEFT) {
      boat->setCurrentBank(rightBank);
   } else {
      boat->setCurrentBank(leftBank);
   }
   return true;
}


