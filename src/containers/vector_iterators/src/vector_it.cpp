#include <iostream>
#include <vector>
#include "vector_it.hpp"

// Implement the functions here

std::vector<int> ReadVector()
{
	std::vector<int> numbers;
	int user_input;
	std::cout << "Enter the numbers: " << std::endl;
	while(std::cin >> user_input)
	{
		numbers.push_back(user_input);
	}
	return numbers;

}

// Prints the sum of each pair of adjacent elements: input: 1 2 3 4 !\n, output: 3 5 7\n
void PrintSum1(std::vector<int>& numbers)
{
	for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end()-1; it++) {
		std::cout << (*it + *(it+1)) << " "; 
	}
	std::cout << std::endl;
}

// Prints the sum of the first and last elements, followed by the sum of the second and second-to-last, and so on.
void PrintSum2(std::vector<int>& numbers)
{
	for(unsigned int i = 0; i < numbers.size()/2; i++)
	{
		std::cout << numbers[i] + numbers[numbers.size() - i - 1] << " ";
	}
	std::cout << std::endl;
}

