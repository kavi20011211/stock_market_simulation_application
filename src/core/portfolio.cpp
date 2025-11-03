#include"../../includes/core/portfolio.h"
#include<iostream>
#include<iomanip>

PortfolioHolding::PortfolioHolding(const std::string& sym, int qty, double cost)
    : symbol(sym), quantity(qty), averageCost(cost), basis(cost* qty) {}

double PortfolioHolding::getCurrentValue(double currentPrice) const {
    return quantity * currentPrice;
}

double PortfolioHolding::getUnrealizedGainLoss(double currentPrice) const {
    return getCurrentValue(currentPrice) - basis;
}

double PortfolioHolding::getPercentGainLoss(double currentPrice) const {
    return ((getCurrentValue(currentPrice) - basis) / basis) * 100.0;
}

Portfolio::Portfolio(const std::string& id, const std::string& name,
    double cash, const std::string& owner, const std::string& date)
    : portfolioId(id), portfolioName(name), cashBalance(cash),
    ownerName(owner), createdDate(date) {}

bool Portfolio::buyStock(const std::string& symbol, int quantity, double price, double commission) {
    double totalCost = (quantity * price) + commission;

    if (cashBalance >= totalCost) {
        cashBalance -= totalCost;
        // Check if we already have this stock
        for (auto& holding : holdings) {
            if (holding.getSymbol() == symbol) {
                // Update existing holding (simplified - in reality, we'd need to recalculate average cost)
                return true;
            }
        }
        // Add new holding
        PortfolioHolding newHolding(symbol, quantity, price);
        holdings.push_back(newHolding);
        return true;
    }
    return false;
}

bool Portfolio::sellStock(const std::string& symbol, int quantity, double price, double commission) {
    for (auto& holding : holdings) {
        if (holding.getSymbol() == symbol && holding.getQuantity() >= quantity) {
            double proceeds = (quantity * price) - commission;
            cashBalance += proceeds;
            // In reality, we'd update the holding quantity
            return true;
        }
    }
    return false;
}

void Portfolio::addHolding(const PortfolioHolding& holding) {
    holdings.push_back(holding);
}

double Portfolio::calculateTotalValue(const std::vector<Stock>& stocks) const {
    double total = cashBalance;

    for (const auto& holding : holdings) {
        // Find current price for this stock
        for (const auto& stock : stocks) {
            if (stock.getSymbol() == holding.getSymbol()) {
                total += holding.getCurrentValue(stock.getCurrentPrice());
                break;
            }
        }
    }
    return total;
}

void Portfolio::displayPortfolio(const std::vector<Stock>& stocks) const {
    std::cout << "\n=== Portfolio: " << portfolioName << " ===" << std::endl;
    std::cout << "Cash: $" << std::fixed << std::setprecision(2) << cashBalance << std::endl;
    std::cout << "\nHoldings:\n";

    double totalValue = cashBalance;

    for (const auto& holding : holdings) {
        for (const auto& stock : stocks) {
            if (stock.getSymbol() == holding.getSymbol()) {
                double currentValue = holding.getCurrentValue(stock.getCurrentPrice());
                double gainLoss = holding.getUnrealizedGainLoss(stock.getCurrentPrice());
                double percentGainLoss = holding.getPercentGainLoss(stock.getCurrentPrice());

                std::cout << holding.getSymbol() << " - " << holding.getQuantity() << " shares" << std::endl;
                std::cout << "  Current Value: $" << currentValue
                    << " | Gain/Loss: $" << gainLoss
                    << " (" << percentGainLoss << "%)" << std::endl;

                totalValue += currentValue;
                break;
            }
        }
    }

    std::cout << "\nTotal Portfolio Value: $" << totalValue << std::endl;
}
