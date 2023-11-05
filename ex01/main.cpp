#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		RPN rpn;
		// std::cout << "Usage: ./rpn <expression>" << std::endl;
		std::cerr << rpn.formatErrorMessage("Error: Invalid Input") << std::endl;
		return (1);
	}
	RPN rpn(argv[1]);
	rpn.evaluate();
	return (0);
}