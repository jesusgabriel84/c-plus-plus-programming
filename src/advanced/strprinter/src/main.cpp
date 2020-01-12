#include <iterator>
#include <sstream>
#include <stdexcept>

#include "printers.hpp"
#include "standard_printer.hpp"
#include "diagonal_printer.hpp"
#include "string_printer.hpp"

class ReversePrinter : public StringPrinter {
public:
    /* Construct a new object - pass the std::ostream& to the base class */
    ReversePrinter(std::ostream &os = std::cout) : StringPrinter(os) { }
    /* Copy this object */
    ReversePrinter* Clone() const {
        return new ReversePrinter(os_);
    }
    virtual StringPrinter& operator()(const std::string& str) {
        /* os is a protected member of the base class */
        std::copy(str.rbegin(), str.rend(), std::ostream_iterator<char>(os_));
        os_ << std::endl;
        return *this;
    }
private:
};

void msg(const std::string& line) {
    std::cout << "===" << line << std::endl;
}

int main() {
    Printers printers1;
    std::ostringstream oss1;
    std::ostringstream oss2;

    msg("Adding a StandardPrinter");
    printers1.Add("normal", new StandardPrinter);
    msg("Adding a StandardPrinter with a non-default stream");
    printers1.Add("normal-oss", new StandardPrinter(oss1));

    msg("Adding a ReversePrinter");
    printers1.Add("reverse", new ReversePrinter());

    msg("Adding a DiagonalPrinter");
    printers1.Add("diagonal1", new DiagonalPrinter());
    msg("Adding a DiagonalPrinter with non-default parameters");
    printers1.Add("diagonal2", new DiagonalPrinter(">>First<<", ">>Last<<", oss2));

    msg("Testing the printers");
    printers1["normal"]("StandardPrinter output");
    printers1["reverse"]("ReversePrinter output");
    printers1["diagonal1"]("Diagonal!");
    printers1["diagonal2"]("Diagonal to !cout!");
    printers1["normal-oss"]("Some more output");

    msg("Printing output from the non-cout streams");
    std::cout << oss1.str() << oss2.str();

    msg("Testing chaining");
    printers1["normal"]("One line")("Two lines")("Three lines..");

    msg("Testing the exceptions");
    msg("Testing existing name");
    try {
	    printers1.Add("normal", (StringPrinter*)0xdeadbeef);
    }
    catch(std::invalid_argument) {
        msg("Caught the correct exception");
    }
    catch(...) {
	    msg("Caught some other exception");
    }

    msg("Testing a null function");
    try {
	    printers1.Add("brand new", (StringPrinter*)0);
    }
    catch(std::invalid_argument) {
        msg("Caught the correct exception");
    }
    catch(...) {
	    msg("Caught some other exception");
    }

    msg("Testing that the previous operation did not change the object");
    try {
	    printers1.Add("brand new", new StandardPrinter());
    }
    catch(...) {
	    msg("Caught an unexpected exception");
    }

    msg("Testing a non-existant name");
    try {
        printers1["fluffy"];
    }
    catch(std::invalid_argument) {
        msg("Caught the correct exception");
    }
    catch(...) {
	    msg("Caught some other exception");
    }

    msg("Testing the copy and assignment of Printers");


    //Printers printers2(printers1);
    //Printers printers3(printers1);
    //Printers printers3;
    //printers3 = printers1;

    /*msg("Testing operations on the copies");
    printers2["normal"]("Copy constructed");
    printers2["reverse"]("Copy constructed again");
    printers3["normal"]("Assigned");
    printers3["reverse"]("Assigned again");*/

    msg("Terminating");
}

