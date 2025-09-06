#pragma once

#include "signal.h"
#include <cstddef>  // for size_t

/**
 * @brief Trade class records a single buy/sell transaction
 * 
 * Stores all the details of what happened when we executed a trade
 */
class Trade {
public:
    // Constructor - creates a new trade record
    Trade(Signal type, int quantity, double price, size_t dayIndex);

    //getters
    Signal getType() const;
    int getQuantity() const;
    double getPrice() const;
    size_t getDayIndex() const;
    double getTotalValue() const; //price * quantity
    
    private:
    Signal type_;
    int quantity_;
    double price_;
    size_t dayIndex_;
};