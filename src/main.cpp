#include <iostream>
#include <vector>

#include "../include/CsvReader.h"
#include "../include/OrderBook.h"
#include "../include/Validator.h"

int main() {
    try {
        OrderBook book;

        // Read CSV
        auto orders = CsvReader::readOrders("../data/order.csv");

        // Print Orders for Debugging CSV Reads
        for (const auto& order : orders) {
            order.printOrder();
        }

        std::vector<ExecutionReport> allReports;

        for (const auto& order : orders) {
            std::string reason;

            // Validate
            if (!Validator::validate(order, reason)) {
                ExecutionReport rejected;
                rejected.clientOrderId = order.clientOrderId;
                rejected.orderId = "ord_rej";
                rejected.instrument = order.instrument;
                rejected.side = order.side;
                rejected.price = order.price;
                rejected.quantity = order.quantity;
                rejected.status = 1;
                rejected.reason = reason;
                rejected.transactionTime = "20260324-120000.000"; // replace later

                allReports.push_back(rejected);
                continue;
            }

            // Send to OrderBook
            auto reports = book.processOrder(order);

            allReports.insert(allReports.end(), reports.begin(), reports.end());
        }

        // Print Execution Results for Debugging
        for (const auto& r : allReports) {
            r.printReport();
        }

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}