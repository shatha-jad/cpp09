#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <cmath>
#include <cstdlib>

#define RED "\033[0;31m"
#define RESET "\033[0m"

class RPN {
private:
    std::stack<double> stack; // Stack for evaluation of RPN
    std::string expression;       // The RPN expression

public:
    RPN();                               // Default constructor
    RPN(const std::string& exp); // Constructor with RPN expression
    RPN(const RPN& other);               // Copy constructor
    RPN& operator=(const RPN& other);    // Assignment operator
    ~RPN();                              // Destructor

    void evaluate(); // Evaluate the RPN expression
    static std::string formatErrorMessage(const std::string& message);

};


#endif