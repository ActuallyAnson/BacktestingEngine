#include "market_data.h"
#include <iostream>
#include <fstream>
#include <sstream>

// TODO: Implement constructors
MarketData::MarketData(){
    filename_ = "";
}

MarketData::MarketData(const std::string& file) {
    filename_ = file;
    loadFromFile(file);
};

// TODO: Implement loadFromFile method
bool MarketData::loadFromFile(const std::string& file) {
    std::ifstream inputfile(file);
    if(!inputfile) {
        return false;
    }

    bars_.clear();

    //read line by line
    std::string line;
    bool first_line = true;

    while(std::getline(inputfile,line)) {
        if(first_line) {
            first_line = false;
            continue;
        }
        Bar bar;
        if (parseLine(line, bar)) {
            bars_.push_back(bar);
        }
        else {
            std::cerr << "Warning: Could not parse line: " << line << std::endl;
        }
    }
    inputfile.close();
    return true;
}

bool MarketData::parseLine(const std::string& line, Bar& bar){
    std::stringstream ss(line);
    std::string token;

    // O(1) space: Fixed array of pointers to Bar fields
    double* fields[] = {&bar.timestamp, &bar.open, &bar.high, &bar.low, &bar.close, &bar.volume};
    
    try {
        for (int i = 0; i < 6; i++) {
            //getline till ',' is found. aka the delimiter
            if (!std::getline(ss, token, ',')) {
                return false;  // Not enough fields
            }
            *fields[i] = std::stod(token);  // convert string to double and assign
        }
        return true;
    } catch(const std::exception& e) {
        return false;  // Conversion failed
    }
}

// getters
size_t MarketData::size() const {
    return bars_.size();
}

const Bar& MarketData::getBar(size_t index) const {
    if (index >= bars_.size()){
        throw std::out_of_range("index out of range");
    }
    return bars_[index];
}
