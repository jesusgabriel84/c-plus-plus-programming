#include <sstream>
#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <vector>

int main()
{

	std::string poly_input, mon;
	unsigned int i = 0;
	std::vector<std::string> mon_v;
	std::vector<int> numbers;


	poly_input = "20x4+15x3-10x2+5x1+0x0";
	//poly_input = "4x2+2x1+7x0";

	std::cout << poly_input << std::endl;

	while(i < poly_input.size())
	{
		while(poly_input[i] != 'x' && i < poly_input.size())
		{
			mon.push_back(poly_input[i]);
			i++;
		}

		mon_v.push_back(mon);
		mon.clear();
		i++;

	}
	
	unsigned int ii = 0;
	numbers.push_back(stoi(mon_v[0]));
	for(unsigned int j = 1; j<mon_v.size()-1; j++)
	{

			while(mon_v[j][ii] != '+' && mon_v[j][ii] != '-')
			{
				mon.push_back(mon_v[j][ii]);
				ii++;
			}
			numbers.push_back(stoi(mon));
			mon.clear();

			while(ii < mon_v[j].size())
			{
				mon.push_back(mon_v[j][ii]);
				ii++;
			}
			numbers.push_back(stoi(mon));
			mon.clear();

			ii = 0;
		
	}

	numbers.push_back(stoi(mon_v[mon_v.size()-1]));

	for(unsigned int j = 0; j < numbers.size(); j++)
	{
		std::cout << numbers[j] << std::endl;
	}

	/*for(unsigned int kk = 0; kk < mon_v.size(); kk++)
	{
		std::cout << mon_v[kk] << std::endl;
	}*/

	std::cout << "SIZE: " << numbers.size() << std::endl;
	std::cout<< "End" << std::endl;

	for(unsigned int iii = 0; iii < numbers.size(); iii+=2)
	{
		if(numbers[iii] != 0)
		std::cout << "Coeff: " << numbers[iii] << " | Exp: " << numbers[iii+1] << std::endl;
	}
    return 0;
}