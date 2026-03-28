#include "../include/OrderBook.h"

#include <algorithm>

std::vector<ExecutionReport> OrderBook::processOrder(const Order& order) {
    Order incoming = order;
    incoming.orderId = generateOrderId();

    auto& instrumentBook = books[incoming.instrument];

    if (incoming.side == 1) {
        return matchBuy(incoming, instrumentBook);
    }

    return matchSell(incoming, instrumentBook);
}

std::vector<ExecutionReport> OrderBook::matchBuy(Order& incoming, InstrumentOrderBook& book) {
    std::vector<ExecutionReport> reports;
    bool matchedAnything = false;

    while (incoming.quantity > 0 && !book.sellOrders.empty()) {
        auto bestSellIt = book.sellOrders.begin(); // lowest sell price first

        if (bestSellIt->first > incoming.price) {
            break;
        }

        auto& queue = bestSellIt->second;
        Order& resting = queue.front();

        const int tradedQty = std::min(incoming.quantity, resting.quantity);
        const int tradePrice = resting.price;

        incoming.quantity -= tradedQty;
        resting.quantity -= tradedQty;
        matchedAnything = true;

        reports.push_back(makeTradeReport(
            incoming,
            tradedQty,
            tradePrice,
            incoming.quantity == 0 ? "Fill" : "Pfill"
        ));

        reports.push_back(makeTradeReport(
            resting,
            tradedQty,
            tradePrice,
            resting.quantity == 0 ? "Fill" : "Pfill"
        ));

        if (resting.quantity == 0) {
            queue.pop_front();
        }

        if (queue.empty()) {
            book.sellOrders.erase(bestSellIt);
        }
    }

    if (!matchedAnything) {
        book.buyOrders[incoming.price].push_back(incoming);
        reports.push_back(makeNewReport(incoming));
    } else if (incoming.quantity > 0) {
        book.buyOrders[incoming.price].push_back(incoming);
    }

    return reports;
}

std::vector<ExecutionReport> OrderBook::matchSell(Order& incoming, InstrumentOrderBook& book) {
    std::vector<ExecutionReport> reports;
    bool matchedAnything = false;

    while (incoming.quantity > 0 && !book.buyOrders.empty()) {
        auto bestBuyIt = book.buyOrders.begin(); // highest buy price first

        if (bestBuyIt->first < incoming.price) {
            break;
        }

        auto& queue = bestBuyIt->second;
        Order& resting = queue.front();

        const int tradedQty = std::min(incoming.quantity, resting.quantity);
        const int tradePrice = resting.price;

        incoming.quantity -= tradedQty;
        resting.quantity -= tradedQty;
        matchedAnything = true;

        reports.push_back(makeTradeReport(
            incoming,
            tradedQty,
            tradePrice,
            incoming.quantity == 0 ? "Fill" : "Pfill"
        ));

        reports.push_back(makeTradeReport(
            resting,
            tradedQty,
            tradePrice,
            resting.quantity == 0 ? "Fill" : "Pfill"
        ));

        if (resting.quantity == 0) {
            queue.pop_front();
        }

        if (queue.empty()) {
            book.buyOrders.erase(bestBuyIt);
        }
    }

    if (!matchedAnything) {
        book.sellOrders[incoming.price].push_back(incoming);
        reports.push_back(makeNewReport(incoming));
    } else if (incoming.quantity > 0) {
        book.sellOrders[incoming.price].push_back(incoming);
    }

    return reports;
}

std::string OrderBook::generateOrderId() {
    return "ord" + std::to_string(nextOrderNumber++);
}

ExecutionReport OrderBook::makeNewReport(const Order& order) const {
    ExecutionReport report;
    report.orderId = order.orderId;
    report.clientOrderId = order.clientOrderId;
    report.instrument = order.instrument;
    report.side = order.side;
    report.execStatus = "New";
    report.quantity = order.quantity;
    report.price = order.price;
    return report;
}

ExecutionReport OrderBook::makeRejectedReport(const Order& order) const {
    ExecutionReport report;
    report.orderId = "NA";
    report.clientOrderId = order.clientOrderId;
    report.instrument = order.instrument;
    report.side = order.side;
    report.execStatus = "Rejected";
    report.quantity = order.quantity;
    report.price = order.price;
    return report;
}

ExecutionReport OrderBook::makeTradeReport(const Order& order,
                                           int tradedQty,
                                           int tradePrice,
                                           const std::string& status) const {
    ExecutionReport report;
    report.orderId = order.orderId;
    report.clientOrderId = order.clientOrderId;
    report.instrument = order.instrument;
    report.side = order.side;
    report.execStatus = status;
    report.quantity = tradedQty;
    report.price = tradePrice;
    return report;
}