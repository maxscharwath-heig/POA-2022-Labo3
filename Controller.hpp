#ifndef POA_LABO3_CONTROLLER_HPP
#define POA_LABO3_CONTROLLER_HPP

#include "Bank.hpp"
#include "Boat.hpp"

enum BoatSide {
    LEFT, RIGHT
};

class Controller {
public:
    Controller();

    ~Controller();

    void showMenu();

    void display();

    void nextTurn();

private:
    unsigned turn;
    Bank* leftBank;
    Bank* rightBank;
    Boat* boat;
    BoatSide boatSide;
};


#endif //POA_LABO3_CONTROLLER_HPP
