#include <iterator>
#include <sstream>
#include <stdexcept>
#include "diagonal_printer.hpp"

std::string Spaces(unsigned int count)
{
	std::string result = "";
	for(unsigned int i = 0; i < count; i++)
		result += " ";
	return result;
}

DiagonalPrinter::DiagonalPrinter(const std::string& first, const std::string& last, std::ostream &os)
	:  StringPrinter(os)
	{ 
		first_ = first;
		last_ = last;
	}

StringPrinter& DiagonalPrinter::operator()(const std::string& str) 
{
	if(first_ != "")
		os_ << first_ << std::endl;

	for(unsigned int i = 0; i < str.size(); i++)
		os_ << Spaces(i) << str[i] << Spaces(str.size() - i - 1) << std::endl;

	if(last_ != "")
		os_ << last_ << std::endl;

	return *this;
}