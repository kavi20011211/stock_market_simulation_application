#pragma once
#include<vector>
#include<string>
#include"../core/stock.h"
#include"../core/portfolio.h"

class DataLoader {
private:
	static std::vector<std::vector<std::string>>readCSV(const std::string& fileName);

public:
	static std::vector<Stock> loadMarketData(const std::string& fileName);
	static std::vector<Portfolio> loadPortfolioData(const std::string& portfolioFile,const std::string& holdingsFile);
};
