#pragma once

#include "bird.hpp"

/* TODO: Duck class.
 * It has a constructor that takes a string as a parameter, which is the duck's name.
 * When Speak is called a duck should say:
<name>: QUACK\n
 * into the stream given as a parameter.
 *
 * Due to the simplicity of the classes, all member functions are 
 * implemented in this header file.
*/

class Duck : public Bird {
public:
	Duck(const std::string& name): Bird(name) { }
	virtual void Speak(std::ostream& os) const {
	os << GetName() << ": " << "QUACK" << std::endl;
	}
};

