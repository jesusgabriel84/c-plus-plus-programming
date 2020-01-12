#include "list.hpp"
#include <iostream>
#include <list>
#include <string>

// Implement the functions here

/** Read all lines from the stream into the list. Newline characters are not
 * stored in the list. Returns the stream. **/
std::istream& GetLines(std::istream& is, std::list<std::string>& list)
{
	std::string input;
	while(std::getline(is, input))
	{
		list.push_back(input);
	}
	return is;
}

/** Print the list, with a newline after each entry. **/
void Print(const std::list<std::string>& list)
{
	//Remeber to use 'iterator' or 'const_iterator' depending on how the argument of the function is referenced
	//In this case the object 'list' is passed with the '&', for this reason we need to use
	//'const_iterator' to iterate the list.
	for (std::list<std::string>::const_iterator it = list.begin(); it != list.end(); it++) 
	{
		std::cout << *it << std::endl; 
	}
}

/** Sort the list and remove all duplicate entries. **/
void SortAndUnique(std::list<std::string>& list)
{
	list.sort();
	list.unique();
}