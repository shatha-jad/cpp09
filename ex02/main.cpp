#include "PmergeMe.hpp"

bool	is_digit(char **av)
{
	int	i = 1;
	while (av[i])
	{
		int	j = 0;
		while (av[i][j])
		{
			if (isdigit(av[i][j]) == 0)
				return false;
			j++;
		}
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	if ((ac >= 3 && ac <= 3000) && is_digit(av))
	{
		PmergeMe
	}
	else
	{
		std::cout << "Error Invalid Arguments." << std::endl;
		std::cout << "Usage: ./PmergeMe 3 5 9 7 4 ..." << std::endl;
		return (1);
	}


}





bool	is_digit(char **argv)
{
	int i = 1;

	while (argv[i])
	{
		int j = 0;
		while (argv[i][j])
		{
			if (isdigit(argv[i][j]) == 0)
				return (false);
			j++;
		}
		i++;
	}
	return(true);
}

int main(int argc, char **argv)
{
    if ((argc >= 3 && argc < 3001) && is_digit(argv))
    {
		PmergeMe sort(argv);
		return (0);
    }
    else
    {
        std::cout << "Error Invalid Arguments." << std::endl;
        std::cout << "Usage: ./PmergeMe 3 5 9 7 4 ..." << std::endl;
		return (1);
    }
    return (0);
}

