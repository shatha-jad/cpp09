#include "BitcoinExchange.hpp"


int	main(int ac, char **av)
{
	if (ac != 2)
	{
		BitcoinExchange bitcoinexchange;
		std::cerr << bitcoinexchange.formatErrorMessage("Error: could not open file.") << std::endl;
		return 1;
	}
	std::string exchangeName = av[1];
	BitcoinExchange exchange(exchangeName);
	exchange.printExchangeRates(exchangeName);

}



// int main(int argc, char** argv)
// {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: " << argv[0] << " <exchange name>" << std::endl;
// 		return 1;
// 	}
// 	std::string exchangeName = argv[1];
// 	BitcoinExchange exchange(exchangeName);
// 	exchange.printExchangeRates(exchangeName);
// }

