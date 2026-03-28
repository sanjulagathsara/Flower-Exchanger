#ifndef FLOWER_EXCHANGER_EXECUTIONREPORT_H
#define FLOWER_EXCHANGER_EXECUTIONREPORT_H

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class ExecutionReport {
public:
    std::string orderId;
    std::string clientOrderId;
    std::string instrument;
    int side = 0;
    std::string execStatus;      // New, Rejected, Fill, Pfill
    int quantity = 0;            // New => order qty, Fill/Pfill => executed qty
    int price = 0;               // New => order price, Fill/Pfill => execution price

    static std::string formatPrice(int cents) {
        std::ostringstream oss;
        oss << (cents / 100) << "."
            << std::setw(2) << std::setfill('0') << (cents % 100);
        return oss.str();
    }

    void printReport() const {
        std::cout
            << orderId << ","
            << clientOrderId << ","
            << instrument << ","
            << side << ","
            << execStatus << ","
            << quantity << ","
            << formatPrice(price)
            << '\n';
    }
};

#endif // FLOWER_EXCHANGER_EXECUTIONREPORT_H