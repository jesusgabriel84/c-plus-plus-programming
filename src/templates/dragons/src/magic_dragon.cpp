#include "magic_dragon.hpp"

// Define MagicDragon's methods here

MagicDragon::MagicDragon(const std::string& name, size_t age, size_t size)
	: Dragon(name,age,size) { }

void MagicDragon::Eat(std::list<Food>& food)
{
	std::list<Food>::const_iterator it = food.begin();
	while(it != food.end())
	{
		if(it->type == Herbs)
		{
			std::cout << "Magic dragon ate: " << it->name << std::endl;
			this->IncreaseSize();
			//food.erase(it);
		}
		std::advance(it,1);
	}
	food.remove_if([](Food n){ return (n.type == Herbs); });
}

void MagicDragon::Hoard(std::list<Treasure>& treasure)
{
	std::list<Treasure>::const_iterator it = treasure.begin();
	while(it != treasure.end())
	{
		if(it->type == Potions)
		{
			this->AddTreasure(*it);
			std::cout << "Magic dragon received: " << it->name << std::endl;
			//t.erase(it);
		}
		std::advance(it,1);
	}
	treasure.remove_if([](Treasure n){ return (n.type == Potions); });
}