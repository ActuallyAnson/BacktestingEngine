#pragma once

#include "strategy.h"

class SMACrossoverStrategy: public Strategy {
    public:
        SMACrossoverStrategy(int short_period, int long_period);

        //main method - Decides buy/sell/hold. Index == period of time chosen
        Signal analyze(const MarketData& data, size_t index) override;
    private:
        int short_period_;
        int long_period_;

        //helper
        double calculateMA(const MarketData& data, size_t index, int period);
};