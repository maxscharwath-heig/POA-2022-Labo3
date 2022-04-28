#ifndef POA_LABO3_BANK_HPP
#define POA_LABO3_BANK_HPP

#include <string>
#include "Container.hpp"

class Bank : public Container {

public:
    explicit Bank(const std::string& name);

    std::ostream& toStream(std::ostream& os) const override;

};


#endif //POA_LABO3_BANK_HPP
