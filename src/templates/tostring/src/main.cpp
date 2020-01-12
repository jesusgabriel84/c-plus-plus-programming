#include "to_string.hpp"
#include <iostream>
#include <set>

int main() {
	std::string s = "25Yb7kXfTMUXSmp^]2S^uXpVP";
	std::cout << "ToString(s) = " << ToString<std::string>(s) << std::endl;
	std::cout << "ToString(s) = " << ToString(s) << std::endl;
	std::cout << "ToString(s.begin(), s.end()) = " << ToString(s.begin(), s.end()) << std::endl;
	std::set<double> v;
	v.insert(1.23);
	v.insert(4.56);
	v.insert(7.89);
	std::cout << "ToString(v) = " << ToString(v) << std::endl;
	std::cout << "ToString(v.begin(), v.end()) = " << ToString(v.begin(), v.end()) << std::endl;
}

