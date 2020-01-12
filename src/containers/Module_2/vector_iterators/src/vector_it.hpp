#ifndef AALTO_ELEC_CPP_VECTOR_IT
#define AALTO_ELEC_CPP_VECTOR_IT

#include <vector>

// Reads a set of integers into a vector. Stops when user gives something other than an integer. 
std::vector<int> ReadVector();

// Prints the sum of each pair of adjacent elements: input: 1 2 3 4 !\n, output: 3 5 7\n
void PrintSum1(std::vector<int>& );

// Prints the sum of the first and last elements, followed by the sum of the second and second-to-last, and so on.
void PrintSum2(std::vector<int>& );

#endif
