#include "Controller.hpp"

int main() {

    // TODO: hiérarchie de Personnes, de contraintes

    Controller controller;
    controller.showMenu();
    controller.display();
    while(true){
        controller.getInput();
    }


    return EXIT_SUCCESS;
}
