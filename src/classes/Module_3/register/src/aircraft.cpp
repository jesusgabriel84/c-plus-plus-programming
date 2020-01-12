#include "aircraft.hpp"
#include <vector>
//TODO: implement Aircraft's members

Aircraft::Aircraft(std::string register_number, std::string owner, std::string model, double wingspan, unsigned int cruise_speed)
	: Vehicle(register_number,owner) 
	{
		model_ = model;
		wingspan_ = wingspan;
		cruise_speed_ = cruise_speed;
	}

void Aircraft::Write(std::ostream& stream)
{
	stream << "A;" << GetRegisterNumber() << ";" << GetOwner() << ";" << model_ << ";" << wingspan_ << ";" << cruise_speed_ << std::endl;
}

void Aircraft::Print()
{
	std::cout << "A;" << GetRegisterNumber() << ";" << GetOwner() << ";" << model_ << ";" << wingspan_ << ";" << cruise_speed_ << std::endl;
}

Aircraft* Aircraft::Read(std::istream& stream)
{
	//A;RU-123;Russian Federation;MiG-21;80.8;1600

	std::string s;
	std::vector<std::string> serialized_str;
	std::getline(stream, s); //Remember to use this command to read line into string, 
							//otherwhise if you use stream>>s it will not convert to string properly
							//because the blank spaces is considered as a new input stream, for this
							// reason, we need first to convert the stream into string.
	std::string delimiter = ";";

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
	    token = s.substr(0, pos);
	    serialized_str.push_back(token);
	    s.erase(0, pos + delimiter.length());
	}
	serialized_str.push_back(s);

	if(serialized_str[0] == "A")
	{
		try
		{
			Aircraft* new_aircraft = new Aircraft(serialized_str[1], serialized_str[2], serialized_str[3], stod(serialized_str[4]), stoi(serialized_str[5]));
			//Aircraft* new_aircraft = new Aircraft("test","test2","test4",80.8,2000);
			return new_aircraft;
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