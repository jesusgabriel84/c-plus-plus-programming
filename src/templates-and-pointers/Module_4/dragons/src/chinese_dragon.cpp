#include "chinese_dragon.hpp"

// Define ChineseDragon's methods here

ChineseDragon::ChineseDragon(const std::string& name, size_t age, size_t size)
	: Dragon(name,age,size) { }

void ChineseDragon::Eat(std::list<Food>& food)
{
	std::list<Food>::const_iterator it = food.begin();
	while(it != food.end())
	{
		if(it->type == PeopleFood || it->type == Herbs)
		{
			std::cout << "Chinese dragon ate: " << it->name << std::endl;
			this->IncreaseSize();
			//food.erase(it);
		}
		std::advance(it,1);
	}
	food.remove_if([](Food n){ return (n.type == PeopleFood || n.type == Herbs); });
}


void ChineseDragon::Hoard(std::list<Treasure>& treasure)
{
	std::list<Treasure>::const_iterator it = treasure.begin();
	while(it != treasure.end())
	{
		if(it->type == Wisdom)
		{
			this->AddTreasure(*it);
			std::cout << "Chinese dragon received: " << it->name << std::endl;
			//t.erase(it);
		}
		std::advance(it,1);
	}
	treasure.remove_if([](Treasure n){ return (n.type == Wisdom); });
}