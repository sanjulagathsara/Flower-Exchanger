//
// Created by Sanjula Gathsara on 2026-03-24.
//

#include "../include/OrderBook.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>

std::vector<ExecutionReport> OrderBook::processOrder(Order order) {
    if (order.side == 1) {
        return matchBuy(order);
    }
    return matchSell(order);
}

std::vector<ExecutionReport> OrderBook::matchBuy(Order& incoming) {
    std::vector<ExecutionReport> reports;
    const std::string incomingOrderId = generateOrderId();

    int originalQty = incoming.quantity;
    int totalExecuted = 0;

    while (incoming.quantity > 0 && !sellOrders.empty()) {
        auto bestSellIt = sellOrders.begin(); // lowest sell price

        if (bestSellIt->first > incoming.price) {
            break;
        }

        auto& queue = bestSellIt->second;
        Order& resting = queue.front();

        int tradedQty = std::min(incoming.quantity, resting.quantity);

        incoming.quantity -= tradedQty;
        resting.quantity -= tradedQty;
        totalExecuted += tradedQty;

        int incomingStatus;
        if (incoming.quantity == 0) {
            incomingStatus = 2; // Fill
        } else {
            incomingStatus = 3; // PFill
        }

        reports.push_back(makeReport(
            incoming,
            incomingOrderId,
            tradedQty,
            incomingStatus
        ));

        if (resting.quantity == 0) {
            queue.pop_front();
        }

        if (queue.empty()) {
            sellOrders.erase(bestSellIt);
        }
    }

    if (totalExecuted == 0) {
        buyOrders[incoming.price].push_back(incoming);

        reports.push_back(makeReport(
            incoming,
            incomingOrderId,
            originalQty,
            0 // New
        ));
    } else if (incoming.quantity > 0) {
        buyOrders[incoming.price].push_back(incoming);

        reports.push_back(makeReport(
            incoming,
            incomingOrderId,
            incoming.quantity,
            3 // PFill
        ));
    }

    return reports;
}

std::vector<ExecutionReport> OrderBook::matchSell(Order& incoming) {
    std::vector<ExecutionReport> reports;
    const std::string incomingOrderId = generateOrderId();

    int originalQty = incoming.quantity;
    int totalExecuted = 0;

    while (incoming.quantity > 0 && !buyOrders.empty()) {
        auto bestBuyIt = buyOrders.begin(); // highest buy price

        if (bestBuyIt->first < incoming.price) {
            break;
        }

        auto& queue = bestBuyIt->second;
        Order& resting = queue.front();

        int tradedQty = std::min(incoming.quantity, resting.quantity);

        incoming.quantity -= tradedQty;
        resting.quantity -= tradedQty;
        totalExecuted += tradedQty;

        int incomingStatus;
        if (incoming.quantity == 0) {
            incomingStatus = 2; // Fill
        } else {
            incomingStatus = 3; // PFill
        }

        reports.push_back(makeReport(
            incoming,
            incomingOrderId,
            tradedQty,
            incomingStatus
        ));

        if (resting.quantity == 0) {
            queue.pop_front();
        }

        if (queue.empty()) {
            buyOrders.erase(bestBuyIt);
        }
    }

    if (totalExecuted == 0) {
        sellOrders[incoming.price].push_back(incoming);

        reports.push_back(makeReport(
            incoming,
            incomingOrderId,
            originalQty,
            0 // New
        ));
    } else if (incoming.quantity > 0) {
        sellOrders[incoming.price].push_back(incoming);

        reports.push_back(makeReport(
            incoming,
            incomingOrderId,
            incoming.quantity,
            3 // PFill
        ));
    }

    return reports;
}

std::string OrderBook::generateOrderId() {
    return "ord" + std::to_string(nextOrderNumber++);
}

std::string OrderBook::currentTimestamp() const {
    using namespace std::chrono;

    auto now = system_clock::now();
    auto millis = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::time_t timeNow = system_clock::to_time_t(now);
    std::tm localTime{};

#ifdef _WIN32
    localtime_s(&localTime, &timeNow);
#else
    localtime_r(&timeNow, &localTime);
#endif

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y%m%d-%H%M%S")
        << "."
        << std::setw(3) << std::setfill('0') << millis.count();

    return oss.str();
}

ExecutionReport OrderBook::makeReport(const Order& order,
                                      const std::string& orderId,
                                      int executedQty,
                                      int status,
                                      const std::string& reason) const {
    ExecutionReport report;
    report.clientOrderId = order.clientOrderId;
    report.orderId = orderId;
    report.instrument = order.instrument;
    report.side = order.side;
    report.price = order.price;
    report.quantity = executedQty;
    report.status = status;
    report.reason = reason;
    report.transactionTime = currentTimestamp();
    return report;
}