#pragma once

#include <iostream>
#include <sstream>
//#include <string>

/* As an introduction to templates you will write and specialize a template function 
 * for formatting the contents of a container (string, vector, list, ...) into a string, 
 * assuming that the elements of the container are printable (with the << operator). 
 *
 * This function is called ToString and it returns the container contents in the following format 
 * (assuming a container of strings with three elements: "foo", "bar" and "baz"): 
{ foo, bar, baz }
 * (assuming a container of ints with three elements: 10, -5 and 4): 
{ 10, -5, 4 }
 * When passed a std::string, the function should, instead of returning a list of characters { f, o, o, b, a, r }, 
 * just put double quotes around the string:
"foobar"
 * Additionally, overload the function with a version that, instead of a container, 
 * takes begin and end iterators, and formats the contents in the format specified above for containers 
 * (no special handling for string iterators).
 *
 * Notes:
 * You may assume that std::strings have their regular interface. 
 * For other containers, only use the iterator interface (begin and end functions).
 * Your functions must work with at least bidirectional iterators. Note that such 
 * iterators do not have operators + and - (but they do have ++ and --).
 * If you'd really want to provide printing support for containers, 
 * you should write operator<< for them instead of a ToString function.
 * This would allow printing containers that contain other containers, etc.
 */

//First declare the template skeletons and then declare the functions!!!
//Need to create the templates for every class
template<class T> 
std::string ToString(std::string);

template<class T> 
std::string ToString(std::basic_string<char>);

template<class iter>
std::string ToString ( iter , iter ) ;

template<template <typename... Args> class Container,typename... Types>
std::string ToString(Container<Types...>& );

template<template <typename... Args> class Container>
std::string ToString(Container<std::string>& );

template<class T>
std::string ToString(std::string::iterator, std::string::iterator );

template<template <typename... Args> class Container>
std::string ToString(Container<char>& );


///////////////////////////////////////////////////////////////////////////
 
// Specialization for T=string
template<class T>
std::string ToString(std::string s) 
{ 
	std::string correct = "\"";
	correct += s;
	correct += "\"";
	return correct; 
}

template<>
std::string ToString(std::string::iterator ptr1, std::string::iterator ptr2)
{
	std::string::iterator it = ptr1;
	std::string correct = "{ ";
	correct += (*it);
	it++;
    for (; it!=ptr2; it++) 
    {
    	correct += ", ";
    	correct += (*it);
    }

    correct += " }";

    return correct;
}


template<typename iter>
std::string ToString ( iter ptr1, iter ptr2) 
{

	iter it = ptr1;
	std::string correct = "{ ";
	correct += std::to_string(*it);
	it++;
    for (; it!=ptr2; it++) 
    {
    	correct += ", ";
    	correct += std::to_string(*it);
    }

    correct += " }";

    return correct;
}


template<template <typename... Args> class Container,typename... Types>
std::string ToString(Container<Types...>& c)
{

	typename Container<Types...>::iterator it = c.begin();
	std::string correct = "{ ";
	correct += std::to_string(*it);
	it++;
	for(; it != c.end(); it++)
	{
    	correct += ", ";
    	correct += std::to_string(*it);
    }

    correct += " }";

    return correct;
}


template<template <typename... Args> class Container>
std::string ToString(Container<std::string>& c)
{

	typename Container<std::string>::iterator it = c.begin();
	std::string correct = "{ ";
	correct += (*it);
	it++;
	for(; it != c.end(); it++)
	{
    	correct += ", ";
    	correct += (*it);
    }

    correct += " }";

    return correct;
}

//Special function for the case when the parameter is just a simple string (container of char)
template<template <typename... Args> class Container>
std::string ToString(Container<char>& s)
{ 
	std::string correct = "\"";
	correct += s;
	correct += "\"";
	return correct; 
}

