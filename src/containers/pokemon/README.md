**Objective:** Practice use of algorithms together with a list
  container.

Pokemon is an information entity with a name (string) and an
identifier. Therefore the **pair** type can be used to store one such
element. This exercise operates on lists that consist of (string,
size_t) pairs. You should review the function interfaces and respective 
descriptions there.

You will need to implement the following methods for the *PokemonCollection* class:

  * **Add(name, id)**: adds a new Pokemon with
    given name/id pair at the end of list *pokemon_*.

  * **Remove(name, id)**: removes the first Pokemon with matching name and id.

  * **Print**: prints the Pokemons.
    See the example in *pokemon.hpp* for the required print format.

  * **SortByName**: sorts the Pokemon collection by their name. 
    If two names are equal, their order is determined by their ids.

  * **SortById**: sorts the Pokemon collection by their id. 
    If two ids are equal, their order is determined by their names.

And the following constructor:

  * **PokemonCollection(c1, c2)**: merges the contents of the two
    collections. Duplicate elements must be removed.


**Compile and run:**
```bash
#In the folder src/containers/pokemon
make
cd src
./main
```
