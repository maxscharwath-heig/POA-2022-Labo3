#include <iostream>
#include <limits>
#include "Controller.hpp"
#include "person/Thief.hpp"
#include "person/Parent.hpp"
#include "person/Child.hpp"
#include "person/Police.hpp"

Controller::Controller() {
    leftBank = new Bank("Gauche");
    rightBank = new Bank("Droite");
    boat = new Boat("Bateau", leftBank);
    turn = 0;
    boatSide = LEFT;

    leftBank->add(new Parent("pere", MALE));
    leftBank->add(new Parent("mere", FEMALE));
    leftBank->add(new Child("paul", MALE));
    leftBank->add(new Child("pierre", MALE));
    leftBank->add(new Child("julie", FEMALE));
    leftBank->add(new Child("jeanne", FEMALE));
    leftBank->add(new Police("policier"));
    leftBank->add(new Thief("voleur"));
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
        std::cout << *boat  << std::endl;
    } else {
        std::cout << std::endl;
    }
    std::cout << "==========================================================";
    if (boatSide == RIGHT) {
        std::cout << *boat << std::endl;
    } else {
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
        std::cout<< std::endl<< turn << ">\t";
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


