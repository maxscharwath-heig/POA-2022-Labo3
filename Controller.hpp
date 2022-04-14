#ifndef POA_LABO3_CONTROLLER_HPP
#define POA_LABO3_CONTROLLER_HPP


#include "Bank.hpp"
#include "Boat.hpp"

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

};


#endif //POA_LABO3_CONTROLLER_HPP
