#ifndef FLOWER_EXCHANGER_ORDER_H
#define FLOWER_EXCHANGER_ORDER_H

#include <string>

class Order {
public:
    std::string orderId;         // internal exchange id
    std::string clientOrderId;
    std::string instrument;
    int side = 0;                // 1 = Buy, 2 = Sell
    int quantity = 0;            // remaining quantity
    int price = 0;               // cents
};

#endif // FLOWER_EXCHANGER_ORDER_H