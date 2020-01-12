#pragma once
#include "string_printer.hpp"

/* TODO: class StandardPrinter
 * ------------
 * Description:
 * A minimal StringPrinter implementation with no special functionality.
 * ------------
 * Functions:
 * A constructor that takes a single parameter:
 *  - A reference to the output stream, which is std::cout by default
 * 
 * Overrides the necessary members from the base class.
 * ------------
 * Other:
 * StandardPrinter prints a string like one normally would but with a 
 * newline at the end. For the string "like this":
like this\n
*/

class StandardPrinter : public StringPrinter {
public:


    /* Construct a new object - pass the std::ostream& to the base class */
    StandardPrinter(std::ostream &os = std::cout);

    virtual ~StandardPrinter() {}

    virtual StringPrinter& operator()(const std::string& str) ;

private:
};