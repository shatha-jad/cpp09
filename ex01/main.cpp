#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./rpn <expression>" << std::endl;
		return (1);
	}
	RPN rpn(argv[1]);
	rpn.calculate();
	return (0);
}