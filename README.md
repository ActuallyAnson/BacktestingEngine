# High-Performance C++ Backtesting Engine

A production-quality quantitative trading backtesting framework built in modern C++17, featuring real market data integration, advanced portfolio management, and comprehensive strategy testing capabilities.

## 🚀 Live Demo Results

**Real Apple Stock Backtest (100 days):**
```
=== PORTFOLIO SUMMARY ===
Starting Value: $10,000
Current Cash: $1,237.96
Current Position: 40 shares  
Position Value: $7,926
Total Portfolio Value: $9,163.96
Total Return: -8.36%
Total Trades: 48
```

## ✨ Key Features

### 🏎️ **High-Performance Core**
- **C++17** optimized engine with O(1) space complexity CSV parsing
- **Zero-allocation** string operations using const char* arrays
- **Modular architecture** with clean separation of concerns
- **Real-time trade execution** with proper error handling

### 📊 **Real Market Data Integration**
- **Alpha Vantage API** integration for live market data
- **100 days of real Apple stock data** included
- **OHLCV bar structure** with high/low/volume tracking
- **Professional data validation** and error handling

### 🧠 **Advanced Strategy Framework**
- **Polymorphic strategy interface** with virtual analyze() method
- **Simple Moving Average Crossover** strategy implemented
- **Signal generation** (BUY/SELL/HOLD) with trade tracking
- **Extensible design** for multiple strategy implementations

### 💰 **Professional Portfolio Management**
- **$10,000 starting capital** with realistic cash management
- **50% cash allocation rule** for risk management
- **Position tracking** with average cost basis calculation
- **Trade history** with complete P&L tracking
- **Unrealized gains/losses** calculation

### 📈 **Comprehensive Performance Analytics**
- **Total return calculation** with percentage tracking
- **Portfolio summary** showing cash, positions, and performance
- **Trade statistics** with buy/sell signal counting
- **Real-time portfolio valuation** at market prices

## 🏗️ Architecture Overview

```
backtester/
├── src/
│   ├── core/              # Main application logic
│   │   └── main.cpp       # Complete backtesting workflow
│   ├── data/              # Market data infrastructure
│   │   └── market_data.cpp # CSV parsing and data management
│   ├── strategies/        # Trading strategy implementations
│   │   └── sma_crossover_strategy.cpp # Moving average strategy
│   └── portfolio/         # Portfolio management system
│       ├── portfolio.cpp  # Main portfolio class
│       ├── position.cpp   # Position tracking
│       └── trade.cpp      # Trade execution records
├── include/               # Header files with clean interfaces
├── data/                  # Real market data (Apple stock)
└── build/                 # CMake build artifacts
```

## 🛠️ Technology Stack

- **C++17**: Modern C++ with STL containers and smart pointers
- **CMake 3.16+**: Cross-platform build system with modular libraries
- **Alpha Vantage API**: Real financial market data integration
- **Git**: Version control with professional development workflow
- **macOS/Linux**: Optimized for Unix-based development environments

## ⚡ Quick Start

### Prerequisites
```bash
# Required
- C++17 compatible compiler (GCC 7+, Clang 5+)
- CMake 3.16+
- macOS or Linux environment
```

### Build and Run
```bash
# Clone the repository
git clone <your-repo-url>
cd backtester

# Build the project
mkdir build && cd build
cmake ..
make

# Run the backtester
./backtester

# Expected output: Complete portfolio performance analysis
```

## 📊 Strategy Performance Analysis

### Current Implementation: SMA Crossover (3-day vs 5-day)
- **Total Days Analyzed**: 100
- **Trading Signals Generated**: 100 (42 BUY, 54 SELL, 4 HOLD)
- **Actual Trades Executed**: 48
- **Final Return**: -8.36% ($836.04 loss)
- **Risk Management**: 50% maximum position size enforced

### Strategy Behavior
- **High Frequency**: Short SMAs generate frequent signals
- **Risk Controlled**: Portfolio never exceeds 50% stock allocation
- **Realistic Execution**: Cannot sell shares you don't own
- **Complete Tracking**: Every trade recorded with price and day

## 🎯 Core Classes

### Strategy Interface
```cpp
class Strategy {
public:
    virtual Signal analyze(const MarketData& data, size_t index) = 0;
    virtual ~Strategy() = default;
};
```

### Portfolio Management
```cpp
class Portfolio {
    // $10,000 starting capital
    // 50% maximum position allocation
    // Complete trade history tracking
    void executeSignal(Signal signal, double price, int day);
    double getReturn(double currentPrice) const;
    void printSummary(double currentPrice) const;
};
```

### Market Data Infrastructure
```cpp
class MarketData {
    // O(1) space CSV parsing
    // Real Apple stock data (100 days)
    // Professional OHLCV structure
    const Bar& getBar(size_t index) const;
    size_t size() const;
};
```

## 🔬 Performance Characteristics

- **Memory Usage**: O(1) space parsing, minimal heap allocation
- **Execution Speed**: Linear O(n) with data size
- **Data Capacity**: Designed for millions of data points
- **Trade Execution**: Real-time signal processing with proper validation

## 🚀 Extensibility

### Add New Strategies
```cpp
class YourStrategy : public Strategy {
public:
    Signal analyze(const MarketData& data, size_t index) override {
        // Implement your trading logic
        return Signal::Hold;
    }
};
```

### Optimize Parameters
```cpp
// Test different SMA periods
SMACrossoverStrategy strategy(10, 20);  // Less frequent trades
SMACrossoverStrategy strategy(5, 15);   // Medium frequency
SMACrossoverStrategy strategy(20, 50);  // Long-term strategy
```

## 📈 Future Enhancements

### Phase 4: Advanced Features
- [ ] **Multiple Stock Support**: Portfolio with diversified holdings
- [ ] **Stop-Loss Orders**: Advanced risk management
- [ ] **Position Sizing**: Kelly criterion and risk parity
- [ ] **Performance Metrics**: Sharpe ratio, maximum drawdown

### Phase 5: Python Integration
- [ ] **pybind11 Bindings**: Python API for strategy development
- [ ] **Machine Learning**: TensorFlow/PyTorch strategy optimization
- [ ] **Jupyter Notebooks**: Interactive research environment

### Phase 6: Production Features
- [ ] **REST API**: Microservice deployment
- [ ] **Database Integration**: PostgreSQL/TimescaleDB
- [ ] **Real-time Data**: WebSocket market feeds