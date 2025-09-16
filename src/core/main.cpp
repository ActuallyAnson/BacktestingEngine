#include <iostream>
#include "market_data.h"
#include "sma_crossover_strategy.h"
#include "rsi_strategy.h"
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
    
    // ==========================================
    // STRATEGY COMPARISON: SMA vs RSI
    // ==========================================
    
    std::cout << "\n=== TESTING SMA CROSSOVER STRATEGY ===" << std::endl;
    
    // Test SMA Strategy
    SMACrossoverStrategy smaStrategy(3, 5);
    Portfolio smaPortfolio(10000.0);
    
    int smaTotalTrades = 0;
    int smaBuySignals = 0;
    int smaSellSignals = 0;
    int smaHoldSignals = 0;
    Signal smaLastSignal = Signal::Hold;
    
    for (size_t i = 0; i < data.size(); i++) {
        Signal smaSignal = smaStrategy.analyze(data, i);
        const Bar& bar = data.getBar(i);
        
        // Count signals
        if (smaSignal == Signal::Buy) smaBuySignals++;
        else if (smaSignal == Signal::Sell) smaSellSignals++;
        else smaHoldSignals++;
        
        // Count trades (signal changes)
        if (i > 0 && smaSignal != smaLastSignal && smaSignal != Signal::Hold) {
            smaTotalTrades++;
            std::cout << "SMA TRADE " << smaTotalTrades << " - Day " << i << ": " 
                      << signalToString(smaSignal) << " at $" << bar.close << std::endl;
        }
        
        // Execute signal in portfolio
        smaPortfolio.executeSignal(smaSignal, bar.close, i);
        smaLastSignal = smaSignal;
    }
    
    std::cout << "\n=== TESTING RSI STRATEGY ===" << std::endl;
    
    // Test RSI Strategy  
    RSIStrategy rsiStrategy(14);
    Portfolio rsiPortfolio(10000.0);
    
    int rsiTotalTrades = 0;
    int rsiBuySignals = 0;
    int rsiSellSignals = 0;
    int rsiHoldSignals = 0;
    Signal rsiLastSignal = Signal::Hold;
    
    // Test RSI strategy on each bar
    for (size_t i = 0; i < data.size(); i++) {
        Signal rsiSignal = rsiStrategy.analyze(data, i);
        const Bar& bar = data.getBar(i);
        
        // Count signals
        if (rsiSignal == Signal::Buy) rsiBuySignals++;
        else if (rsiSignal == Signal::Sell) rsiSellSignals++;
        else rsiHoldSignals++;
        
        // Count trades (signal changes)
        if (i > 0 && rsiSignal != rsiLastSignal && rsiSignal != Signal::Hold) {
            rsiTotalTrades++;
            std::cout << "RSI TRADE " << rsiTotalTrades << " - Day " << i << ": " 
                      << signalToString(rsiSignal) << " at $" << bar.close << std::endl;
        }
        
        // Execute signal in portfolio
        rsiPortfolio.executeSignal(rsiSignal, bar.close, i);
        rsiLastSignal = rsiSignal;
    }
    
    // ==========================================
    // STRATEGY COMPARISON RESULTS
    // ==========================================
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "         STRATEGY COMPARISON" << std::endl;
    std::cout << "========================================" << std::endl;
    
    // SMA Results
    std::cout << "\n=== SMA CROSSOVER (3-day vs 5-day) ===" << std::endl;
    std::cout << "Total Days Analyzed: " << data.size() << std::endl;
    std::cout << "Total Trades: " << smaTotalTrades << std::endl;
    std::cout << "BUY signals: " << smaBuySignals << std::endl;
    std::cout << "SELL signals: " << smaSellSignals << std::endl;
    std::cout << "HOLD signals: " << smaHoldSignals << std::endl;
    
    if (data.size() > 0) {
        const Bar& lastBar = data.getBar(data.size() - 1);
        smaPortfolio.printSummary(lastBar.close);
    }
    
    // RSI Results  
    std::cout << "\n=== RSI STRATEGY (14-day period) ===" << std::endl;
    std::cout << "Total Days Analyzed: " << data.size() << std::endl;
    std::cout << "Total Trades: " << rsiTotalTrades << std::endl;
    std::cout << "BUY signals: " << rsiBuySignals << std::endl;
    std::cout << "SELL signals: " << rsiSellSignals << std::endl;
    std::cout << "HOLD signals: " << rsiHoldSignals << std::endl;
    
    if (data.size() > 0) {
        const Bar& lastBar = data.getBar(data.size() - 1);
        rsiPortfolio.printSummary(lastBar.close);
    }
    
    // Performance Comparison
    std::cout << "\n========================================" << std::endl;
    std::cout << "         PERFORMANCE WINNER" << std::endl;
    std::cout << "========================================" << std::endl;
    
    if (data.size() > 0) {
        const Bar& lastBar = data.getBar(data.size() - 1);
        double smaReturn = smaPortfolio.getReturn(lastBar.close);
        double rsiReturn = rsiPortfolio.getReturn(lastBar.close);
        
        if (smaReturn > rsiReturn) {
            std::cout << "WINNER: SMA Crossover Strategy!" << std::endl;
            std::cout << "SMA Return: " << smaReturn << "%" << std::endl;
            std::cout << "RSI Return: " << rsiReturn << "%" << std::endl;
            std::cout << "Difference: +" << (smaReturn - rsiReturn) << "%" << std::endl;
        } else {
            std::cout << "WINNER: RSI Strategy!" << std::endl;
            std::cout << "RSI Return: " << rsiReturn << "%" << std::endl;
            std::cout << "SMA Return: " << smaReturn << "%" << std::endl;
            std::cout << "Difference: +" << (rsiReturn - smaReturn) << "%" << std::endl;
        }
    }
    
    return 0;
}
