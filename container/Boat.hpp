#ifndef POA_LABO3_BOAT_HPP
#define POA_LABO3_BOAT_HPP

#include "Container.hpp"
#include "Bank.hpp"

enum BoatSide {
   LEFT, RIGHT
};

class Boat : public Container {

public:
   /**
    * Creates a new boat
    * @param name boat's name
    * @param bank boat's current bank
    */
   Boat(const std::string& name, Bank* bank);

   /**
    * Define the boat's current bank
    * @param bank new boat's bank
    */
   void setCurrentBank(Bank* bank);

   /**
    * Check if the boat can be driven by someone in the boat
    * @return true if it has a driver, else false
    */
   bool hasDriver() const;


   std::ostream& toStream(std::ostream& os) const override;

   bool add(Person* person) override;

private:
   Bank* currentBank;
   const static unsigned MAX_CAPACITY;
};

#endif //POA_LABO3_BOAT_HPP
