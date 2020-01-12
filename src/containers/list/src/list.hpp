#ifndef AALTO_ELEC_CPP_LIST
#define AALTO_ELEC_CPP_LIST

#include <iostream>
#include <list>
#include <string>

/** Read all lines from the stream into the list. Newline characters are not
 * stored in the list. Returns the stream. **/
std::istream& GetLines(std::istream& is, std::list<std::string>& list);

/** Print the list, with a newline after each entry. **/
void Print(const std::list<std::string>& list);

/** Sort the list and remove all duplicate entries. **/
void SortAndUnique(std::list<std::string>& list);

#endif
