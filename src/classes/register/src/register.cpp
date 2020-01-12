#include "register.hpp"
#include "car.hpp"
#include "boat.hpp"
#include "aircraft.hpp"
#include <string>
#include <ostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
//TODO: implement Register's members

void Register::Add(Vehicle* v)
{
	try
	{
		this->vehicles_.push_back(v);
	}
	catch(std::logic_error)
	{
		std::cout << "Pointer is null" << std::endl;
	}
}

void Register::Save(const std::string& filename) const
{
	std::ofstream os(filename);
	/*std::vector<Vehicle*>::iterator it = this->vehicles_.begin();
	for(; it != this->vehicles_.end(); it++)
		*it.Write(os);*/
	for(auto it : this->vehicles_)
	{
		it->Write(os);
	}
	os.close();
}

bool Register::ReadLine(std::istream& stream)
{
	
	//Be careful when reading from stream, in this case we need to create a separate stream for each vechicle
	std::string s;
	std::getline(stream, s);
	std::istringstream iss_car(s);
	std::istringstream iss_boat(s);
	std::istringstream iss_air(s);

	Car* new_car = Car::Read(iss_car);
	Boat* new_boat = Boat::Read(iss_boat);
	Aircraft* new_air = Aircraft::Read(iss_air);

		if(new_car != NULL) 
		{ 
			Register::Add(new_car);
			return true;
		}

		if(new_boat != NULL)
		{
			Register::Add(new_boat);
			return true;
		}
		if(new_air != NULL)
		{
			Register::Add(new_air);
			return true;
		}

		return false;
}

int Register::Load(const std::string& filename)
{
	std::string line;
	int counter = 0;
	std::ifstream istr(filename);
	if (istr.rdstate() & (istr.failbit | istr.badbit)) {
	    // output error to stderr stream
	    return -1;
	} 
	else 
	{
		while (!istr.eof()) 
		{
			std::getline(istr, line);
			std::istringstream iss(line);
			if(Register::ReadLine(iss))
				counter++;
			line.clear();
		}
	}
	return counter;
}

void Register::Print()
{
	for(auto it : this->vehicles_)
	{
		it->Print();
	}
}

size_t Register::Size() const
{
	return this->vehicles_.size();
}
