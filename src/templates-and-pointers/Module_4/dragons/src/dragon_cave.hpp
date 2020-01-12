#pragma once

#include "dragon.hpp"
#include <iostream>
#include <string>
#include <ostream>
#include <list>

/* TODO: class DragonCave
 * Description:
 * ------------
 * The DragonCave class is a sort of storage class for Dragons. The class
 * stores pointers of Dragon objects in a list. The class allows basic
 * manipulation of the Dragon pointer list through the functions described
 * below.
 *
 * Functions:
 * -----------
 * The DragonCave class has a parameterless constructor that default constructs
 * the members i.e. uses the parameterless constructor to initialize them.
 *
 * The destructor of the DragonCave class deletes all the Dragons in the
 * the DragonCave's Dragon* list.
 *
 * GetDragons: the function returns a const reference to the DragonCave's
 * list of Dragon pointers. The function takes no parameters and does not change 
 * the DragonCave's state, i.e. the function should be const.
 *
 * Accommodate: takes a Dragon pointer as a parameter and adds it to the end of
 * the DragonCave's Dragon pointer list. The function returns nothing.
 * 
 * Evict: takes a Dragon's name as a const string reference as a parameter.
 * Tries to find a dragon with a matching name from the DragonCaves Dragon pointer
 * list. Erases the first Dragon pointer with a matching name from the list. If
 * there is no Dragon with a matching name in the list, the function does nothing.
 * Note that the function only erases the pointer from the list, but DOES NOT delete
 * the Dragon object. The function returns nothing.
 *
 * Other:
 * -----------
 * The class obviously has a list of Dragon pointers as a private member. This class is not
 * copyable (also means not assignable), so copy and assignment operations for this
 * class should be prevented.
 */


class DragonCave {
public:
    DragonCave() {}

    ~DragonCave() {
    for(auto it : dragons_) 
        delete it;
    }

    const std::list<Dragon*>& GetDragons() const;

    void Accommodate(Dragon* dragon);
    
    void Evict(const std::string& name);
    
private:
    // TODO: the needed variables
    std::list<Dragon*> dragons_;
    //copy and assignment operations are prevented
    DragonCave(const DragonCave&) = delete;
    DragonCave& operator=(const DragonCave&);
};



/* TODO: operator <<
 * ------------
 * Description:
 * An overloaded << stream operator for printing DragonCaves to parameter ostreams.
 * The DragonCave should be printed to the parameter ostream in the following format:
DragonCave dwellers:\n
\n
<First Dragon in the dragons list>\n
<Second Dragon in the dragons list>\n
...
<Last Dragon in the dragons list>
 *
 * NOTE: The dragons in the dragon list are printed in the same format as the overloaded
 *       << stream operator for Dragons prints them. Also note that there is an additional
 *       end line character after each dragon except for the last one.
 * ------------
 * Parameters:
 * - the output stream to which the information is printed (ostream).
 * - the DragonCave whose information should be printed (const DragonCave&).
 * ------------
 * Returns:
 * The parameter output stream.
 */
std::ostream& operator<<(std::ostream& os, const DragonCave& dc);

