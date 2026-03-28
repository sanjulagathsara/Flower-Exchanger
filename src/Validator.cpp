#include "../include/Validator.h"

#include <algorithm>
#include <cctype>
#include <set>
#include <string>

namespace {
    const std::set<std::string> validInstruments = {
        "Rose", "Lavender", "Lotus", "Tulip", "Orchid"
    };

    bool isAlphaNumeric(const std::string& s) {
        return !s.empty() &&
               std::all_of(s.begin(), s.end(), [](unsigned char ch) {
                   return std::isalnum(ch) != 0;
               });
    }
}

bool Validator::validate(const Order& order, std::string& reason) {
    if (order.clientOrderId.empty()) {
        reason = "Client Order ID is empty";
        return false;
    }

    if (order.clientOrderId.size() > 7) {
        reason = "Client Order ID must be max 7 chars";
        return false;
    }

    if (!isAlphaNumeric(order.clientOrderId)) {
        reason = "Client Order ID must be alphanumeric";
        return false;
    }

    if (order.instrument.empty()) {
        reason = "Instrument is empty";
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