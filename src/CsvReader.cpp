#include "../include/CsvReader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
    std::string trim(const std::string& s) {
        const std::string whitespace = " \t\r\n";
        const auto start = s.find_first_not_of(whitespace);
        if (start == std::string::npos) return "";
        const auto end = s.find_last_not_of(whitespace);
        return s.substr(start, end - start + 1);
    }

    bool readField(std::stringstream& ss, std::string& token) {
        return static_cast<bool>(std::getline(ss, token, ','));
    }
}

std::vector<ParsedOrderRow> CsvReader::readOrders(const std::string& filename) {
    std::vector<ParsedOrderRow> rows;

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;

    // skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (trim(line).empty()) {
            continue;
        }

        ParsedOrderRow row;
        std::stringstream ss(line);
        std::string token;

        if (!readField(ss, token) || trim(token).empty()) {
            row.error = "Missing required field: ClientOrderId";
            rows.push_back(row);
            continue;
        }
        row.order.clientOrderId = trim(token);

        if (!readField(ss, token) || trim(token).empty()) {
            row.error = "Missing required field: Instrument";
            rows.push_back(row);
            continue;
        }
        row.order.instrument = trim(token);

        if (!readField(ss, token) || trim(token).empty()) {
            row.error = "Missing required field: Side";
            rows.push_back(row);
            continue;
        }
        try {
            row.order.side = std::stoi(trim(token));
        } catch (...) {
            row.error = "Invalid side";
            rows.push_back(row);
            continue;
        }

        if (!readField(ss, token) || trim(token).empty()) {
            row.error = "Missing required field: Quantity";
            rows.push_back(row);
            continue;
        }
        try {
            row.order.quantity = std::stoi(trim(token));
        } catch (...) {
            row.error = "Invalid quantity";
            rows.push_back(row);
            continue;
        }

        if (!readField(ss, token) || trim(token).empty()) {
            row.error = "Missing required field: Price";
            rows.push_back(row);
            continue;
        }
        try {
            const double priceDouble = std::stod(trim(token));
            row.order.price = static_cast<int>(priceDouble * 100.0 + 0.5);
        } catch (...) {
            row.error = "Invalid price";
            rows.push_back(row);
            continue;
        }

        row.parseSuccess = true;
        rows.push_back(row);
    }

    return rows;
}