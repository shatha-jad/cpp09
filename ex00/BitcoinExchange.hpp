#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>

#define RED "\033[0;31m"
#define RESET "\033[0m"

class BitcoinExchange {
private:
    std::map<std::string, double> exchangeRates;
    std::string exchangeName;
    std::string newDate;
    double newRate;

public:
    BitcoinExchange();
    BitcoinExchange(const std::string& name);
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void printExchangeRates(const std::string& file);
    void parseLine(const std::string& date, const std::string& rate);
    std::string getnewDate(const std::string& date); // Declare this function

    bool isValidDate(const std::string& date);
    bool isValidNumber(const std::string& rate);
    static std::string formatErrorMessage(const std::string& message);

};

#endif // BITCOINEXCHANGE_HPP
