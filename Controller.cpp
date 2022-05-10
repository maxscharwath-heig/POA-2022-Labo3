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

    persons = {pere, mere, policier, paul, pierre, julie, jeanne, voleur};
    leftBank->add(persons);
}

Controller::~Controller() {
    for (const Person* p: persons) {
        delete p;
    }
    delete leftBank;
    delete boat;
    delete rightBank;
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
              << std::setw(MENU_GAP) << std::left << "h" << ": menu" << std::endl;
}

void Controller::display() {
    std::cout << std::endl << *leftBank;

    if (boat->getCurrentBank() == leftBank) {
        std::cout << *boat;
    }

    std::cout << std::endl << std::setw(LINE_SIZE) << std::setfill(RIVER_CHAR) << ""
              << std::endl;

    if (boat->getCurrentBank() == rightBank) {
        std::cout << *boat;
    }

    std::cout << std::endl << *rightBank << turn << ">\t";
}

void Controller::nextTurn() {
    ++turn;
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

                if (validatePersonMove(boat->getCurrentBank(), boat, name)) {
                    std::cout << "Embarquement de " << name << std::endl;
                }
                nextTurn();
                break;
            }

            case UNLOAD_KEY: {
                std::string name;
                std::cin >> name;

                if (validatePersonMove(boat, boat->getCurrentBank(), name)) {
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
                std::cout << ERROR_PREFIX<< "Commande introuvable" << std::endl;
        }
    } else {
        std::cout << ERROR_PREFIX<< " Format de commande invalide" << std::endl;
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
    boat->setCurrentBank(leftBank);
}

void Controller::start() {
    showMenu();
    bool continueGame;
    do { //main game loop
        if (rightBank->getPeople().size() == persons.size()) {
            std::cout << "Vous avez reussi en " << turn << " coups !" << std::endl;
            break;
        }
        display();
        continueGame = getInput();
    } while (continueGame);
}

bool Controller::validatePersonMove(Container* from, Container* to,
                                    const std::string& name) {

    if (from == nullptr || to == nullptr) {
        return false;
    }

    auto personIt = std::find_if(persons.begin(), persons.end(),
                                 [&name](const Person* p) {
                                     return p->getName() == name;
                                 });

    if (personIt == persons.end()) {
        std::cout << ERROR_PREFIX<< " Personne specifiee invalide" << std::endl;
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
    if (!boat->hasDriver()) {
        std::cout << ERROR_PREFIX<< " Le bateau n'a pas de conducteur" << std::endl;
        return false;
    }

    Bank* bankSide = boat->getCurrentBank() == leftBank ? rightBank : leftBank;
    boat->setCurrentBank(bankSide);
    return true;
}




