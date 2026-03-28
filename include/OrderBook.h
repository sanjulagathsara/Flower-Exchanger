#ifndef FLOWER_EXCHANGER_ORDERBOOK_H
#define FLOWER_EXCHANGER_ORDERBOOK_H

#include <deque>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "ExecutionReport.h"
#include "Order.h"

class OrderBook {
public:
    using Price = int;

    std::vector<ExecutionReport> processOrder(const Order& order);

private:
    struct InstrumentOrderBook {
        std::map<Price, std::deque<Order>, std::greater<>> buyOrders; // highest price first
        std::map<Price, std::deque<Order>, std::less<>> sellOrders;   // lowest price first
    };

    std::map<std::string, InstrumentOrderBook> books;
    int nextOrderNumber = 1;

private:
    std::vector<ExecutionReport> matchBuy(Order& incoming, InstrumentOrderBook& book);
    std::vector<ExecutionReport> matchSell(Order& incoming, InstrumentOrderBook& book);

    std::string generateOrderId();

    ExecutionReport makeNewReport(const Order& order) const;
    ExecutionReport makeRejectedReport(const Order& order) const;
    ExecutionReport makeTradeReport(const Order& order,
                                    int tradedQty,
                                    int tradePrice,
                                    const std::string& status) const;
};

#endif // FLOWER_EXCHANGER_ORDERBOOK_H