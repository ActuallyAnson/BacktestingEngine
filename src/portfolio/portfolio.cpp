#include "portfolio.h"
#include <iostream>

Portfolio::Portfolio(double startingCash) : 
    cash_(startingCash), 
    position_(),                    // Default constructor - starts with 0 shares
    tradeHistory_(),               // Empty vector of trades
    startingValue_(startingCash)   // Remember starting amount for return calculation
{
}

double Portfolio::getCash() const {
    return cash_;
}

double Portfolio::getTotalValue(double currentPrice) const {
    // Total portfolio value = cash + value of position
    return cash_ + position_.getCurrentValue(currentPrice);
}

double Portfolio::getReturn(double currentPrice) const {
    // Calculate percentage return from starting value
    double currentTotalValue = getTotalValue(currentPrice);
    return ((currentTotalValue - startingValue_) / startingValue_) * 100.0;
}

const std::vector<Trade>& Portfolio::getTradeHistory() const {
    return tradeHistory_;
} 

void Portfolio::executeSignal(Signal signal, double price, size_t dayIndex) {

    if (signal == Signal::Buy) {
        //buy logic
        double cashToSpend = cash_ * 0.5;
        if  (cashToSpend < price) {
            std::cout << "Day " << dayIndex << ": Not enough cash to buy (need $" 
            << price << ", have $" << cashToSpend << ")" << std::endl;
            return;
        }

        int sharesToBuy = static_cast<int> (cashToSpend/price);
        double actualCost = sharesToBuy * price;

        //execute purchase
        cash_ -= actualCost;
        position_.buyShares(sharesToBuy,price);

        tradeHistory_.push_back(Trade(Signal::Buy, sharesToBuy, price, dayIndex));
        std::cout << "Day " << dayIndex << ": BUY " << sharesToBuy 
                  << " shares at $" << price << " (cost: $" << actualCost << ")" << std::endl;
    }
    else if (signal == Signal::Sell) {
        int sharesToSell = position_.getShares();
        if (sharesToSell == 0) {
            std::cout << "Day " << dayIndex << ": Cannot sell - own 0 shares" << std::endl;
            return;
        }

        double saleProceeds = sharesToSell * price;

        position_.sellShares(sharesToSell,price);
        cash_ += saleProceeds;

        tradeHistory_.push_back(Trade(Signal::Sell,sharesToSell,price,dayIndex));
        std::cout << "Day " << dayIndex << ": SELL " << sharesToSell 
                  << " shares at $" << price << " (proceeds: $" << saleProceeds << ")" << std::endl;
    }
    
    else if (signal == Signal::Hold) {
    }    
}

void Portfolio::printSummary(double currentPrice) const {
    double currentTotalValue = getTotalValue(currentPrice);
    double returnPercent = getReturn(currentPrice);
    
    std::cout << "\n=== PORTFOLIO SUMMARY ===" << std::endl;
    std::cout << "Starting Value: $" << startingValue_ << std::endl;
    std::cout << "Current Cash: $" << cash_ << std::endl;
    std::cout << "Current Position: " << position_.getShares() << " shares" << std::endl;
    std::cout << "Position Value: $" << position_.getCurrentValue(currentPrice) << std::endl;
    std::cout << "Total Portfolio Value: $" << currentTotalValue << std::endl;
    std::cout << "Total Return: " << returnPercent << "%" << std::endl;
    std::cout << "Total Trades: " << tradeHistory_.size() << std::endl;
    
    if (!position_.isEmpty()) {
        std::cout << "Unrealized P&L: $" << position_.getUnrealizedPnL(currentPrice) << std::endl;
    }
}