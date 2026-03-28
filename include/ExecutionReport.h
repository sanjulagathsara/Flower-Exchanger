//
// Created by Sanjula Gathsara on 2026-03-24.
//

#ifndef FLOWER_EXCHANGER_EXECUTIONREPORT_H
#define FLOWER_EXCHANGER_EXECUTIONREPORT_H

#include <string>

class ExecutionReport {
public:
    std::string clientOrderId;
    std::string orderId;
    std::string instrument;
    int side;
    int price;              // cents
    int quantity;
    int status;             // 0=New, 1=Rejected, 2=Fill, 3=PFill
    std::string reason;
    std::string transactionTime;

    void printReport() const {
        std::cout << clientOrderId << " " << orderId << " " << instrument << " " << side << " " << price/100 << "." << price%100 << " " << quantity << " " << status << " " << reason << " " << transactionTime << std::endl;
    }
};
#endif //FLOWER_EXCHANGER_EXECUTIONREPORT_H