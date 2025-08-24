#include <iostream>
#include "engine.h"
#include "market_data.h"

int main() {
    std::cout << "Backtester Engine v1.0.0" << std::endl;
    std::cout << "Testing MarketData class..." << std::endl;
    
    // Test MarketData
    MarketData data("../data/test.csv");
    std::cout << "Loaded " << data.size() << " bars" << std::endl;
    if (data.size() > 0) {
        const Bar& firstBar = data.getBar(0);
        std::cout << "First bar: Open=" << firstBar.open << ", Close=" << firstBar.close << std::endl;
    }
    
    return 0;
}
