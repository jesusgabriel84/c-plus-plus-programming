#include "dragon.hpp"
#include <string>
#include <list>

Dragon::Dragon(const std::string& name, size_t age, size_t size)
	: name_(name), age_(age), size_(size) {}

const std::string Dragon::GetName() const
{
	return name_;
}

size_t Dragon::GetAge() const
{
	return age_;
}

size_t Dragon::GetSize() const
{
	return size_;
}

const std::list<Treasure>& Dragon::GetTreasures() const
{
	return treasures_;
}

void Dragon::AddTreasure(Treasure t)
{
	try
	{
		this->treasures_.push_back(t);
	}
	catch(std::logic_error)
	{
		std::cout << "Pointer is null" << std::endl;
	}
}

void Dragon::IncreaseSize()
{
	size_++;
}

std::ostream& operator<<(std::ostream& os, const Dragon& d)
{

	os << "Dragon named: " << d.GetName() << ", age: " << d.GetAge() << ", size: " << d.GetSize() << std::endl;
	os << "Treasures:" << std::endl;

	auto it = d.GetTreasures().begin();
    for(; it != d.GetTreasures().end(); it++)
    	os << it->name << std::endl;

    return os;
}
