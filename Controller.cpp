#include <iostream>
#include "Controller.hpp"

Controller::Controller() {
    leftBank = new Bank("Gauche");
    rightBank = new Bank("Droite");
    boat = new Boat("Bateau", leftBank);
    turn = 0;
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

}

void Controller::nextTurn() {
    ++turn;
}


