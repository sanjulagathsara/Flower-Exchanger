//
// Created by Sanjula Gathsara on 2026-03-24.
//

#include "../include/Validator.h"
#include <regex>
#include <set>

bool Validator::validate(const Order& order, std::string& reason) {
    static const std::set<std::string> validInstruments = {
        "Rose", "Lavender", "Lotus", "Tulip", "Orchid"
    };

    if (order.clientOrderId.empty()) {
        reason = "Client Order ID is empty";
        return false;
    }

    if (order.clientOrderId.size() > 7) {
        reason = "Client Order ID must be max 7 chars";
        return false;
    }

    if (!std::regex_match(order.clientOrderId, std::regex("^[A-Za-z0-9]+$"))) {
        reason = "Client Order ID must be alphanumeric";
        return false;
    }

    if (validInstruments.find(order.instrument) == validInstruments.end()) {
        reason = "Invalid instrument";
        return false;
    }

    if (order.side != 1 && order.side != 2) {
        reason = "Invalid side";
        return false;
    }

    if (order.price <= 0) {
        reason = "Price must be greater than 0";
        return false;
    }

    if (order.quantity < 10 || order.quantity > 1000) {
        reason = "Quantity must be between 10 and 1000";
        return false;
    }

    if (order.quantity % 10 != 0) {
        reason = "Quantity must be a multiple of 10";
        return false;
    }

    return true;
}