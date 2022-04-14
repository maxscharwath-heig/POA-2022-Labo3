#ifndef POA_LABO3_BOAT_HPP
#define POA_LABO3_BOAT_HPP

#include "Container.hpp"
#include "Bank.hpp"

class Boat: public Container {

public:
    explicit Boat(const std::string& name, Bank* bank);
    void setCurrentBank(Bank* bank);

private:
    Bank* currentBank;
};

#endif //POA_LABO3_BOAT_HPP
