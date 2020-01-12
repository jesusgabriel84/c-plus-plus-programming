#pragma once

#include "bird.hpp"

/* TODO: Owl class.
 * It has a constructor that takes a string as a parameter, which is the owl's name.
 * When Speak is called an owl should say
<name>: WHUU\n
 * into the stream given as a parameter.
 *
 * Due to the simplicity of the classes, all member functions are 
 * implemented in this header file.
*/

class Owl : public Bird {
public:
	Owl(const std::string& name): Bird(name) { }
	virtual void Speak(std::ostream& os) const {
	os << GetName() << ": " << "WHUU" << std::endl;
	}
};

