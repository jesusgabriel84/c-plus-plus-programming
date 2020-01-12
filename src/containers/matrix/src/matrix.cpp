#include <iostream>
#include <vector>
#include "matrix.hpp"

// Implement the functions here
// Remember to use auto and ranged for-loops when they can be used!


// Function reads input from user to n x n matrix
Matrix ReadMatrix(int n)
{
	//Initialize the object 'matrix' with 'n' elements of type vector<int>(n)
	Matrix matrix(n,std::vector<int>(n));

	for( int i = 0; i < n; i++)
	{
		for( int j = 0; j < n; j++)
		{
			std::cin >> matrix[i][j];
		}
	}
	return matrix;
}

// Function rotates n x n matrix 90 degrees clockwise
Matrix Rotate90Deg(Matrix &m )
{
	
	int n = m[0].size();
	Matrix new_matrix(n,std::vector<int>(n));


	for( int i = 0; i < n; i++)
	{
		for( int j = 0; j < n; j++)
		{
			new_matrix[j][i] = m[n-1-i][j];

		}
	}

	return new_matrix;
}

/* Function prints n x n matrix to standard output:
 * e.g. when n = 3 and the matrix' rows are all 1,2,3:
Printing out a 3 x 3 matrix:\n
1 2 3 \n
1 2 3 \n
1 2 3 \n
 */
void Print(Matrix & m)
{
	int n = m[0].size();
	std::cout << "Printing out a " << n << " x " << n << " matrix:" << std::endl;
	for( int i = 0; i < n; i++)
	{
		for( int j = 0; j < n; j++)
		{
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}


  
}