#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <deque>
#include <time.h>

class PmergeMe
{
    private:
		int					_k;
		std::vector<int>	_vec;
		std::deque<int>		_deque;

        void    fillAndPrint(char **argv);
		void	sortContainers();

		void	vecSort(int begin, int end);
		void	mergeVec(int begin, int mid, int end);
		void	vecInsertion(int begin, int end);
		void	printVec();

		void	dequeSort(int begin, int end);
		void	mergeDeque(int begin, int mid, int end);
		void	dequeInsertion(int begin, int end);

        
    public:
        PmergeMe();
        PmergeMe(char **argv);
        PmergeMe(const PmergeMe &object);
        PmergeMe &operator=(const PmergeMe &rhs);
        ~PmergeMe();
};

#endif