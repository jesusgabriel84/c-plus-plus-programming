#include <iostream>
#include <vector>

int main(void) {
				int n;

std::cin >> n;
std::vector<std::vector<int>> matriz (n,std::vector<int>(n,4));
		/*for( int i = 0; i < n; i++)
		{
			matriz[i].push_back(0);
		}*/

	std::cout << "Printing out a " << n << " x " << n << " matrix:" << std::endl;
	for( int i = 0; i < n; i++)
	{
		for( int j = 0; j < n; j++)
		{
			std::cout << matriz[i][j] << " ";
		}
		std::cout << std::endl;
	}

    return 0;
}
