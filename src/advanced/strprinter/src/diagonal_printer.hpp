#pragma once
#include "string_printer.hpp"

/* TODO: class DiagonalPrinter
 * ------------
 * Description:
 * A class that is used to print strings diagonally (see below).
 * The class inherits (public inheritance) class StringPrinter.
 * ------------
 * Functions:
 * 
 * A constructor that takes three parameters:
 *  - The first line, which is "" by default, i.e. it is not printed at all
 *  - The last line, which is "" by default, i.e. it is not printed at all either
 *  - A reference to the output stream, which is std::cout by default
 * 
 * Overrides the necessary members from the base class.
 * ------------
 * Other:
 * DiagonalPrinter prints a string diagonally. For the string "like this":
<first line>\n
l        \n
 i       \n
  k      \n
   e     \n
         \n
     t   \n
      h  \n
       i \n
        s\n
<last line>\n
 * where <first line> and <last line> are replaced by the strings given in the
 * constructor. If the first line is empty, it is not printed. The same applies
 * to the last line.
 */

class DiagonalPrinter : public StringPrinter {
public:
	

    /* Construct a new object - pass the std::ostream& to the base class */
    DiagonalPrinter(const std::string& first = "", const std::string& last = "", std::ostream &os = std::cout);

    virtual StringPrinter& operator()(const std::string& str) ;

    virtual ~DiagonalPrinter() {}
    
private:
	std::string first_;
	std::string last_;
};