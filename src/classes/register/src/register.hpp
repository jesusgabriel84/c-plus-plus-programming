#pragma once

#include <string>
#include <ostream>
#include <vector>
#include <iostream>
#include <fstream>

#include "vehicle.hpp"

class Register {
public:
    /* destructor
     * Does what destuctors should.
    */
    ~Register() {
    for(auto it : vehicles_) 
        delete it;
    }
    
    /* Add
     * Adds the parameter to the vehicle vector
    */
    void Add(Vehicle* v);
    
    /* Save
     * Saves the vehicles to the file named by the parameter with each vehicle on its
     * own line in the serialized format.
    */
    void Save(const std::string& filename) const;
    
    /* ReadLine
     * Reads a vehicle from the stream given as a parameter assuming a serialized format, and 
     * adds it to the register. Reads a whole line from the stream whether or not constructing 
     * the vehicle was succesful.
     * Returns true if a vehicle was added, false otherwise.
    */
    bool ReadLine(std::istream& stream);
    
    /* Load
     * Reads all vehicles from a file and adds them to the register.
     * Each vehicle is on a different line. On an error the line is discarded and reading is
     * continued from the next line.
     * Returns the number of vehicles added.
    */
    int Load(const std::string& filename);
    
    /* Print
     * Prints all the vehicles in the register to the standard output each on a different line
     * in the serialized format.
    */
    void Print();
    
    /* Size
     * Returns the number of vehicles in the register.
    */
    size_t Size() const;

private:
    std::vector<Vehicle*> vehicles_;
};
