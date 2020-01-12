#pragma once

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


/* TODO: class Dragon
 * ------------
 * Description:
 * An abstract class that describes a dragon. Each Dragon object has a name (string), 
 * age (size_t), size (size_t) and a list of Treasure objects that the Dragon has
 * hoarded.
 * ------------
 * Functions:
 * 
 * The constructor takes the Dragon's name (const std::string&), age (size_t) and 
 * size (size_t) as a parameter and intializes them to the parameter values.
 *
 * GetName: the function returns a constant reference to the Dragon's name and takes
 * no parameters. This function does not change the state of the Dragon object, i.e.
 * the function should be const.
 *
 * GetAge: the function returns the Dragon's age as a size_t and takes no parameters. 
 * This function does not change the state of the Dragon object, i.e. the function 
 * should be const.
 *
 * GetSize: the function returns the Dragon's size as a size_t and takes no parameters.
 * This function does not change the state of the Dragon object, i.e. the function 
 * should be const.
 *
 * GetTreasures: the function returns a constant reference to the Dragon's treasures list
 * and takes no parameters. This function does not change the state of the Dragon object, 
 * i.e. the function should be const.
 *
 * Eat: a pure virtual function, which returns nothing and takes a reference to a list of
 * Food objects as a parameter.
 *
 * Hoard: a pure virtual function, which returns nothing and takes a reference to a list of
 * Treasure objects as a parameter.
 * ------------
 * Other:
 * The class has the following protected members, which means they are accessible to classes
 * which inherit this class: name (std::string), age (size_t), size (size_t), treasures 
 * (std::list<Treasure>).
 */

class Dragon {
public:
  explicit Dragon(const std::string& name, size_t age, size_t size);

  virtual ~Dragon() {}

  /* GetName
  * Returns the Dragon's name.
  */
  const std::string GetName() const;

  /* GetAge
  * Returns the Dragon's age.
  */
  size_t GetAge() const;

  /* GetSize
  * Returns the Dragon's size.
  */
  size_t GetSize() const;

  void IncreaseSize();

  /* GetTreasures
  * Returns the Dragon's size.
  */
  const std::list<Treasure>& GetTreasures() const;

  void AddTreasure(Treasure t);

  /* Eat
  * Returns nothing (pure virtual function).
  */
  virtual void Eat(std::list<Food>& food) = 0;

  /* Hoard
  * Returns nothing (pure virtual function).
  */
  virtual void Hoard(std::list<Treasure>& t) = 0;

private:
    std::string name_;
    size_t age_;
    size_t size_;
    std::list<Treasure> treasures_;
};


/* TODO: operator <<
 * Description:
 * An overloaded << stream operator for printing Dragons to an parameter ostream.
 * The dragon should be printed to the parameter ostream in the following format:
Dragon named: <Dragon's name>, age: <Dragon's age>, size: <Dragon's size>\n
Treasures:\n
<First Treasure's name in the Dragon's treasures list>\n
<Second Treasure's name in the Dragon's treasures list>\n
...
<Last Treasure's name in the Dragon's treasures list>\n
 * ------------
 * Parameters:
 * - a reference to the output stream where the information is printed (ostream&).
 * - Dragon whose information should be printed (const Dragon&).
 * ------------
 * Returns:
 * A reference to the output stream given as a parameter.
 */

std::ostream& operator<<(std::ostream& os, const Dragon& d);