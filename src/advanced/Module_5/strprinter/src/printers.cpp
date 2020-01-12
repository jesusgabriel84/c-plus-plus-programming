#include "string_printer.hpp"
#include "printers.hpp"
#include <string>
#include <list>
#include <utility>
#include <memory>

//Copy constructor
Printers::Printers(Printers& sp)
{
	collection_ = sp.collection_;
}

//Add function
void Printers::Add(const std::string& name, StringPrinter* sp)
{
	for (std::list<std::pair<std::string, std::shared_ptr<StringPrinter>>>::const_iterator it = collection_.begin(); it != collection_.end(); it++) 
	    if(it->first == name)
	    	throw std::invalid_argument("Duplicate index");

	if(sp == nullptr)
		throw std::invalid_argument("Invalid printer");

	this->collection_.emplace_back(name,sp);
}

//Indexing operators
StringPrinter& Printers::operator[](const std::string& name) const
{
	for (std::list<std::pair<std::string, std::shared_ptr<StringPrinter>>>::const_iterator it = collection_.begin(); it != collection_.end(); it++) 
	    if(it->first == name)
	    	return *(it->second);

	throw std::invalid_argument("Unknown index");
}

//Copy a ssignment operator
Printers& Printers::operator=(Printers &sp)
{
	this->~Printers();
	collection_ = sp.collection_;
	return *this;
}