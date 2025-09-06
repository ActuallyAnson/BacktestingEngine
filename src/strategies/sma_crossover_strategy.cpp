#include "sma_crossover_strategy.h"
#include <iostream>

SMACrossoverStrategy::SMACrossoverStrategy(int short_period, int long_period):
short_period_(short_period), long_period_(long_period) {
//test

}

double SMACrossoverStrategy::calculateMA(const MarketData& data, size_t index, int period) {
    //index: Which day we're currently analyzing (like "Day 5")
    //period: How many recent days to average (like "3 days")
    // if on Day 2 but want a 3-day average, means can't calculate it yet
    if (index+1 < period) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 0; i < period; i++) {
        size_t bar_index = index - i;
        sum += data.getBar(bar_index).close;
    }
    return sum/period;
}

Signal SMACrossoverStrategy::analyze(const MarketData& data, size_t index) {
    double short_MA = calculateMA(data, index, short_period_);
    double long_MA = calculateMA(data, index, long_period_ );
    
    if (short_MA == 0.0 || long_MA == 0.0) {
        return Signal::Hold;
    }
    
    if (short_MA > long_MA) {
        return Signal::Buy;
    }
    else if(short_MA < long_MA) {
        return Signal::Sell;
    }
    else {
        return Signal::Hold;
    }
}