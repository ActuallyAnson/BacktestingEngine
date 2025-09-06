#include "position.h"
#include <iostream>

Position::Position(): shares_(0), averagePrice_(0){

}

void Position::buyShares(int quantity, double price) {
    if(quantity <= 0) {
        std::cout << "Error: Cannot buy " << quantity << " shares" << std::endl;
        return;
    }

    if (shares_ == 0) {
        // First purchase - simple case
        shares_ = quantity;
        averagePrice_ = price;
    }
    else {
        // Adding to existing position - MUST update average price first!
        updateAveragePrice(quantity, price);
        shares_ += quantity;
    }
}

void Position::sellShares(int quantity, double price) {
    if (quantity <= 0) {
        std::cout << "Error: Cannot sell " << quantity << " shares" << std::endl;
        return;
    }

    if (quantity > shares_) {
        std::cout << "Error: Cannot sell " << quantity << " shares, only own " << shares_ << std::endl;
        return;
    }
    
    shares_ -= quantity;
    
    // If we sold all shares, reset average price
    if (shares_ == 0) {
        averagePrice_ = 0.0;
    }
}

int Position::getShares() const {
    return shares_;
}

double Position::getAveragePrice() const {
    return averagePrice_;
}

bool Position::isEmpty() const {
    return shares_ == 0;
}

double Position::getCurrentValue(double currentPrice) const {
    return shares_ * currentPrice;
}

double Position::getUnrealizedPnL(double currentPrice) const {
    if (shares_ == 0) {
        return 0.0;
    }
    return (currentPrice - averagePrice_) * shares_;
}

void Position::updateAveragePrice(int newShares, double newPrice) {
    // Calculate weighted average
    // Total value = (existing shares × existing avg) + (new shares × new price)
    // New average = total value ÷ total shares
    
    double totalValue = (shares_ * averagePrice_) + (newShares * newPrice);
    int totalShares = shares_ + newShares;
    averagePrice_ = totalValue / totalShares;
}