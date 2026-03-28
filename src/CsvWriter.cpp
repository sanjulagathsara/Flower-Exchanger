#include "../include/CsvWriter.h"

#include <fstream>
#include <stdexcept>

void CsvWriter::writeExecutionReports(const std::string& filename,
                                      const std::vector<ExecutionReport>& reports) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open output file: " + filename);
    }

    file << "Order ID,Cl. Ord. ID,Instrument,Side,Exec Status,Quantity,Price\n";

    for (const auto& report : reports) {
        file << report.orderId << ","
             << report.clientOrderId << ","
             << report.instrument << ","
             << report.side << ","
             << report.execStatus << ","
             << report.quantity << ","
             << ExecutionReport::formatPrice(report.price) << "\n";
    }
}