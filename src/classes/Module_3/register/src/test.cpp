#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <ostream>
#include <iostream>
#include <fstream>

int main()
{
	std::string input_car, temp;
	std::vector<std::string> serialized_str;
	input_car = "A;MAG 1C;Paul Daniels;Bentley;650.3;0";
	unsigned int i = 0;

	//C;<register number>;<owner>;<maker>;<range>;<inspection>
	
	while(i < input_car.size())
	{
		while(input_car[i] != ';' && i < input_car.size())
		{
			temp.push_back(input_car[i]);
			i++;
		}

		serialized_str.push_back(temp);
		temp.clear();
		i++;

	}


		bool insp;
		if (serialized_str[5] == "1")
		{
			insp = true;
		}
		else
		{
			insp = false;
		}
	

for(unsigned int i = 0; i < serialized_str.size(); i++)
std::cout << "String: " << serialized_str[i] << std::endl;

try
{
std::cout << stod(serialized_str[20]) << std::endl;
}
catch(std::invalid_argument)
		{
			std::cout << "WRONG!!" << std::endl;
		}


return 0;

}