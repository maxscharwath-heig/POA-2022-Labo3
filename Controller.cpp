#include <iostream>
#include <limits>
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
            nextTurn();
            break;
         case 'e': {
            std::string name;
            std::cin >> name;
            std::cout << "Embarquement de " << name << std::endl;
         }
            break;
         case 'd': {
            std::string name;
            std::cin >> name;
            std::cout << "Debarquement de " << name << std::endl;
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


