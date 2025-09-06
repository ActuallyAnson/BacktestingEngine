#pragma once

/**
 * @brief Position class tracks ownership of shares in a single stock
 * 
 * Manages:
 * - How many shares we currently own
 * - Average price we paid for them
 * - Current market value and P&L calculations
 */
class Position {
public:
    // Constructor - starts with no shares
    Position();
    
    // Trading operations
    void buyShares(int quantity, double price);
    void sellShares(int quantity, double price);
    
    // Getters
    int getShares() const;
    double getAveragePrice() const;
    bool isEmpty() const;  // true if we own 0 shares
    
    // Market value calculations (require current market price)
    double getCurrentValue(double currentPrice) const;
    double getUnrealizedPnL(double currentPrice) const;
    
private:
    int shares_;           // Number of shares currently owned
    double averagePrice_;  // Average price paid per share
    
    // Helper method to recalculate average price when buying more
    void updateAveragePrice(int newShares, double newPrice);
};
