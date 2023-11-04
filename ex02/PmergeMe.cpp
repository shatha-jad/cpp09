#include "PmergeMe.hpp" // Include the header file for this class

// Constructor - Default constructor
PmergeMe::PmergeMe()
{
}

// Constructor that takes a char array as input
PmergeMe::PmergeMe(char **argv)
{
    this->_k = 5; // Initialize k to 5
    this->fillAndPrint(argv); // Fill vectors from command line arguments and print them
    this->sortContainers(); // Sort vectors using different algorithms
}

// Copy constructor
PmergeMe::PmergeMe(const PmergeMe &object)
{
    *this = object; // Copy constructor (assignment)
}

// Assignment operator overload
PmergeMe &PmergeMe::operator=(const PmergeMe &rhs)
{
    if (this != &rhs)
    { 
        // Copy data from 'rhs' to 'this' if needed
        // You can add code here for deep copying if necessary
    }
    return (*this); // Return the current object
}

// Destructor
PmergeMe::~PmergeMe()
{
}

// Function to print the content of the vector
void PmergeMe::printVec()
{
    std::vector<int>::iterator it;

    for (it = this->_vec.begin(); it != this->_vec.end(); ++it)
    {
        std::cout << " " << *it; // Print each element of the vector
    }
    std::cout << std::endl; // Print a newline
}

// Function to fill vectors from command line arguments and print them
void PmergeMe::fillAndPrint(char **argv)
{
    int i = 1;
    std::cout << "Before:";

    // Loop through command line arguments
    while (argv[i])
    {
        this->_vec.push_back(atoi(argv[i])); // Convert char array to integer and add to vector
        this->_deque.push_back(atoi(argv[i])); // Convert char array to integer and add to deque
        std::cout << " " << argv[i]; // Print the current argument
        i++; // Move to the next argument
    }
    std::cout << std::endl; // Print a newline
}

// Recursive function to perform insertion sort on a vector
void PmergeMe::vecInsertion(int begin, int end)
{
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

// Recursive function to perform insertion sort on a deque
void PmergeMe::dequeInsertion(int begin, int end)
{
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

// Function to merge two subarrays of a deque
void PmergeMe::mergeDeque(int begin, int mid, int end)
{
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

// Function to merge two subarrays of a vector
void PmergeMe::mergeVec(int begin, int mid, int end)
{
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

// Recursive function to perform merge sort on a vector
void PmergeMe::vecSort(int begin, int end)
{
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

// Recursive function to perform merge sort on a deque
void PmergeMe::dequeSort(int begin, int end)
{
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

// Function to measure and print the time taken to sort vectors
void PmergeMe::sortContainers()
{
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
