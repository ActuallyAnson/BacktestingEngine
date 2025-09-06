#include "trade.h"

Trade::Trade(Signal type, int quantity, double price, size_t dayIndex):
type_(type), quantity_(quantity), price_(price), dayIndex_(dayIndex) {

}

Signal Trade::getType() const {
    return type_;
}

int Trade::getQuantity() const {
    return quantity_;
}

double Trade::getPrice() const {
    return price_;
}

size_t Trade::getDayIndex() const {
    return dayIndex_;
}

double Trade::getTotalValue() const {
    return quantity_ * price_;
}