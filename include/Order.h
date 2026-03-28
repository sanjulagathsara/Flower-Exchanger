//
// Created by Sanjula Gathsara on 2026-03-24.
//

#ifndef FLOWER_EXCHANGER_ORDER_H
#define FLOWER_EXCHANGER_ORDER_H

#include <iostream>
#include <string>

class Order {
    public:
    std::string clientOrderId;
    std::string instrument;
    int side;       // 1 = Buy, 2 = Sell
    int quantity;   // remaining quantity
    int price;      // store as cents, e.g. 55.00 => 5500

    void printOrder() const {
        std::cout << clientOrderId << " " << instrument << " " << side << " " << quantity << " " << price/100 << "." << price%100 << "\n";
    };

};

#endif //FLOWER_EXCHANGER_ORDER_H