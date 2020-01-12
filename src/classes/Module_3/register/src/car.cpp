#include "car.hpp"
#include <vector>
#include <list>
//TODO: implement Car's members

Car::Car(std::string register_number, std::string owner, std::string maker, unsigned int range, bool inspection)
	: Vehicle(register_number,owner), maker_ (maker), range_(range), inspection_(inspection)
	{ 
		/*maker_ = maker; 
	   	range_ = range;
	   	inspection_ = inspection;*/
	}

void Car::Write(std::ostream& stream)
{
	int insp = 0;
	if(inspection_ == true)
		insp = 1;	
	stream << "C;" << this->GetRegisterNumber() << ";" << this->GetOwner() << ";" << maker_ << ";" << range_ << ";" << insp << std::endl;
}

void Car::Print()
{
	int insp = 0;
	if(inspection_ == true)
		insp = 1;
	std::cout << "C;" << this->GetRegisterNumber() << ";" << this->GetOwner() << ";" << maker_ << ";" << range_ << ";" << insp << std::endl;
}

Car* Car::Read(std::istream& stream)
{
	//C;EES-321;Nikola;Tesla;600;0

	std::string s,var1,var2,var3,var4,var5,var6;
	int counter = 1;
	std::getline(stream, s);
	std::string delimiter = ";";
	size_t pos = 0;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		if(counter == 1)
			var1 = s.substr(0, pos);
		if(counter == 2)
			var2 = s.substr(0, pos);
		if(counter == 3)
			var3 = s.substr(0, pos);
		if(counter == 4)
			var4 = s.substr(0, pos);
		if(counter == 5)
			var5 = s.substr(0, pos);
	    s.erase(0, pos + delimiter.length());
	    counter++;
	}
	var6 = s;

	if(var1 == "C" )
	{
		bool insp = false;
		if(stoi(var6) == 1)
			insp = true;
		Car* new_car = new Car(var2,var3,var4,stoi(var5),insp);
		return new_car;		
	}
	else
	{
		return NULL;
	}	
}