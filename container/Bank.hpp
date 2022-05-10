#ifndef POA_LABO3_BANK_HPP
#define POA_LABO3_BANK_HPP

#include <string>
#include "Container.hpp"

/**
 * Represents a river's bank
 *
 * @author Nicolas Crausaz
 * @author Maxime Scharwath
 * @date 10.05.2022
 */
class Bank : public Container {
public:
    /**
     * Creates a new river bank
     * @param name name of the bank
     */
    explicit Bank(const std::string& name);

    std::ostream& toStream(std::ostream& os) const override;
};


#endif //POA_LABO3_BANK_HPP
