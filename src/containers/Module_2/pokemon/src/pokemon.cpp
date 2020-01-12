#include "pokemon.hpp"
#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <algorithm>


bool ByName(const std::pair<std::string, size_t>& a, const std::pair<std::string, size_t>& b) {
	if(std::get<0>(a) == std::get<0>(b))
	{
		return std::get<1>(a) < std::get<1>(b);
	}
	else
	{
		return std::get<0>(a) < std::get<0>(b);
	}
}

bool ByID(const std::pair<std::string, size_t>& a, const std::pair<std::string, size_t>& b) {
	if(std::get<1>(a) == std::get<1>(b))
	{
		return std::get<0>(a) < std::get<0>(b);
	}
	else
	{
		return std::get<1>(a) < std::get<1>(b);
	}
}

//PokemonCollection is a list of elements, to access the List we need the operator 'this->'
//in order to access the list of pairs created in the Class
//For more reference check the link:
//https://www.badprog.com/c-tips-n-tricks-using-a-list-of-pairs
PokemonCollection::PokemonCollection(PokemonCollection collection, PokemonCollection collection2)
{

	std::copy(collection.begin(), collection.end(), back_inserter(pokemons_));
	std::copy(collection2.begin(), collection2.end(), back_inserter(pokemons_));
	this->pokemons_.sort();
	this->pokemons_.unique();
}

void PokemonCollection::Add(const std::string& name, size_t id)
{
	auto aPokemon = std::make_pair(name, id);
	pokemons_.push_back(aPokemon);
}

bool PokemonCollection::Remove(const std::string& name, size_t id)
{
	int pos = 0;
	for (std::list<std::pair<std::string, size_t>>::iterator it = pokemons_.begin(); it != pokemons_.end(); it++) 
	{
	    if(it->first == name && it->second == id)
	    {
	    	pokemons_.erase(it);
	    	return true;
	    }
	    pos++;
    }
    return false;
}

void PokemonCollection::Print() const
{
	for (auto it = pokemons_.begin(); it != pokemons_.end(); it++) 
	{
        // it->first is the key part of a pair.
        // it->second is the value part of a pair.
        std::cout << "id: " << it->second << ", name: " << it->first << std::endl;
    }
}

void PokemonCollection::SortByName()
{
	this->pokemons_.sort(ByName);
}

void PokemonCollection::SortById()
{
	this->pokemons_.sort(ByID);
}