#pragma once
#include <iostream>

/* TODO: abstract class StringPrinter
 * ------------
 * Description:
 * A class that works as a base class for different string printers.
 * ------------
 * Functions:
 * 
 * A single constructor that takes std::ostream& as a parameter with the 
 * default value std::cout to which the function call operator prints.
 *
 * Clone: a function that copies the object and returns a StringPrinter pointer.
 *
 * Function call operator (operator()) overload, i.e. this base class is 
 *  a function object:
 *    - Takes one std::string argument (the string should not be modified).
 *    - Prints out the string in the format specified in the child class's
 *      specification to the ostream that was given in the constructor.
 *    - Returns a reference to the StringPrinter object meaning that this
 *      function call operation can be "chained", e.g.
 *      object("First")("Second")("Third");
 * ------------
 * Protected members:
 *  An std::ostream reference to the output stream
 * ------------
 * Other:
 * Do not forget the virtual destructor.
 * As to what functions should be pure virtual (this is an abstract class after all)
 * is left for you to figure out.
 */

class StringPrinter {
public:
    
    
    /* Construct a new object */
    explicit StringPrinter(std::ostream &os = std::cout) : os_(os) { }

    //Virtual destructor
    virtual ~StringPrinter() {}

    /* Copy this object */
    StringPrinter* Clone() const {
        return new StringPrinter(os_);
    }

    /*Overloading operator*/
    virtual StringPrinter& operator()(const std::string& str) {
        os_ << str << std::endl;
        return *this;
    }

//private:
	std::ostream& os_;
};
