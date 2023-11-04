
#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _k(0) {}

PmergeMe::PmergeMe(char **argv) : _k(5) {
    fillAndPrint(argv);
    sortContainers();
}

PmergeMe::PmergeMe(const PmergeMe &object) : _k(object._k), _vec(object._vec), _deque(object._deque) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs) {
    if (this != &rhs) {
        _k = rhs._k;
        _vec = rhs._vec;
        _deque = rhs._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}


void PmergeMe::fillAndPrint(char **argv) {
 int i = 1;
    std::cout << "Before:";

    // Loop through command line arguments
    while (argv[i])
    {
        this->_vec.push_back(atoi(argv[i])); // Convert char array to integer and add to vector
        this->_deque.push_back(atoi(argv[i])); // Convert char array to integer and add to deque
        std::cout << " " << argv[i]; 
        i++; 
    }
    std::cout << std::endl; 
}

void PmergeMe::printVec() {
std::vector<int>::iterator it;

    for (it = this->_vec.begin(); it != this->_vec.end(); ++it)
    {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
}

void PmergeMe::vecInsertion(int begin, int end) {
 for (int i = begin; i < end; i++)
    {
        int tmp = this->_vec[i + 1];
        int j = i + 1;

        // Insertion sort
        while (j > begin && this->_vec[j - 1] > tmp)
        {
            this->_vec[j] = this->_vec[j - 1];
            j--;
        }
        this->_vec[j] = tmp;
    }
}

void PmergeMe::dequeInsertion(int begin, int end) {
    for (int i = begin; i < end; i++)
    {
        int tmp = this->_deque[i + 1];
        int j = i + 1;

        // Insertion sort
        while (j > begin && this->_deque[j - 1] > tmp)
        {
            this->_deque[j] = this->_deque[j - 1];
            j--;
        }
        this->_deque[j] = tmp;
    }
}

void PmergeMe::mergeDeque(int begin, int mid, int end) {
    int n1 = mid - begin + 1;
    int n2 = end - mid;
    int rightIdx = 0;
    int leftIdx = 0;

    std::deque<int> left(this->_deque.begin() + begin, this->_deque.begin() + mid + 1);
    std::deque<int> right(this->_deque.begin() + mid + 1, this->_deque.begin() + end + 1);

    for (int i = begin; i <= end; i++)
    {
        if (rightIdx == n2)
        {
            this->_deque[i] = left[leftIdx];
            leftIdx++;
        }
        else if (leftIdx == n1)
        {
            this->_deque[i] = right[rightIdx];
            rightIdx++;
        }
        else if (right[rightIdx] > left[leftIdx])
        {
            this->_deque[i] = left[leftIdx];
            leftIdx++;
        }
        else
        {
            this->_deque[i] = right[rightIdx];
            rightIdx++;
        }
    }
}

void PmergeMe::mergeVec(int begin, int mid, int end) {
    int n1 = mid - begin + 1;
    int n2 = end - mid;
    int rightIdx = 0;
    int leftIdx = 0;

    std::vector<int> left(this->_vec.begin() + begin, this->_vec.begin() + mid + 1);
    std::vector<int> right(this->_vec.begin() + mid + 1, this->_vec.begin() + end + 1);

    for (int i = begin; i <= end; i++)
    {
        if (rightIdx == n2)
        {
            this->_vec[i] = left[leftIdx];
            leftIdx++;
        }
        else if (leftIdx == n1)
        {
            this->_vec[i] = right[rightIdx];
            rightIdx++;
        }
        else if (right[rightIdx] > left[leftIdx])
        {
            this->_vec[i] = left[leftIdx];
            leftIdx++;
        }
        else
        {
            this->_vec[i] = right[rightIdx];
            rightIdx++;
        }
    }
}

void PmergeMe::vecSort(int begin, int end) {
    if (end - begin > this->_k)
    {
        int mid = (begin + end) / 2;
        vecSort(begin, mid); // Recursively sort the left half
        vecSort(mid + 1, end); // Recursively sort the right half
        this->mergeVec(begin, mid, end); // Merge the sorted halves
    }
    else
        this->vecInsertion(begin, end); // Use insertion sort for small subarrays
}


void PmergeMe::dequeSort(int begin, int end) {
     if (end - begin > this->_k)
    {
        int mid = (begin + end) / 2;
        dequeSort(begin, mid); // Recursively sort the left half
        dequeSort(mid + 1, end); // Recursively sort the right half
        this->mergeDeque(begin, mid, end); // Merge the sorted halves
    }
    else
        this->dequeInsertion(begin, end); // Use insertion sort for small subarrays
}

void PmergeMe::sortContainers() {
    clock_t start, finish;
    double vecTime, dequeTime;

    std::cout << "After: ";

    // Measure time taken to sort a vector
    start = clock();
    this->vecSort(0, this->_vec.size() - 1);
    finish = clock();
    vecTime = ((double)(finish - start)) / CLOCKS_PER_SEC;

    // Measure time taken to sort a deque
    start = clock();
    dequeSort(0, this->_deque.size() - 1);
    finish = clock();
    dequeTime = ((double)(finish - start)) / CLOCKS_PER_SEC;

    printVec(); // Print the sorted vector
    std::cout << "Time to process a range of " << this->_vec.size() << " elements with std::vector: " << std::fixed << vecTime << " seconds" << std::endl;
    std::cout << "Time to process a range of " << this->_deque.size() << " elements with std::deque: " << std::fixed << dequeTime << " seconds" << std::endl;
}