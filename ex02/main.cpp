#include "PmergeMe.hpp"
#include <cctype> // for std::isdigit
#include <cstdlib> // for std::atoi

bool is_positive_integer(const char *str)
{
    // Check for empty string
    if (*str == '\0') {
        return false;
    }

    // Check for positive integer (no sign allowed)
    for (; *str; str++) {
        if (!std::isdigit(*str)) {
            return false;
        }
    }
    return true;
}

bool are_all_positive_integers(char **argv)
{
    for (int i = 1; argv[i]; i++) {
        if (!is_positive_integer(argv[i])) {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv)
{
    if (argc >= 3 && are_all_positive_integers(argv))
    {
        PmergeMe sort(argv);
    }
    else
    {
        std::cerr << "Error Invalid Arguments." << std::endl;
        return 1;
    }
    return 0;
}
