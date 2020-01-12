#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include <gcheck.h>
#include <redirectors.h>
#include "../src/pokemon.hpp"

const std::list<std::pair<std::string, size_t>> pokemons = {std::pair<std::string, size_t>("Pikachu", 25), std::pair<std::string, size_t>("Raticate", 20), std::pair<std::string, size_t>("Raticate", 20), std::pair<std::string, size_t>("Bulbasaur", 1), std::pair<std::string, size_t>("Pikachu", 25), std::pair<std::string, size_t>("Diglett", 50)};

PREREQ_TEST(Pokemon, Add, 1, 0) {
    PokemonCollection collection({std::pair<std::string, size_t>("Pikachu", 25), std::pair<std::string, size_t>("Bulbasaur", 1)});
    collection.Add("Meowth", 52);
    collection.Add("Diglett", 50);
    
    auto it = collection.begin();
    std::advance(it, 2);
    EXPECT_EQ("Meowth", (*it).first);
    EXPECT_EQ(52, (*it).second);
    std::advance(it, 1);
    EXPECT_EQ("Diglett", (*it).first);
    EXPECT_EQ(50, (*it).second);
}

PREREQ_TEST(Pokemon, Print, 1, 0) {
    {
        PokemonCollection collection(pokemons);
        
        gcheck::StdoutCapturer tout;
        collection.Print();
        std::string Print_out = tout.str();
        tout.Restore();

        std::string correct = 
            "id: 25, name: Pikachu\n"
            "id: 20, name: Raticate\n"
            "id: 20, name: Raticate\n"
            "id: 1, name: Bulbasaur\n"
            "id: 25, name: Pikachu\n"
            "id: 50, name: Diglett\n";
        
        EXPECT_EQ(correct, Print_out);
    }
    {
        PokemonCollection collection({std::pair<std::string, size_t>("Raticate", 20), std::pair<std::string, size_t>("Bulbasaur", 1), std::pair<std::string, size_t>("Pikachu", 25)});
        
        gcheck::StdoutCapturer tout;
        collection.Print();
        std::string Print_out = tout.str();
        tout.Restore();

        std::string correct = 
            "id: 20, name: Raticate\n"
            "id: 1, name: Bulbasaur\n"
            "id: 25, name: Pikachu\n";
        
        EXPECT_EQ(correct, Print_out);
    }
}

TEST(Pokemon, Remove) {
    PokemonCollection collection(pokemons);

    // Use this list to append removed items to verify whether they are actually deleted.
    PokemonCollection removed_items;
    
    size_t initial_size = collection.size();
 
    EXPECT_TRUE(collection.Remove("Raticate", 20));
    removed_items.Add("Raticate", 20); 
    
    EXPECT_EQ(collection.size(), initial_size - removed_items.size());
    EXPECT_FALSE(collection.Remove("Oddish", 43));
    
    EXPECT_EQ(collection.size(), initial_size - removed_items.size());
    EXPECT_TRUE(collection.Remove("Raticate", 20));
    
    removed_items.Add("Raticate", 20); 
    EXPECT_EQ(collection.size(), initial_size - removed_items.size());
    EXPECT_FALSE(collection.Remove("Raticate", 20));
    
    EXPECT_EQ(collection.size(), initial_size - removed_items.size());
    EXPECT_TRUE(collection.Remove("Bulbasaur", 1));
    
    removed_items.Add("Bulbasaur", 1);
    EXPECT_EQ(collection.size(), initial_size - removed_items.size());

    for(auto idx = removed_items.begin(); idx != removed_items.end(); idx++) {
        auto it = std::find(collection.begin(), collection.end(), *idx);
        EXPECT_EQ(it, collection.end()); 
    } 
}

PREREQ_TEST(Pokemon, SortById, 1, 1) {
    PokemonCollection collection(pokemons);
    collection.Add("Meowth", 52);
    collection.Add("Arcanine", 59);
    
    collection.SortById();
    
    gcheck::StdoutCapturer tout;
    collection.Print();
    std::string sorted_by_id = tout.str();
    tout.Restore();

    std::string correct =
        "id: 1, name: Bulbasaur\n"
        "id: 20, name: Raticate\n"
        "id: 20, name: Raticate\n"
        "id: 25, name: Pikachu\n"
        "id: 25, name: Pikachu\n"
        "id: 50, name: Diglett\n"
        "id: 52, name: Meowth\n"
        "id: 59, name: Arcanine\n";
        
    EXPECT_EQ(correct, sorted_by_id);
}

PREREQ_TEST(Pokemon, SortByName, 1, 1) {
    PokemonCollection collection(pokemons);
    
    collection.Add("Meowth", 52);
    collection.Add("Arcanine", 59);
    
    collection.SortByName();
    
    gcheck::StdoutCapturer tout;
    collection.Print();
    std::string sorted_by_name = tout.str();
    tout.Restore();

    std::string correct =
        "id: 59, name: Arcanine\n"
        "id: 1, name: Bulbasaur\n"
        "id: 50, name: Diglett\n"
        "id: 52, name: Meowth\n"
        "id: 25, name: Pikachu\n"
        "id: 25, name: Pikachu\n"
        "id: 20, name: Raticate\n"
        "id: 20, name: Raticate\n";
    
    EXPECT_EQ(correct, sorted_by_name);
}

TEST_(Pokemon, merge_constructor, 2) {
    PokemonCollection collection1(pokemons);
    PokemonCollection collection2({std::pair<std::string, size_t>("Venomoth", 49), std::pair<std::string, size_t>("Oddish", 43)});
    
    collection1.Add("Meowth", 52);
    collection2.Add("Arcanine", 59);
    collection2.Add("Raticate", 20);
    
    PokemonCollection merged(collection1, collection2);
    merged.SortById();
    
    gcheck::StdoutCapturer tout;
    merged.Print();
    std::string Print_merged = tout.str();
    tout.Restore();
    
    std::string correct =
        "id: 1, name: Bulbasaur\n"
        "id: 20, name: Raticate\n"
        "id: 25, name: Pikachu\n"
        "id: 43, name: Oddish\n"
        "id: 49, name: Venomoth\n"
        "id: 50, name: Diglett\n"
        "id: 52, name: Meowth\n"
        "id: 59, name: Arcanine\n";
    
    EXPECT_EQ(correct, Print_merged);
}
