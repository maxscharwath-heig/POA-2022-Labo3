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

#define RUN_TESTS false // Change here to run tests

void tests() {
   std::cout << "TESTS" << std::endl;
   // Test 1
   ConstrainedPerson cp("voleur");
   const UnconstrainedPerson ucp("policier");
   const UnconstrainedPerson mom("mere");
   const UnconstrainedPerson* dad = new UnconstrainedPerson("pere");

   std::cout << cp.getName() << " " << ucp.getName() << " " << dad->getName()
             << std::endl;

   // Test 2
   std::list<const Person*> shouldFailCheck = {&mom, dad};
   std::list<const Person*> shouldPassCheck = {&mom, dad, &ucp};
   cp.setConstraint(&ucp, {&mom, dad}, "should be with policier but not with mere or pere");
   std::cout << "Should be 0: " << cp.checkConstraint(shouldFailCheck) << std::endl;
   std::cout << "Should be 1: " << cp.checkConstraint(shouldPassCheck) << std::endl;

   // Test 3
   std::cout << "Should be 0: " << cp.canDrive() << std::endl;
   std::cout << "Should be 1: " << dad->canDrive() << std::endl;

   // Test 4
   Bank bank("bankname");
   if (bank.add(&cp)) {
      std::cout << "Should be 1: " << (bank.getPeople().back() == &cp)
                << std::endl;
   }
   else {
      std::cout << "Failed test 4" << std::endl;
   }

   // Test 5
   Bank bank2("bankname");
   bank2.add(shouldPassCheck);
   std::cout << "Should be 1: "
             << (bank2.getPeople().size() == shouldPassCheck.size()) << std::endl;

   // Test 6
   Bank bank3("bankname");
   bank3.add({&mom, dad, &ucp});
   std::cout << "Should be 1: " << (bank3.getPeople().size() == 3) << std::endl;

   // Test 7
   bank3.add(&mom);
   bank3.add({dad, &ucp});
   std::cout << "Should be 1: " << (bank3.getPeople().size() == 3) << std::endl;

   // Test 8
   Boat boat("bateau", &bank3);
   boat.add(&mom);
   std::cout << "Should be 1: " << (boat.getPeople().back() == &mom) << std::endl;

   // Test 9
   boat.add(dad);
   std::cout << "Should be 1: " << (boat.getPeople().size() == 2) << std::endl;

   // Test 10
   boat.add(&cp);

   // Test 11 (tested with the debugger as we don't have a getter)
   cp.setConstraint(&ucp, {&mom, &ucp}, "should be with policier but not with mere or policier");
   // -> ucp must no be in "cannotBeWith"

   // Test 12 (tested with the debugger as we don't have a getter)
   ConstrainedPerson cp2("voleur2");
   cp2.setConstraint(&cp2, {&mom}, "should be with voleur but not with mere");

   // Test 13 (tested with the debugger as we don't have a getter)
   cp2.setConstraint(&mom, {&cp2}, "should be with mere but not with voleur");

   // Test 14 (tested with the debugger as we don't have a getter)
   cp2.setConstraint(&mom, {dad, dad, &cp}, "should be with mere but not with pere or voleur");

   delete dad;
}

int main() {

   if (RUN_TESTS)
      tests();

   Controller controller;
   controller.start();

   return EXIT_SUCCESS;
}
