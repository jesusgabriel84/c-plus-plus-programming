#include <string>

class Car {
public:
	Car(unsigned int w_score, const std::string& w_name) : 
		score_(w_score),
		name_(w_name) {}
		
	std::string GetName() {
		return name_;
	}

	unsigned int score_;
private:
	std::string name_;
};