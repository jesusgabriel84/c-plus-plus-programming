#include "aviary.hpp"
#include <string>
#include <ostream>
#include <vector>
#include <iostream>

void Aviary::Add(Bird* bird)
{
	try
	{
		this->birds_.push_back(bird);
	}
	catch(std::logic_error)
	{
		std::cout << "Pointer is null" << std::endl;
	}
}

std::ostream& Aviary::SpeakAll(std::ostream& os)
{
	for(auto it : this->birds_)
	{
		it->Speak(os);
	}

	return os;
}

size_t Aviary::Size() const
{
	return this->birds_.size();
}

Bird* Aviary::operator[](size_t i)
{

	try
	{
		std::list<Bird*>::iterator it = this->birds_.begin();
		for(unsigned int j = 0; j < i; j++)
			it++;
		return *it;
	}
	catch(std::out_of_range)
	{
		std::cout << "Index out of range" << std::endl;
	}
}

const Bird* Aviary::operator[](size_t i) const
{
	try
	{
		std::list<Bird*>::const_iterator it = this->birds_.begin();
		for(unsigned int j = 0; j < i; j++)
			it++;
		return *it;
	}
	catch(std::out_of_range)
	{
		std::cout << "Index out of range" << std::endl;
	}
}

