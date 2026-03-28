#ifndef FLOWER_EXCHANGER_CSVREADER_H
#define FLOWER_EXCHANGER_CSVREADER_H

#include <string>
#include <vector>
#include "Order.h"

struct ParsedOrderRow {
    Order order;
    bool parseSuccess = false;
    std::string error;
};

class CsvReader {
public:
    static std::vector<ParsedOrderRow> readOrders(const std::string& filename);
};

#endif // FLOWER_EXCHANGER_CSVREADER_H