#include <iostream>
#include "Controller.hpp"
#include "person/ConstrainedPerson.h"
#include "person/UnconstrainedPerson.h"

/**
 * Main entry for the river game
 * & Tests
 *
 * @author Nicolas Crausaz
 * @author Maxime Scharwath
 * @date 10.05.2022
 */

#define RUN_TESTS true // Change here to run tests

void tests() {
   // Test 1
   ConstrainedPerson cp("voleur");
   const UnconstrainedPerson ucp("policier");
   const UnconstrainedPerson mom("mere");
   const UnconstrainedPerson* dad = new UnconstrainedPerson("pere");

   std::cout << cp.getName() << " " << ucp.getName() << " " << dad->getName() << std::endl << std::endl;

   // Test 2
   std::list<const Person*> shouldFailCheck = {&mom, dad};
   std::list<const Person*> shouldPassCheck = {&mom, dad, &ucp};
   cp.setConstraint(&ucp, {&mom, dad});
   std::cout << "Should be 0: " << cp.checkConstraint(shouldFailCheck) << std::endl;
   std::cout << "Should be 1: " << cp.checkConstraint(shouldPassCheck) << std::endl;


   delete dad;
}

int main() {

   if (RUN_TESTS)
      tests();


   return EXIT_SUCCESS;
   Controller controller;
   controller.start();

   return EXIT_SUCCESS;
}
