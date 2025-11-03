#include "../../includes/utils/csvReader.h"
#include<fstream>
#include<sstream>
#include<iostream>

std::vector<std::vector<std::string>> DataLoader::readCSV(const std::string& fileName) {
    std::vector<std::vector<std::string>> data;

    std::ifstream FILE(fileName);
    if (!FILE.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return data;
    }

    std::string line;
    // Skip header
    std::getline(FILE, line);

    while (std::getline(FILE, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            // Trim whitespace
            cell.erase(0, cell.find_first_not_of(" \t\r\n"));
            cell.erase(cell.find_last_not_of(" \t\r\n") + 1);
            row.push_back(cell);
        }

        if (!row.empty()) {
            data.push_back(row);
        }
    }

    FILE.close();
    //std::cout << "Read " << data.size() << " rows from " << fileName << std::endl;
    return data;
}

std::vector<Stock> DataLoader::loadMarketData(const std::string& fileName) {
    std::vector<Stock> stocks;
    auto data = readCSV(fileName);

    for (const auto& row : data) {
        if (row.size() >= 11) {  // MarketData has 11 columns
            try {
                Stock stock(
                    row[0],              // symbol
                    row[1],              // company_name
                    std::stod(row[2]),   // current_price
                    std::stod(row[3]),   // previous_close
                    std::stod(row[4]),   // day_high
                    std::stod(row[5]),   // day_low
                    std::stol(row[6]),   // volume
                    std::stod(row[7]),   // market_cap
                    row[8],              // sector
                    std::stod(row[9]),   // pe_ratio
                    std::stod(row[10])   // dividend_yield
                );
                stocks.push_back(stock);
            }
            catch (const std::exception& e) {
                std::cerr << "Error parsing stock row: " << e.what() << std::endl;
            }
        }
        else {
            std::cerr << "Row has only " << row.size() << " columns, expected 11" << std::endl;
        }
    }

    //std::cout << "Loaded " << stocks.size() << " stocks from " << fileName << std::endl;
    return stocks;
}

std::vector<Portfolio> DataLoader::loadPortfolioData(const std::string& portfolioFile,
    const std::string& holdingsFile) {
    std::vector<Portfolio> portfolios;

    // Load portfolios - Portfolio.csv has 6 columns
    auto portfolioData = readCSV(portfolioFile);
    for (const auto& row : portfolioData) {
        if (row.size() >= 6) {  // Changed from 5 to 6
            try {
                Portfolio portfolio(
                    row[0],              // portfolio_id
                    row[1],              // portfolio_name
                    std::stod(row[2]),   // cash_balance
                    row[3],              // owner_name
                    row[4]               // created_date
                    // row[5] is total_value - add if your constructor needs it
                );
                portfolios.push_back(portfolio);
            }
            catch (const std::exception& e) {
                std::cerr << "Error parsing portfolio row: " << e.what() << std::endl;
            }
        }
        else {
            std::cerr << "Portfolio row has only " << row.size() << " columns, expected 6" << std::endl;
        }
    }

    // Load holdings - Holdings.csv has 7 columns
    auto holdingsData = readCSV(holdingsFile);
    for (const auto& row : holdingsData) {
        if (row.size() >= 7) {  // Changed from 5 to 7
            try {
                std::string portfolioId = row[0];   // portfolio_id
                std::string symbol = row[1];         // symbol
                int quantity = std::stoi(row[2]);    // quantity
                double averageCost = std::stod(row[3]); // average_cost
                // row[4] is basis
                // row[5] is current_value
                // row[6] is unrealized_gain_loss

                // Find matching portfolio
                bool found = false;
                for (auto& portfolio : portfolios) {
                    if (portfolio.getPortfolioId() == portfolioId) {
                        PortfolioHolding holding(symbol, quantity, averageCost);
                        portfolio.addHolding(holding);
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    std::cerr << "Portfolio " << portfolioId << " not found for holding " << symbol << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Error parsing holding row: " << e.what() << std::endl;
            }
        }
        else {
            std::cerr << "Holding row has only " << row.size() << " columns, expected 7" << std::endl;
        }
    }

    //std::cout << "Loaded " << portfolios.size() << " portfolios" << std::endl;
    return portfolios;
}