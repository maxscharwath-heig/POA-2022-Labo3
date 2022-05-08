#ifndef POA_LABO3_BOAT_HPP
#define POA_LABO3_BOAT_HPP

#include "Container.hpp"
#include "Bank.hpp"

enum BoatSide {
   LEFT, RIGHT
};

class Boat : public Container {

public:
   explicit Boat(const std::string& name, Bank* bank);

   void setCurrentBank(Bank* bank);

   std::ostream& toStream(std::ostream& os) const override;

   bool hasDriver() const;

   bool add(Person* person) override;

private:
   Bank* currentBank;
   const static unsigned MAX_CAPACITY;
};

#endif //POA_LABO3_BOAT_HPP
