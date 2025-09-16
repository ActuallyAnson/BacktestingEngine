#include "rsi_strategy.h"

RSIStrategy::RSIStrategy(int rsi_period) : rsi_period_(rsi_period) {
    // Constructor body
}


Signal RSIStrategy::analyze(const MarketData& data, size_t index) {
    double rsi = calculateRSI(data, index,rsi_period_);
    if (rsi < 30) return Signal::Buy;
    if (rsi > 70) return Signal::Sell;
    return Signal::Hold;
}


double RSIStrategy::calculateRSI(const MarketData& data, size_t index, int period) {
    if (index < period) return 50.0;
    double totalGain = 0.0;
    double totalLoss = 0.0;

    for (int i = 0; i < period; i++) {
        size_t today_idx = index - i;
        size_t yesterday_idx = index - i - 1;

        //calculate change:
        double today_price = data.getBar(today_idx).close;
        double yesterday_price = data.getBar(yesterday_idx).close;
        double change = today_price - yesterday_price;

        if (change > 0) {
            totalGain+=change;
        }
        else {
            totalLoss -= change;
        }
    }

    double averageGain = totalGain / period;
    double averageLoss = totalLoss/ period;

    if (averageLoss == 0) return 100.0;
    
    double rs = averageGain / averageLoss;
    double rsi = 100.0 - (100.0/(1.0 + rs));


    return rsi;
}