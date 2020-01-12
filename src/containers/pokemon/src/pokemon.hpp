#ifndef AALTO_ELEC_CPP_POKEMON
#define AALTO_ELEC_CPP_POKEMON

#include <iostream>
#include <string>
#include <list>
#include <utility>

class PokemonCollection {
public:

    /* constructor
    * initializes the collection to empty
    * You don't need to define this in the cpp file as the definition is given here
    */
    PokemonCollection() {}
    
    /* constructor
    * initializes the collection to by copying the parameter
    * You don't need to define this in the cpp file as the definition is given here
    */
    PokemonCollection(const std::list<std::pair<std::string, size_t>>& pokemons) : pokemons_(pokemons) {}

    /* constuctor
    * initializes the collection to contain all the pokemons from the two 
    * collections given as parameters and removes all duplicates, takes the following parameters:
    *  - a PokemonCollection
    *  - a PokemonCollection
    * Hint: sorting at some point would probably help
    * 
    * All the other functions must get full points before this is tested.
    */
   PokemonCollection(PokemonCollection collection, PokemonCollection collection2);
    
    /* Add:
    * adds a pokemon to the end of the collection, takes the following parameters:
    *  - the pokemon's name, 
    *  - the pokemon's id, 
    */ 
    void Add(const std::string& name, size_t id);
    
    /* Remove:
    * removes a pokemon to the collection, takes the following parameters:
    *  - the pokemon's name, 
    *  - the pokemon's id
    * returns true if the pokemon was found and removed, false otherwise
    */ 
    bool Remove(const std::string& name, size_t id);
    
    /* Print:
    * Prints the collection to the standard output stream. 
    * The format of the print should be as below: 
id: <id>, name: <name>\n
id: <id>, name: <name>\n
    */ 
    void Print() const;
    
    /* SortByName:
    * sorts the collection by name.
    * If two names are equal, their order is determined by their ids
    * Hint: A list only has bidirectional iterators, which might narrow your sorting solutions down a bit.
    * However a valid and easy solution does exist!
    */ 
    void SortByName();
    
    /* SortById:
    * sorts the collection by id
    * If two ids are equal, their order is determined by their names
    * Hint: A list only has bidirectional iterators, which might narrow your sorting solutions down a bit.
    * However a valid and easy solution does exist!
    */ 
    void SortById();
    
    /* These are for the tests to use. Do not modify */
    auto begin() { return pokemons_.begin(); }
    auto end() { return pokemons_.end(); }
    auto size() { return pokemons_.size(); }
private:
    std::list<std::pair<std::string, size_t>> pokemons_;
};

#endif
