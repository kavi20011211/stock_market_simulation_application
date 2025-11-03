#pragma once
#include<string>
#include<vector>

class Stock {
private:
	std::string symbol;
	std::string companyName;
	double currentPrice;
	double previousClose;
	double dayHigh;
	double dayLow;
	long volume;
	double marketCap;
	std::string sector;
	double peRatio;
	double dividendYield;
	std::vector<double>priceHistory;

public:
	Stock(const std::string& sym, const std::string& compName,
		double currPrice, double prevClose, double dHigh, double dLow,
		long vol, double markCap, const std::string& sec,
		double pRatio, double divYield);

	//getters
	std::string getSymbol() const { return symbol; }
	std::string getCompanyName() const { return companyName; }
	double getCurrentPrice() const { return currentPrice; }

	//setters
	void setCurrentPrice(double price);
	void updatePrice(double newPrice);

	//utility methods
	double getPriceChange()const;
	double getPercentageChange()const;
	void displayInfo()const;
};
