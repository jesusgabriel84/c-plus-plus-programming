
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <ostream>
#include <iostream>
#include <fstream>

class Vehicle {
public:
    /* constructor
     * Initializes the corresponing members from the parameters.
    */
    explicit Vehicle(std::string register_number, std::string owner)
    	: register_number_(register_number), owner_(owner) {}
    
    virtual ~Vehicle() {};
    
    /* GetRegisterNumber
     * Returns the register number.
    */
    std::string GetRegisterNumber() const
    {
    	return register_number_;
    }
    
    /* GetOwner
     * Returns the owner.
    */
    std::string GetOwner() const
    {
    	return owner_;
    }
    
    
private:
    std::string register_number_;
    std::string owner_;
};




int main()
{
std::string s;
std::istringstream iss("C;YUU-123;Teemu Teekkari;Volkswagen Polo;800;1");
std::string var1, var2, var3, var4, var5, var6;
//iss >> s;
std::getline(iss, s);
int counter = 1;
size_t pos = 0;
//std::string s = "gggggg";
std::string delimiter = ";";

while ((pos = s.find(delimiter)) != std::string::npos) {
	    
		if(counter == 1)
			var1 = s.substr(0, pos);
		if(counter == 2)
			var2 = s.substr(0, pos);
		if(counter == 3)
			var3 = s.substr(0, pos);
		if(counter == 4)
			var4 = s.substr(0, pos);
		if(counter == 5)
			var5 = s.substr(0, pos);


	    //token = s.substr(0, pos);
	    //serialized_str.push_back(token);
	    s.erase(0, pos + delimiter.length());
	    counter++;
	}
	var6 = s;

std::cout << var1 << std::endl;
std::cout << var2 << std::endl;
std::cout << var3 << std::endl;
std::cout << var4 << std::endl;
std::cout << var5 << std::endl;
std::cout << var6 << std::endl;

Vehicle veh =  Vehicle(var2,var3);
std::cout << veh.GetOwner() << std::endl;

return 0;
}