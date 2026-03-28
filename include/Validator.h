#ifndef FLOWER_EXCHANGER_VALIDATOR_H
#define FLOWER_EXCHANGER_VALIDATOR_H

#include <string>
#include "Order.h"

class Validator {
public:
    static bool validate(const Order& order, std::string& reason);
};

#endif // FLOWER_EXCHANGER_VALIDATOR_H