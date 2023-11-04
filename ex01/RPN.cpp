#include "RPN.hpp"

RPN::RPN() : input("")
{
}

RPN::RPN(std::string input) : input(input)
{
}

RPN::RPN(const RPN &other)
{
	*this = other;
}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		input = other.input;
		stack = other.stack;
	}
	return (*this);
}

RPN::~RPN()
{
}

void RPN::calculate()
{
    // If the input is empty, there's nothing to evaluate
    if (this->input.empty())
        return;

    // Create an input stream to read tokens from the input string
	//It behaves like the standard input stream (std::cin), but instead of reading input from the keyboard, it reads from a string.
	//we can tokenize the input string and process each token one by one.
    std::istringstream string_stream(input);
    std::string input_str;

    // Process each token in the input string
	//It iterates over the input stream string_stream, extracting each token (number or operator) from the input string one by one, until there are no more tokens to read.
    while (string_stream >> input_str)
    {
        // Check if the token is an operator
        if (input_str == "+" || input_str == "-" || input_str == "*" || input_str == "/" || input_str == "%")
        {
            // If there are less than 2 values in the stack, there are not enough operands for the operator
            if (stack.size() < 2)
            {
                std::cout << RED << "Error: Not enough values" << RESET << std::endl;
                return;
            }

            // Pop the top two values from the stack
            double a = stack.top();//This line retrieves the value of the top element from the stack and assigns it to the variable a
            stack.pop();//emoves the top element from the stack after it has been extracted and assigned to the variable a
            double b = stack.top();//ine retrieves the new top element from the stack, which is now the first operand needed to perform the arithmetic operation.
            stack.pop();

            // Perform the corresponding operation based on the operator and push the result back to the stack
            if (input_str == "+")
                stack.push(b + a);
            else if (input_str == "-")
                stack.push(b - a);
            else if (input_str == "*")
                stack.push(b * a);
            else if (input_str == "/" && b != 0)
                stack.push(b / a);
            else if (input_str == "/" && b == 0)
            {
                std::cout << RED << "Error: Division by zero" << RESET << std::endl;
                return;
            }
        }
        else if (std::isdigit(input_str[0]))//check if the current token (input_str) is a digit. 
        {
            // If the token is a digit, convert it to a double and push it onto the stack
            double number;
            if (std::atof(input_str.c_str()) < 0 || std::atof(input_str.c_str()) > 9)
            {
                std::cout << RED << "Error: Invalid value" << RESET << std::endl;
                return;
            }
            number = std::atof(input_str.c_str());//converts the C-style string represented by input_str to a double value and assigns it to the variable number.
            stack.push(number);//push it onto the stack
        }
        else
        {
            // Invalid token encountered
            std::cout << RED << "Error: Invalid value" << RESET << std::endl;
            return;
        }
    }

    // After processing all tokens, check if there's only one value left in the stack
    if (stack.size() > 1)
    {
        std::cout << RED << "Error: Too many values" << RESET << std::endl;
        return;
    }

    // Print the final result
    std::cout << stack.top() << std::endl;
}
