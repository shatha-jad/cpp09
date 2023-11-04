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
	this->exchangeName = exchangeName;
	// create an input file stream object named input and open a file named "data.csv".
	//The purpose of opening the file is to read exchange rate data from the "data.csv"
	//The data in the file is expected to be in CSV (Comma-Separated Values) format, where each line contains a date and its corresponding exchange rate.
	std::ifstream input("data.csv");
	if (!input.is_open())
	{
		// File not found
		std::cout << "Error: file not found."<<std::endl;
		return ;
	}
	std::string line;//to hold each line read from the file.
	while (std::getline(input, line))//read each line from the input file and store it in the string Line, the function stops reading when it encounters a newline character ('\n') or the end of the file.
	{
		size_t position = line.find(',');//locate the position of the first occurrence of the character ',' (comma) in the string line
		if (position == line.npos)//Checks if the delimiter was not found.
		{
			std::cout<<"Error: invalid file format. "<<std::endl;
			return ;
		}
		std::string date = line.substr(0, line.find(','));//Extracts the date substring from the line.
		std::string rate = line.substr(line.find(',')  + 1);//Extracts the rate substring from the line.
		this->exchangeRates[date] = std::atof(rate.c_str());// Convert rate to double and store in exchangeRates map, std::map when you need an associative container with sorted keys,
	}
	input.close();//close the file
}

// Function to get the nearest date from the exchangeRates map that is less than or equal to the given date
std::string BitcoinExchange::getnewDate(std::string date)
{
    // Find the iterator pointing to the first element in the map that is not less than the given date.
    // If there is no such element, it points to exchangeRates.end().
    std::map<std::string, double>::iterator it = this->exchangeRates.lower_bound(date);//lower_bound(date) returns an iterator to the first element in the map whose key is greater than or equal to the given date

    // If the iterator is pointing to the end of the map, it means all dates in the map are greater than the given date.
    // In this case, return the date of the last entry in the map.
	//Given date is greater than all the dates in the exchangeRates map, the function will return the last date available in the map
	//it->first refers to the key of the element that the iterator it is currently pointing to in the exchangeRates map.
    if (it == this->exchangeRates.end())
        return exchangeRates.rbegin()->first;

    // If the iterator is pointing to a date that is equal to the given date, we found an exact match.
    // Return the same date.
    if (it->first == date)
        return date;

    // If the iterator is pointing to the beginning of the map, it means all dates in the map are smaller than the given date.
    // In this case, return the date of the first entry in the map.
    if (it == this->exchangeRates.begin())
        return it->first;
    else
    {
        // The iterator is pointing to a date greater than the given date.
        // Decrement the iterator to get the previous entry, which is the nearest date that is less than the given date.
        it--;
        return it->first;
    }
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
		std::cout << "Error: file not found." <<std::endl;
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
