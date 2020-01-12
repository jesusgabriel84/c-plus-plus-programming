#include <iostream>
#include <set>
#include <vector>
 
template<class T> 
void ToString();

template<class T> 
std::string ToString(std::string);

template<class iter>
std::string ToString ( iter , iter ) ;

template<template <typename... Args> class Container,typename... Types>
std::string ToString(Container<Types...>& );

///////////////////////////////////////////////////////////////////////////
 
// Specialization for T=double
template<>
void ToString<std::string>() { std::cout << "I am func<string>\n"; }

template<>
std::string ToString<std::string>(std::string s) { return s; }

template<typename iter>
std::string ToString ( iter ptr1, iter ptr2) 
{
	std::cout << std::endl;
	iter it = ptr1;
    for (; it!=ptr2; ++it) 
    	std::cout << *it << std::endl;
    	
    return "FUNCIONA!!!!";
}


template<template <typename... Args> class Container,typename... Types>
std::string ToString(Container<Types...>& c)
{
	std::cout << std::endl;
	typename Container<Types...>::iterator it = c.begin();
	for(; it != c.end(); it++)
		std::cout << *it << std::endl;

	return "FUNCIONA!!!!  FUNCIONA!!!!";
}

int main()
{
	std::set<double> v;
	v.insert(1.23);
	v.insert(4.56);
	v.insert(7.89);
	v.insert(3.14);
	v.insert(44);

	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
 
  ToString<std::string>();
  std::cout << ToString<std::string>("TEST") << std::endl;
  std::cout << ToString(v.begin(), v.end()) << std::endl; 
  std::cout << "ToString(v) = " << ToString(v) << std::endl;
  std::cout << "ToString(vec) = " << ToString(vec) << std::endl;
  //  func<int>(); // Compile time error
                   // No definition for T=int
} // main