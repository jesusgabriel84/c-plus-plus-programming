#pragma once

#include <string>
#include <iostream>

#include "vehicle.hpp"

class Aircraft : public Vehicle {
public:
    /* constructor
     * Initializes the corresponing members from the parameters.
    */
    Aircraft(std::string register_number, std::string owner, std::string model, double wingspan, unsigned int cruise_speed);
    
    /* Write
     * Writes the vehicle to the stream given as a parameter in the serialized format.
     * Format for AirCraft:
A;<register number>;<owner>;<model>;<wingspan>;<cruise_speed>\n
    */
    void Write(std::ostream& stream);
    
    /* Print
     * Writes the vehicle to the standard output in the serialized format (See Write).
    */
    void Print();
    
    /* Read
     * Reads an Aircraft from the stream given as parameter, assuming that the vehicle
     * is stored in the serialized format (See Write) and starts immediately from 
     * the current position of the stream.
     * If the vehicle type (the first character) is wrong, returns NULL.
     * If the read was succesful, returns a pointer to a new Aircraft contructed with 
     * the data read. 
    */
    static Aircraft* Read(std::istream& stream);

private:
    std::string model_;
    double wingspan_;
    unsigned int cruise_speed_;
};