//
// Created by Sanjula Gathsara on 2026-03-24.
//

#include "../include/CsvReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Order> CsvReader::readOrders(const std::string& filename) {
    std::vector<Order> orders;

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;

        Order order;

        // Client Order ID
        std::getline(ss, order.clientOrderId, ',');

        // Instrument
        std::getline(ss, order.instrument, ',');

        // Side
        std::getline(ss, token, ',');
        order.side = std::stoi(token);

        // Quantity
        std::getline(ss, token, ',');
        order.quantity = std::stoi(token);

        // Price (double → int cents)
        std::getline(ss, token, ',');
        double priceDouble = std::stod(token);
        order.price = static_cast<int>(priceDouble * 100 + 0.5);

        orders.push_back(order);
    }

    return orders;
}