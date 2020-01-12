#include <iterator>
#include <sstream>
#include <stdexcept>
#include "standard_printer.hpp"

StandardPrinter::StandardPrinter(std::ostream &os) 
	: StringPrinter(os) { }

StringPrinter& StandardPrinter::operator()(const std::string& str) 
{
    os_ << str << std::endl;
    return *this;
}

