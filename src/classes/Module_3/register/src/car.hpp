#pragma once

#include <string>
#include <iostream>

#include "vehicle.hpp"

class Car : public Vehicle {
public:
    /* constructor
     * Initializes the corresponing members from the parameters.
    */
    Car(std::string register_number, std::string owner, std::string maker, unsigned int range, bool inspection);
    
    /* Write
     * Writes the vehicle to the stream given as a parameter in the serialized format.
     * Format for Car:
C;<register number>;<owner>;<maker>;<range>;<inspection>\n
     * where <inspection> is 1 or 0 when inspection_ is true or false, respectively.
    */
    void Write(std::ostream& stream);
    
    /* Print
     * Writes the vehicle to the standard output in the serialized format (See Write).
    */
    void Print();
    
    /* Read
     * Reads a Car from the stream given as parameter, assuming that the vehicle
     * is stored in the serialized format (See Write) and starts immediately from 
     * the current position of the stream.
     * If the vehicle type (the first character) is wrong, returns NULL.
     * If the read was succesful, returns a pointer to a new Car contructed with 
     * the data read. 
    */
    static Car* Read(std::istream& stream);

private:
    std::string maker_;
    unsigned int range_;
    bool inspection_;
};

