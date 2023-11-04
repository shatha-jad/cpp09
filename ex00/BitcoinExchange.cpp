#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : newDate(""), newRate(0) {
    std::cout << "Default constructor called"<<std::endl;
	this->exchangeName = "default";
}

BitcoinExchange::BitcoinExchange(const std::string& name) : exchangeName(name) {

    std::ifstream file("data.csv");
    if (!file.is_open()) {
        std::cerr << formatErrorMessage("Error: file not found.") << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) {
            std::cerr << formatErrorMessage("Error: invalid file format.") << std::endl;
            return;
        }
        std::string date = line.substr(0, commaPos);
        std::string rateStr = line.substr(commaPos + 1);
        double rate = std::strtod(rateStr.c_str(), NULL);
        exchangeRates[date] = rate;
    }
    file.close();
}


BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : exchangeRates(other.exchangeRates), exchangeName(other.exchangeName), newDate(other.newDate), newRate(other.newRate) {
    std::cout << "Copy constructor called for exchange: " << other.exchangeName << std::endl;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        exchangeRates = other.exchangeRates;
        exchangeName = other.exchangeName;
        newDate = other.newDate;
        newRate = other.newRate;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {
    std::cout << "Destructor called for exchange: " << exchangeName << std::endl;
    exchangeRates.clear();
}

std::string BitcoinExchange::getnewDate(const std::string& date) {
	std::map<std::string, double>::iterator it = exchangeRates.lower_bound(date);
    if (it == exchangeRates.end()) {
        return exchangeRates.rbegin()->first;
    }
    if (it->first == date) {
        return date;
    }
    if (it == exchangeRates.begin()) {
        return it->first;
    }
    --it;
    return it->first;
}

bool BitcoinExchange::isValidDate(const std::string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 2009 || year > 2021) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (month == 2 && day > 29) return false;

    newDate = getnewDate(date);
    return true;
}

bool BitcoinExchange::isValidNumber(const std::string& rate) {
    if (rate.empty()) return false;
    char* end;
    double val = std::strtod(rate.c_str(), &end);
    if (end == rate.c_str() || *end != '\0' || val < 0.0 || val > 1000.0) return false;

	newRate = std::strtod(rate.c_str(), nullptr);
    return true;
}

void BitcoinExchange::parseLine(const std::string& date, const std::string& rate) {
    if (!isValidDate(date)) {
        std::cerr << formatErrorMessage("Error: invalid date.") << std::endl;
        return;
    }
    if (!isValidNumber(rate)) {
        std::cerr << formatErrorMessage("Error: invalid value.") << std::endl;
        return;
    }
    std::cout << date << " => " << newRate << " = " << newRate * exchangeRates[newDate] << std::endl;
}

void BitcoinExchange::printExchangeRates(const std::string& file) {
    std::ifstream input(file.c_str());
    if (!input.is_open()) {
        std::cerr << formatErrorMessage("Error: file not found.") << std::endl;
        return;
    }

    std::string line;
    while (getline(input, line)) {
        size_t pipePos = line.find('|');
        if (pipePos == std::string::npos) {
            std::cerr << formatErrorMessage("Error: invalid file format.") << std::endl;
            continue;
        }
        std::string date = line.substr(0, line.find(' '));
        std::string rate = line.substr(line.find('|') + 2);
        parseLine(date, rate);
    }
    input.close();
}

std::string BitcoinExchange::formatErrorMessage(const std::string& message) {
    return RED + message + RESET;
}
