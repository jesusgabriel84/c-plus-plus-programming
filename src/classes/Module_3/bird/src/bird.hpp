#pragma once

#include <string>
#include <ostream>
#include <vector>
#include <iostream>

/*
 * BIRD CLASS
 * 
 * This class does not need modifications.
 */
class Bird {
public:
  
    // Constructor (explicit, we want to avoid implicit typecasts from string)
    explicit Bird(const std::string& name) : name_(name) {}
    
    // We use implicit copy constructor and assignment operator.
    
    // Virtual - this class may be derived from
    virtual ~Bird() {}
    
    // All birds can fly, or at least the birds we are implementing
    // in this exercise.
    //
    // Notice that flying is not a const member function -
    // const birds cannot fly! They can only speak.
    void Fly(std::ostream& os) { os << name_ << " flies!" << std::endl; }
    
    // How birds speak is defined by their genus (it is implemented in
    // the derived classes)
    virtual void Speak(std::ostream& os) const = 0;
    
    // Returns the name of the bird.
    std::string GetName() const {
        return name_;
    }
  
private:
    std::string name_;
};
