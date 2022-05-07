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

    Controller(const Controller&) = delete;

    Controller& operator=(const Controller&) = delete;

    void showMenu();

    void display();

    void nextTurn();

    void getInput();

    void start();

private:
    unsigned turn;
    Bank* leftBank;
    Bank* rightBank;
    Boat* boat;
    BoatSide boatSide;

    void reset();
};


#endif //POA_LABO3_CONTROLLER_HPP
