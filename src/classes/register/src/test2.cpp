#include "register.hpp"
#include "vehicle.hpp"
#include "car.hpp"
#include "boat.hpp"
#include "aircraft.hpp"
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <ostream>
#include <iostream>
#include <fstream>





int main()
{
std::string s = "C;YUU-123;Teemu Teekkari;Volkswagen Polo;800;1";
//std::string s = "gggggg";
std::string delimiter = ";";
std::list<std::string> vec;

size_t pos = 0;
std::string token;
while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    vec.push_back(token);
    s.erase(0, pos + delimiter.length());
}

vec.push_back(s);

std::cout << "NOW PRINTING VECTOR" << std::endl;

/*if(vec[0] == "C" && vec.size() == 6)
{
for(unsigned int i = 0; i < vec.size(); i++)
	std::cout << vec[i] << std::endl;
}*/
auto it = vec.begin();

//for(auto it = vec.begin(); it != vec.end(); it++)
it++;
it++;
	std::cout << *(it) << std::endl;
std::cout << vec.size() << std::endl;
/*std::cout << stod(vec[4]) << std::endl;
std::cout << vec[2] << std::endl;*/




return 0;
}