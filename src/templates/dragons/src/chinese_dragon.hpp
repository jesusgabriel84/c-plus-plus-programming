#pragma once

#include "dragon.hpp"

/* TODO: class ChineseDragon
 * ------------
 * Description:
 * A class that describes a chinese dragon. Inherits from Dragon.
 * ------------
 * Functions:
 * 
 * The constructor takes the dragon's name (const std::string&), age (size_t) and 
 * size (size_t) as a parameter and intializes them to the parameter values.
 *
 * Eat: an override of Dragon's Eat.
 *  ChineseDragon's only eat Food whose type is either Herbs or PeopleFood. 
 *  Each eaten Food item increases the dragon's size by one.
 * 
 *  The food that the dragon eats is removed from the parameter food list and
 *  each time the dragon feasts upon something you should print information of
 *  the Food that is being eaten to standard output in the following format:
Chinese dragon ate: <Food's name>\n
 *
 *  The food should be eaten in the order from the list's beginning to end.
 *
 * Hoard: an override of Dragon's Hoard.
 *  ChineseDragons hoard only Treasures whose type is Wisdom. Each hoarded 
 *  treasure is added to the dragon's treasure list and is removed from 
 *  the parameter treasure list.
 * 
 *  Each time the ChineseDragon hoards an item you should print information about the hoarded
 *  item to standard output in the following format:
Chinese dragon received: <Treasure's name>\n
 *
 *  The treasures should be received in the order from the list's beginning to end.
 * ------------
 * Other:
 * Public members of Dragon should be public in ChineseDragon as well.
 */

class ChineseDragon : public Dragon {
public:
	ChineseDragon(const std::string& name, size_t age, size_t size);

	void Eat(std::list<Food>& food);

	void Hoard(std::list<Treasure>& t);
};