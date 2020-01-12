#pragma once

#include <string>
#include <iostream>

#include "vehicle.hpp"

class Boat : public Vehicle {
public:
    /* constructor
     * Initializes the corresponing members from the parameters.
    */
    Boat(std::string register_number, std::string owner, std::string name, double draft, double power);
    
    /* Write
     * Writes the vehicle to the stream given as a parameter in the serialized format.
     * Format for Car:
B;<register number>;<owner>;<name>;<draft>;<power>\n
    */
    void Write(std::ostream& stream);
    
    /* Print
     * Writes the vehicle to the standard output in the serialized format (See Write).
    */
    void Print();
    
    /* Read
     * Reads a Boat from the stream given as parameter, assuming that the vehicle
     * is stored in the serialized format (See Write) and starts immediately from 
     * the current position of the stream.
     * If the vehicle type (the first character) is wrong, returns NULL.
     * If the read was succesful, returns a pointer to a new Boat contructed with 
     * the data read. 
    */
    static Boat* Read(std::istream& stream);

private:
    std::string name_;
    double draft_;
    double power_;
};