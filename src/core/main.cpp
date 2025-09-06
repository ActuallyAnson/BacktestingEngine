#include <iostream>
#include "market_data.h"
#include "sma_crossover_strategy.h"
#include "signal.h"
#include "portfolio.h"

int main() {
    std::cout << "Backtester Engine v1.0.0" << std::endl;
    std::cout << "Testing MarketData class..." << std::endl;
    
    // Test MarketData with real Apple data
    MarketData data("../data/daily_AAPL.csv");
    std::cout << "Loaded " << data.size() << " bars" << std::endl;
    if (data.size() > 0) {
        const Bar& firstBar = data.getBar(0);
        std::cout << "First bar: Open=" << firstBar.open << ", Close=" << firstBar.close << std::endl;
    }
    
    std::cout << "\nTesting SMA Crossover Strategy..." << std::endl;
    
    // Create strategy: x-day short SMA, x-day long SMA
    // CHANGE THIS
    SMACrossoverStrategy strategy(3, 5);
    
    // Create portfolio with $10,000 starting capital
    Portfolio portfolio(10000.0);
    
    // Track statistics
    int totalTrades = 0;
    int buySignals = 0;
    int sellSignals = 0;
    int holdSignals = 0;
    Signal lastSignal = Signal::Hold;
    Signal currentSignal = Signal::Hold;
    
    // Test strategy on each bar
    for (size_t i = 0; i < data.size(); i++) {
        currentSignal = strategy.analyze(data, i);
        const Bar& bar = data.getBar(i);
        
        // Count signals
        if (currentSignal == Signal::Buy) buySignals++;
        else if (currentSignal == Signal::Sell) sellSignals++;
        else holdSignals++;
        
        // Count trades (signal changes)
        if (i > 0 && currentSignal != lastSignal && currentSignal != Signal::Hold) {
            totalTrades++;
            std::cout << "TRADE " << totalTrades << " - Day " << i << ": " 
                      << signalToString(currentSignal) << " at $" << bar.close << std::endl;
        }
        
        // Execute signal in portfolio
        portfolio.executeSignal(currentSignal, bar.close, i);
        
        lastSignal = currentSignal;
    }
    
    // Print Summary
    std::cout << "\n=== STRATEGY SUMMARY ===" << std::endl;
    std::cout << "Total Days Analyzed: " << data.size() << std::endl;
    std::cout << "Total Trades: " << totalTrades << std::endl;
    std::cout << "BUY signals: " << buySignals << std::endl;
    std::cout << "SELL signals: " << sellSignals << std::endl;
    std::cout << "HOLD signals: " << holdSignals << std::endl;
    
    // Print final portfolio results
    if (data.size() > 0) {
        const Bar& lastBar = data.getBar(data.size() - 1);
        portfolio.printSummary(lastBar.close);
    }
    
    return 0;
}
