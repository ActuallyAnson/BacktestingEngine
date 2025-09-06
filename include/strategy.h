#pragma once

#include "signal.h"
#include "market_data.h"

class Strategy {
    public:
        //main method - Decides buy/sell/hold. Index == period of time chosen
        virtual Signal analyze(const MarketData& data, size_t index) = 0;

        virtual ~Strategy() = default;

};