#include "boat.hpp"
#include <vector>
//TODO: implement Boat's members

Boat::Boat(std::string register_number, std::string owner, std::string name, double draft, double power)
	: Vehicle(register_number,owner) 
	{ 
		name_ = name; 
		draft_ = draft; 
		power_ = power;
	}
   
void Boat::Write(std::ostream& stream)
{
	stream << "B;" << GetRegisterNumber() << ";" << GetOwner() << ";" << name_ << ";" << draft_ << ";" << power_ << std::endl;
}

void Boat::Print()
{
	std::cout << "B;" << GetRegisterNumber() << ";" << GetOwner() << ";" << name_ << ";" << draft_ << ";" << power_ << std::endl;
}

Boat* Boat::Read(std::istream& stream)
{
	//B;FI123;Pekka Purjehtija;Mariella;1.8;0

	std::string s;
	std::vector<std::string> serialized_str;
	std::getline(stream, s);
	std::string delimiter = ";";

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
	    token = s.substr(0, pos);
	    serialized_str.push_back(token);
	    s.erase(0, pos + delimiter.length());
	}
	serialized_str.push_back(s);

	
	if(serialized_str[0] == "B")
	{
		try
		{
			Boat* new_boat = new Boat(serialized_str[1], serialized_str[2], serialized_str[3], stod(serialized_str[4]), stod(serialized_str[5]));
			//Boat* new_boat = new Boat("test","test2","test3",1.8,0);
			return new_boat;
		}
		catch(std::invalid_argument)
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}

}