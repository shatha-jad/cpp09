#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() :newDate(""), newRate(0)
{
	// Constructor: Initialize member variables
	std::cout<<"Defult constrcuter is called"<<std::endl;
	this->exchangeName = "default";
}

BitcoinExchange::~BitcoinExchange()
{
	// Destructor: Clear exchangeRates map
	std::cout<<"Detrcuter is called"<<std::endl;
	this->exchangeRates.clear();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	// Copy constructor: Assign values from other object
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		// Assignment operator: Assign values from other object
		this->exchangeName = other.exchangeName;
		this->exchangeRates = other.exchangeRates;
	}
	return *this;
}

BitcoinExchange::BitcoinExchange(std::string exchangeName)
{
	// Constructor with exchangeName parameter
	this->exchangeName = exchangeName;
	std::ifstream input("data.csv");//Creates an input file stream and opens the file named "data.csv".
	if (!input.is_open())//Checks if the file was successfully opened
	{
		// File not found
		std::cout << RED << "Error: file not found." << RESET << std::endl;
		return;
	}
	std::string line;//to hold each line read from the file.
	while (std::getline(input, line))//Reads each line from the file until the end.
	{
		size_t pos = line.find(',');//Finds the position of the comma delimiter in the line.
		if (pos == line.npos)//Checks if the delimiter was not found.
		{
			// Invalid file format
			std::cout << RED << "Error: invalid file format." << RESET << std::endl;
			return;
		}
		// Extract date and rate from the line
		std::string date = line.substr(0, line.find(','));//Extracts the date substring from the line.
		std::string rate = line.substr(line.find(',') + 1);//Extracts the rate substring from the line.
		// Convert rate to double and store in exchangeRates map
		this->exchangeRates[date] = std::atof(rate.c_str());
	}
	input.close();
}

std::string BitcoinExchange::getnewDate(std::string date)
{
	// Get the nearest date from exchangeRates map that is less than or equal to the given date
	std::map<std::string, double>::iterator it = this->exchangeRates.lower_bound(date);
	if (it == this->exchangeRates.end())
		return exchangeRates.rbegin()->first;
	if (it->first == date)
		return date;
	if (it == this->exchangeRates.begin())
		return it->first;
	else
		it--;
	return it->first;
}

bool BitcoinExchange::isValidDate(std::string date)
{
	// Check if the date has a valid format and falls within a specific range

	// Check if the date length is not equal to 10 or if the 5th and 8th characters are not hyphens
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
	{
		return false;
	}

	// Check if the year is not within the range 2009-2021
	if (std::atoi(date.substr(0, 4).c_str()) < 2009 || std::atoi(date.substr(0, 4).c_str()) > 2021)
		return false;

	// Check if the month is not within the range 1-12
	if (std::atoi(date.substr(5, 2).c_str()) < 1 || std::atoi(date.substr(5, 2).c_str()) > 12)
		return false;

	// Check if the day is not within the range 1-31
	if (std::atoi(date.substr(8, 2).c_str()) < 1 || std::atoi(date.substr(8, 2).c_str()) > 31)
		return false;

	// Check if it's February and the day is greater than 29
	if (std::atoi(date.substr(5, 2).c_str()) == 2 && std::atoi(date.substr(8, 2).c_str()) > 29)
		return false;

	// If the date is valid, set the newDate variable using the getnewDate function
	this->newDate = getnewDate(date);
	return true;
}

bool BitcoinExchange::isValidNumber(std::string rate)
{
	// Check if the rate string represents a valid number

	// Check if the rate string is empty
	if (rate.length() == 0)
		return false;

	// Check if the rate string does not contain a decimal point
	if (rate.find(".") == rate.npos)
	{
		// If the rate does not contain a decimal point, check if it is a valid integer
		// Check if the rate is less than 0 or greater than 1000
		if (std::atoi(rate.c_str()) < 0 || std::atoi(rate.c_str()) > 1000)
			return false;
	}
	else
	{
		// If the rate contains a decimal point, check if it is a valid floating-point number
		// Check if the rate is less than 0 or greater than 1000
		if (std::atof(rate.c_str()) < 0 || std::atof(rate.c_str()) > 1000)
			return false;
	}

	// If the rate is valid, convert the rate string to a double and assign it to the newRate variable
	this->newRate = std::atof(rate.c_str());
	return true;
}


void BitcoinExchange::parseLine(std::string date, std::string rate)
{
	if (date.find('-') == date.npos)
	{
		// Invalid file format
		std::cout << RED << "Error: invalid file format." << RESET << std::endl;
		return;
	}
	if (isValidDate(date) == false)
	{
		// Invalid date
		std::cout << RED << "Error: invalid date." << RESET << std::endl;
		return;
	}
	if (isValidNumber(rate) == false)
	{
		// Invalid value
		std::cout << RED << "Error: invalid value" << RESET << std::endl;
		return;
	}
	// Print the date, rate, and calculated value
	std::cout << date << " => " << this->newRate << " = " << this->newRate * this->exchangeRates[this->newDate] << std::endl;
}
void BitcoinExchange::printExchangeRates(std::string file)
{
	// Open the input file stream
	std::ifstream input(file.c_str());
	if (!input.is_open())
	{
		// File not found
		std::cout << RED << "Error: file not found." << RESET << std::endl;
		return;
	}
	
	std::string line;
	while (std::getline(input, line))
	{
		// Read each line from the input file

		// Find the position of the '|' delimiter in the line
		size_t pos = line.find('|');
		if (pos == line.npos)
		{
			// Invalid file format
			std::cout << RED << "Error: invalid file format." << RESET << std::endl;
			continue;
		}
		
		// Extract date and rate from the line
		std::string date = line.substr(0, line.find(' '));
		std::string rate = line.substr(line.find('|') + 1);
		
		// Parse and process the line using the parseLine function
		this->parseLine(date, rate);
	}
}
