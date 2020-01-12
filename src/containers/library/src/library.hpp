#ifndef ELEC_AS_CPP_LIBRARY
#define ELEC_AS_CPP_LIBRARY

#include <string>
#include <vector>
#include "book.hpp"
#include "customer.hpp"

class Library {
public:
    /* Library:
    * the constructor of the Library class, takes following parameters:
    *  - the library's name (const reference to string)
    * Remember to also initialize books and customers in the constructor!
    */
    Library(const std::string& name);

    /* GetName:
    * returns the library's name as a string, takes no parameters.
    * This function should not alter the Library object's state, in other words the function should be const.
    */
    const std::string& GetName() const;

    /* GetBooks:
    * returns the Library's books as a reference to a vector<Book>, takes no parameters.
    */
    std::vector<Book>& GetBooks();

    /* GetCustomers:
    * returns the Library's customers as a reference to a vector<Customer>, takes no parameters.
    */
    std::vector<Customer>& GetCustomers();

    /* FindBookByName:
    * returns a Book, takes a const reference to a string as a parameter.
    */
    Book FindBookByName(const std::string& name);

    /* FindBooksByAuthor:
    * returns a vector of Books, takes a const reference to a string as a parameter.
    */
    std::vector<Book> FindBooksByAuthor(const std::string& author);

    /* FindAllLoanedBooks():
    * returns a vector of Books, takes no parameters.
    */
    std::vector<Book> FindAllLoanedBooks();

    /* FindCustomer:
    * returns a Customer, takes a const reference to a string representing the Customer's id as a parameter.
    */
    Customer FindCustomer(const std::string& number);

private:
    /* Make variables for:
    * name (string)
    * books (vector<Book>)
    * customers (vector<Customer>)
    */
    std::string name_;
    std::vector<Book> books_;
    std::vector<Customer> customers_;
};

#endif
