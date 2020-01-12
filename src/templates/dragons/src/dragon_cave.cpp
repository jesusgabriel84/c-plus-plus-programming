#include "dragon_cave.hpp"

// Define DragonCave's methods here

const std::list<Dragon*>& DragonCave::GetDragons() const
{
	return dragons_;
}

void DragonCave::Accommodate(Dragon* dragon)
{
	try
	{
		this->dragons_.push_back(dragon);
	}
	catch(std::logic_error)
	{
		std::cout << "Pointer is null" << std::endl;
	}
}

void DragonCave::Evict(const std::string& name)
{
	auto it = this->dragons_.begin();
	for(; it != this->dragons_.end(); it++)
	{
		if((*it)->GetName() == name)
		{
			this->dragons_.erase(it);
			break;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const DragonCave& dc)
{
	
	int number_dragons = dc.GetDragons().size();
	int pos = 0;
	os << "DragonCave dwellers:" << std::endl;
	os << std::endl;

	std::list<Dragon*>::const_iterator it = dc.GetDragons().begin();
    for(; it != dc.GetDragons().end(); it++)
    {
    	
	    os << "Dragon named: " << (*it)->GetName() << ", age: " << (*it)->GetAge() << ", size: " << (*it)->GetSize() << std::endl;
		os << "Treasures:" << std::endl;

		auto it2 = (*it)->GetTreasures().begin();
	    for(; it2 != (*it)->GetTreasures().end(); it2++)
	    	os << it2->name << std::endl;
	    
	    pos++;

	    if(pos != number_dragons)
	    	os << std::endl;
    }
    return os;
}