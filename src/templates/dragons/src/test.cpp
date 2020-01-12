#include <string>
#include <list>
#include <iostream>

/* Enumeration types for the different treasures */
enum TreasureType {
  Jewellery,
  Wisdom,
  Potions
};

/* Implementation of Treasure */
struct Treasure {
  TreasureType type;
  std::string name;
};

/* Enumeration types for the different foods */
enum FoodType {
  PeopleFood,
  People,
  Herbs
};

/* Implementation of Food */
struct Food {
  FoodType type;
  std::string name;
};

int main()
{

  std::list<Food> lista;
  Food f1 = {People,"Manzana"};
  Food f2 = {PeopleFood,"mandarina"};
  Food f3 = {Herbs,"naranja"};
  lista.push_back(f1);
  lista.push_back(f2);
  lista.push_back(f3);
  std::cout << f1.type << std::endl;
  
  /*std::list<Food>::iterator it = lista.begin();

  for(; it != lista.end(); it++)
  {
    if(it->name == "mandarina")
      lista.erase(it);
  }*/

  std::list<Food>::iterator it = lista.begin();

  for(; it != lista.end(); it++)
  {
    lista.remove_if(it->name == "mandarina");
    std::cout << it->name << std::endl;
  }

 //lista.remove_if([](Food n){ return n.name == "mandarina"; });


  std::list<Food>::iterator it2 = lista.begin();

  for(; it2 != lista.end(); it2++)
  {

    std::cout << it2->name << std::endl;
  }

  return 0;
}