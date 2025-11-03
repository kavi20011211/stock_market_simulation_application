#include"../../includes/core/stock.h"
#include<iostream>
#include<iomanip>

Stock::Stock(const std::string& sym, const std::string& compName, double currPrice, double prevClose, double dHigh, double dLow, long vol, double markCap, const std::string& sec, double pRatio, double divYield) :symbol(sym),
companyName(compName), currentPrice(currPrice), previousClose(prevClose), dayHigh(dHigh), dayLow(dLow), volume(vol), marketCap(markCap), sector(sec), peRatio(pRatio), dividendYield(divYield) {}

void Stock::setCurrentPrice(double price) {
	currentPrice = price;
	priceHistory.push_back(price);

	// Update day High/Low prices
	if (price >= dayHigh) dayHigh = price;
	if (price <= dayLow) dayLow = price;
}

void Stock::updatePrice(double price) {
	previousClose = currentPrice;
	currentPrice = price;
	priceHistory.push_back(price);
}

double Stock::getPriceChange()const {
	return currentPrice - previousClose;
}

double Stock::getPercentageChange()const {
	return ((currentPrice - previousClose) / previousClose) * 100.0;
}

void Stock::displayInfo()const {
	double change = getPriceChange();
	double percentage = getPercentageChange();

	std::cout << std::fixed << std::setprecision(2);
	std::cout << symbol << "-" << companyName << std::endl;
	std::cout << "Price: $" << currentPrice << "|Change: " << (change >= 0 ? "+" : "") << change << "(" << (percentage >= 0 ? "+" : "") << percentage << "%)" << std::endl;
	std::cout << "Volume: " << volume << "|Market Cap: $" << marketCap << std::endl;

}
