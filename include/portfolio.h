#pragma once

#include "signal.h"
#include "trade.h"
#include "position.h"
#include <vector>
#include <cstddef>

class Portfolio {
    public:
        Portfolio(double startingCash);
        //trading methods
        void executeSignal(Signal signal, double price, size_t dayIndex);

        //status of portfolio
        double getCash() const;
        double getTotalValue(double currentPrice) const;
        double getReturn(double currentPrice) const;
        
        //trade history
        const std::vector<Trade>& getTradeHistory() const;
        void printSummary(double currentPrice) const;  // Add portfolio summary
  
    private:
        double cash_;
        Position position_;
        std::vector<Trade> tradeHistory_;
        double startingValue_;
};