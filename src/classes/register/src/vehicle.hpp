#pragma once

#include <string>

class Vehicle {
public:
    /* constructor
     * Initializes the corresponing members from the parameters.
    */
    explicit Vehicle(std::string register_number, std::string owner);
    
    virtual ~Vehicle() {};
    
    /* GetRegisterNumber
     * Returns the register number.
    */
    std::string GetRegisterNumber() const;
    
    /* GetOwner
     * Returns the owner.
    */
    std::string GetOwner() const;
    
    /* Write
     * Writes the vehicle to the stream given as a parameter in the serialized format
     * for that vehicle.
     * Note: this is a pure virtual method.
    */
    virtual void Write(std::ostream& stream) = 0;
    
    /* Print
     * Writes the vehicle to the standard output in the serialized format for that vehicle.
     * Note: this is a pure virtual method.
    */
    virtual void Print() = 0;
    
private:
    std::string register_number_;
    std::string owner_;
};


