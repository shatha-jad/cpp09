#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <cmath>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"
class RPN
{
private:
    std::stack<double> stack; // Stack to store numerical values during RPN evaluation
    std::string input;        // Input string containing the RPN mathematical expression

public:
    RPN();                    // Default constructor
    RPN(std::string input);   // Parameterized constructor to initialize with input expression
    RPN(const RPN &other);    // Copy constructor for creating a copy of another RPN object
    RPN &operator=(const RPN &other); // Assignment operator for assigning one RPN object to another
    void calculate();         // Method to perform the RPN evaluation and display the result
    ~RPN();                   // Destructor to clean up resources when the object goes out of scope
};


#endif