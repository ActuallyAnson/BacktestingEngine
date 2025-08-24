#pragma once

#include <vector>
#include <string>

struct Bar  {
    double timestamp; // maybe string or date? 
    double open;
    double high;
    double low;
    double close;
    double volume; //maybe int/long? for better performance?
};

/**
 * @brief MarketData class for loading and storing price data
 * 
 * This class handles:
 * - Loading OHLCV data from CSV files
 * - Storing time series data efficiently
 * - Providing access to historical bars
 */

class MarketData {
public:
    //constructors
    MarketData();
    MarketData(const std::string& file);
    
    //getters
    bool loadFromFile(const std::string& file);
    const Bar & getBar(size_t index) const;
    size_t size() const;
    
private:
    std::vector<Bar> bars_;
    std::string filename_;

    bool parseLine(const std::string& line, Bar & bar);
};
