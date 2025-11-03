// Portfolio.h
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Stock.h"

class PortfolioHolding {
private:
    std::string symbol;
    int quantity;
    double averageCost;
    double basis;

public:
    PortfolioHolding(const std::string& sym, int qty, double cost);

    void updateCurrentValue(double currentPrice);
    double getCurrentValue(double currentPrice) const;
    double getUnrealizedGainLoss(double currentPrice) const;
    double getPercentGainLoss(double currentPrice) const;

    // Getters
    std::string getSymbol() const { return symbol; }
    int getQuantity() const { return quantity; }
    double getAverageCost() const { return averageCost; }
    double getBasis() const { return basis; }
};

class Portfolio {
private:
    std::string portfolioId;
    std::string portfolioName;
    double cashBalance;
    std::string ownerName;
    std::string createdDate;
    std::vector<PortfolioHolding> holdings;

public:
    Portfolio(const std::string& id, const std::string& name,
        double cash, const std::string& owner, const std::string& date);

    // Portfolio management
    bool buyStock(const std::string& symbol, int quantity, double price, double commission = 9.99);
    bool sellStock(const std::string& symbol, int quantity, double price, double commission = 9.99);
    void addHolding(const PortfolioHolding& holding);

    // Calculations
    double calculateTotalValue(const std::vector<Stock>& stocks) const;
    double calculateUnrealizedGainLoss(const std::vector<Stock>& stocks) const;
    void displayPortfolio(const std::vector<Stock>& stocks) const;

    // Getters
    std::string getPortfolioId() const { return portfolioId; }
    double getCashBalance() const { return cashBalance; }
    const std::vector<PortfolioHolding>& getHoldings() const { return holdings; }
};