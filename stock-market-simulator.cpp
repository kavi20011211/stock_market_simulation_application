// main.cpp
#include <iostream>
#include <vector>
#include <memory>
#include "includes/core/stock.h"
#include "includes/core/portfolio.h"
#include "includes/utils/csvReader.h"
#include <filesystem>


class StockMarketSimulator {
private:
    std::vector<Stock> stocks;
    std::vector<Portfolio> portfolios;
    std::string dataDirectory;

public:
    StockMarketSimulator(const std::string& dataDir) : dataDirectory(dataDir) {}

    void initialize() {
        // Load all data
        stocks = DataLoader::loadMarketData(dataDirectory + "/marketdata.txt");
        portfolios = DataLoader::loadPortfolioData(
            dataDirectory + "/portfolio.txt",
            dataDirectory + "/holdings.txt"
        );

        std::cout << "Stock Market Simulator Initialized!" << std::endl;
        std::cout << "Loaded " << stocks.size() << " stocks and "
            << portfolios.size() << " portfolios" << std::endl;
    }

    void displayMainMenu() {
        std::cout << "\n=== STOCK MARKET SIMULATOR ===" << std::endl;
        std::cout << "1. View All Stocks" << std::endl;
        std::cout << "2. View Portfolios" << std::endl;
        std::cout << "3. Buy Stock" << std::endl;
        std::cout << "4. Sell Stock" << std::endl;
        std::cout << "5. View Stock Details" << std::endl;
        std::cout << "6. Simulate Price Changes" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Choose an option: ";
    }

    void viewAllStocks() {
        std::cout << "\n=== ALL STOCKS ===" << std::endl;
        for (const auto& stock : stocks) {
            stock.displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }

    void viewPortfolios() {
        for (const auto& portfolio : portfolios) {
            portfolio.displayPortfolio(stocks);
        }
    }

    void run() {
        initialize();

        int choice;
        do {
            displayMainMenu();
            std::cin >> choice;

            switch (choice) {
            case 1:
                viewAllStocks();
                break;
            case 2:
                viewPortfolios();
                break;
            case 3:
                // Implement buy stock
                std::cout << "Buy stock functionality coming soon..." << std::endl;
                break;
            case 4:
                // Implement sell stock
                std::cout << "Sell stock functionality coming soon..." << std::endl;
                break;
            case 5:
                // Implement stock details
                std::cout << "Stock details functionality coming soon..." << std::endl;
                break;
            case 6:
                // Implement price simulation
                std::cout << "Price simulation functionality coming soon..." << std::endl;
                break;
            case 7:
                std::cout << "Thank you for using Stock Market Simulator!" << std::endl;
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
            }
        } while (choice != 7);
    }
};

int main() {
    StockMarketSimulator simulator("../../../src/data");
    simulator.run();
    return 0;
}