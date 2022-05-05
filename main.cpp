#include "Controller.hpp"
#include "constraint/ChildConstraint.hpp"
#include "person/Thief.hpp"

int main() {

    // TODO: hiérarchie de Personnes, de contraintes

    auto* jean = new Child("Jean", MALE);
    auto* marcDutrou = new Thief("Marc Dutrou");
    auto* mysteryMachine = new Boat("MysteryMachine", nullptr);
    mysteryMachine->add(jean);
    mysteryMachine->add(marcDutrou);
    ChildConstraint c1;
    c1.execute(jean, mysteryMachine->getPeople());

    Controller controller;
    controller.showMenu();
    controller.display();
    while(true){
        controller.getInput();
    }


    return EXIT_SUCCESS;
}
