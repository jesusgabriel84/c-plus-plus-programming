#include <string>

class Car {
public:
	Car(unsigned int score, const std::string& name) 
		: score_(score), name_(name) {}
	
	std::string GetName() {
		return name_;
	}

	unsigned int score_;
private:
	std::string name_;
};