#include <exception>
#include <iostream>
#include <vector>

#include "../include/CsvReader.h"
#include "../include/CsvWriter.h"
#include "../include/ExecutionReport.h"
#include "../include/OrderBook.h"
#include "../include/Validator.h"

namespace {
    ExecutionReport makeRejectedReport(const Order& order) {
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
}

int main() {
    try {
        const std::string inputFile = "../data/order.csv";
        const std::string outputFile = "../output/exeReports.csv";

        OrderBook book;
        const auto parsedRows = CsvReader::readOrders(inputFile);

        std::vector<ExecutionReport> allReports;

        for (const auto& row : parsedRows) {
            if (!row.parseSuccess) {
                allReports.push_back(makeRejectedReport(row.order));
                continue;
            }

            std::string reason;
            if (!Validator::validate(row.order, reason)) {
                allReports.push_back(makeRejectedReport(row.order));
                continue;
            }

            auto reports = book.processOrder(row.order);
            allReports.insert(allReports.end(), reports.begin(), reports.end());
        }

        for (const auto& report : allReports) {
            report.printReport();
        }

        CsvWriter::writeExecutionReports(outputFile, allReports);

        std::cout << "\nExecution reports written to: " << outputFile << '\n';
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}