//
// Created by Sanjula Gathsara on 2026-03-24.
//

#ifndef FLOWER_EXCHANGER_CSVREADER_H
#define FLOWER_EXCHANGER_CSVREADER_H

#include <vector>
#include <string>
#include "Order.h"

class CsvReader {
public:
    static std::vector<Order> readOrders(const std::string& filename);
};

#endif //FLOWER_EXCHANGER_CSVREADER_H