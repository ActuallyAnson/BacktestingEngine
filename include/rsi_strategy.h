#pragma once
#include "strategy.h"

class RSIStrategy : public Strategy {

    public:
    RSIStrategy(int rsi_period);

    Signal analyze(const MarketData& data, size_t index) override;

    private:
        
    int rsi_period_;    

    double calculateRSI(const MarketData& data, size_t index, int period);


};
