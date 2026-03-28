//
// Created by Sanjula Gathsara on 2026-03-24.
//

#ifndef FLOWER_EXCHANGER_ORDERBOOK_H
#define FLOWER_EXCHANGER_ORDERBOOK_H
#include <map>
#include <deque>
#include <vector>
#include <functional>
#include <string>
#include "Order.h"
#include "ExecutionReport.h"

class OrderBook {
public:
    using Price = int;

    OrderBook() = default;

    std::vector<ExecutionReport> processOrder(Order order);

private:
    std::map<Price, std::deque<Order>, std::greater<>> buyOrders;
    std::map<Price, std::deque<Order>, std::less<>> sellOrders;

    int nextOrderNumber = 1;

private:
    std::vector<ExecutionReport> matchBuy(Order& incoming);
    std::vector<ExecutionReport> matchSell(Order& incoming);

    std::string generateOrderId();
    std::string currentTimestamp() const;

    ExecutionReport makeReport(const Order& order,
                               const std::string& orderId,
                               int executedQty,
                               int status,
                               const std::string& reason = "") const;
};


#endif //FLOWER_EXCHANGER_ORDERBOOK_H
