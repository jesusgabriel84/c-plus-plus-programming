#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <cstddef>

#include <gcheck.h>
#include <redirectors.h>
#include "../src/book.hpp"
#include "../src/customer.hpp"
#include "../src/library.hpp"

std::string GenerateISBN() {
    srand(time(0));
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr1(100, 999); // define the range
    std::uniform_int_distribution<> distr2(100, 999); // define the range
    std::string s = "978-0-"+std::to_string(distr1(eng))+"-"+std::to_string(distr2(eng))+"-2";
    return s;
}

Date GetCurrentDate() {
    Date d;
    std::time_t t = time(0);
    struct tm * now = localtime(&t);
    d.day=now->tm_mday;
    d.month=now->tm_mon+1;
    d.year=now->tm_year+1900;
    return d;
}

Date GetCurrentDatePlusMonth() {
    Date d = GetCurrentDate();
    d.month++;
    return d;
}

bool operator==(const Date& d, const Date& d2) {
    return d.day == d2.day && d.month == d2.month && d.year == d2.year;
}

bool operator==(const Book& b, const Book& b2) {
    return b.GetAuthor() == b2.GetAuthor() 
        && b.GetDueDate() == b2.GetDueDate() 
        && b.GetISBN() == b2.GetISBN() 
        && b.GetName() == b2.GetName() 
        && b.GetStatus() == b2.GetStatus();
}

std::string to_string(const Date& d) {
    return  std::to_string(d.day) + "." + std::to_string(d.month) + "." + std::to_string(d.year);
}
std::string to_string(const Book& b) {
    return  b.GetAuthor() + ": " + b.GetName() + ", due: " + to_string(b.GetDueDate()) + ", isbn: " + b.GetISBN() + ", status: " + (b.GetStatus() ? "true" : "false");
}

PREREQ_TEST(Book, constructor, 0.5, 0) {
    Book book("name", "author", "isbn");
    Book book2("name", "author", "isbn", true, {1,1,1});
}

PREREQ_TEST(Book, getters, 2, 1) {
    Book book("The C++ programming language", "Stroustrup, Bjarne", "978-0-321-56384-2", false, {1,1,1});
    Book book2("C++ Primer", "Lippman, Stanley B.", "978-0-321-71411-4", true, {2,2,2});
    
    EXPECT_EQ("Stroustrup, Bjarne", book.GetAuthor());
    EXPECT_EQ("Lippman, Stanley B.", book2.GetAuthor());
    
    EXPECT_EQ("978-0-321-56384-2", book.GetISBN());
    EXPECT_EQ("978-0-321-71411-4", book2.GetISBN());
    
    EXPECT_FALSE(book.GetStatus());
    EXPECT_TRUE(book2.GetStatus());
    
    EXPECT_EQ(Date({1,1,1}), book.GetDueDate());
    EXPECT_EQ(Date({2,2,2}), book2.GetDueDate());
}

PREREQ_TEST(Book, Loan_Restore, 2, 2) {
    Book book("The C++ programming language", "Stroustrup, Bjarne", "978-0-321-56384-2");
    
    book.Loan();
    EXPECT_EQ(GetCurrentDatePlusMonth(), book.GetDueDate());
    EXPECT_TRUE(book.GetStatus());
    
    book.Restore();
    EXPECT_EQ(Date({0,0,0}), book.GetDueDate());
    EXPECT_FALSE(book.GetStatus());
}

PREREQ_TEST(Book, Print, 1, 2) {
    Book book("The C++ programming language", "Stroustrup, Bjarne", "978-0-321-56384-2");
    Book book2("C++ Primer", "Lippman, Stanley B.", "978-0-321-71411-4", true, {1, 10, 2019});
    
    gcheck::StdoutCapturer tout;
    
    book.Print();
    std::string book1_Print = tout.str();
    
    book2.Print();
    std::string book2_Print = tout.str();
    
    std::string correct1 = "Book: The C++ programming language, author: Stroustrup, Bjarne, ISBN: 978-0-321-56384-2, loaned false, due date: 0.0.0\n"; //TODO: date
    std::string correct2 = "Book: C++ Primer, author: Lippman, Stanley B., ISBN: 978-0-321-71411-4, loaned true, due date: 1.10.2019\n";
    
    EXPECT_EQ(correct1, book1_Print);
    EXPECT_EQ(correct2, book2_Print);
}

PREREQ_TEST(Customer, constructor, 0.5, 10) {
    Customer("Pertti", "10");
}

PREREQ_TEST(Customer, GetName_ID, 2, 11) {
    Customer customer("Pertti Kovanen", "45647658657");
    Customer customer2("Satu Kivinen", "95871034857");
    
    EXPECT_EQ("Pertti Kovanen", customer.GetName());
    EXPECT_EQ("Satu Kivinen", customer2.GetName());
    
    EXPECT_EQ("45647658657", customer.GetID());
    EXPECT_EQ("95871034857", customer2.GetID());
    
    EXPECT_EQ(0, customer.GetLoans().size());
    EXPECT_EQ(0, customer2.GetLoans().size());
    
    EXPECT_EQ(0, customer.GetLoanAmount());
    EXPECT_EQ(0, customer2.GetLoanAmount());
}

PREREQ_TEST(Customer, LoanBook, 1, 12) {
    Book book("The C++ programming language", "Stroustrup, Bjarne", "978-0-321-56384-2");
    Book book2("C++ Primer", "Lippman, Stanley B.", "978-0-321-71411-4");
    Customer customer("Pertti Kovanen", "45647658657");
    
    EXPECT_EQ(0, customer.GetLoans().size());
    EXPECT_EQ(0, customer.GetLoanAmount());
    
    customer.LoanBook(book);
    ASSERT_TRUE(1 == customer.GetLoanAmount());
    EXPECT_EQ(book, customer.GetLoans()[0]);
    
    customer.LoanBook(book2);
    ASSERT_TRUE(2 == customer.GetLoanAmount());
    EXPECT_EQ(book2, customer.GetLoans()[1]);
}

PREREQ_TEST(Customer, ReturnBook, 1, 13) {
    GradingMethod(gcheck::AllOrNothing);
    
    Book book("The C++ programming language", "Stroustrup, Bjarne", "978-0-321-56384-2");
    Book book2("C++ Primer", "Lippman, Stanley B.", "978-0-321-71411-4");
    Customer customer("Pertti Kovanen", "45647658657");
    
    customer.LoanBook(book);
    customer.LoanBook(book2);
    
    customer.ReturnBook(book);
    ASSERT_TRUE(1 == customer.GetLoanAmount());
    EXPECT_EQ(book2, customer.GetLoans()[0]);
    
    customer.ReturnBook(book2);
    EXPECT_EQ(0, customer.GetLoanAmount());
}

PREREQ_TEST(Customer, Print, 1, 13) {
    Customer customer("Pertti Kovanen", "45647658657");
    Customer customer2("Satu Kivinen", "95871034857");
    Book book("The C++ programming language", "Stroustrup, Bjarne", "978-0-321-56384-2");
    Book book2("C++ Primer", "Lippman, Stanley B.", "978-0-321-71411-4");
    Book book3("C++ For Dummies", "Stephen Randy Davis", "978-1-118-82377-4");
    
    gcheck::StdoutCapturer tout;
    
    customer.Print();
    std::string customer1_Print = tout.str();
    
    customer.LoanBook(book);
    customer.Print();
    std::string customer1_Print2 = tout.str();
    
    customer2.LoanBook(book);
    customer2.LoanBook(book2);
    customer2.LoanBook(book3);
    customer2.Print();
    std::string customer2_Print = tout.str();
    
    std::string loan_date = to_string(GetCurrentDatePlusMonth());
    std::string book1str = "Book: The C++ programming language, author: Stroustrup, Bjarne, ISBN: 978-0-321-56384-2, loaned true, due date: " + loan_date + "\n";
    std::string book2str = "Book: C++ Primer, author: Lippman, Stanley B., ISBN: 978-0-321-71411-4, loaned true, due date: " + loan_date + "\n";
    std::string book3str = "Book: C++ For Dummies, author: Stephen Randy Davis, ISBN: 978-1-118-82377-4, loaned true, due date: " + loan_date + "\n";
    
    std::string correct1 = "Customer: Pertti Kovanen, 45647658657, has 0 books on loan:\n";
    std::string correct1_2 = "Customer: Pertti Kovanen, 45647658657, has 1 books on loan:\n" 
        "- " + book1str;
    std::string correct2 = "Customer: Satu Kivinen, 95871034857, has 2 books on loan:\n" 
        "- " + book2str
        + "- " + book3str;
    
    EXPECT_EQ(correct1, customer1_Print);
    EXPECT_EQ(correct1_2, customer1_Print2);
    EXPECT_EQ(correct2, customer2_Print);
}

PREREQ_TEST(Library, constructor, 0.5, 20) {
    Library library("Test Library");
}

PREREQ_TEST(Library, GetBooks, 1, 21) {
    Book book("The C++ programming language", "Stroustrup, Bjarne", "978-0-321-56384-2");
    Book book2("C++ Primer", "Lippman, Stanley B.", "978-0-321-71411-4");
    auto i = GenerateISBN();
    auto i2 = GenerateISBN();
    Book book3("Test book", "Test author", i);
    Book book4("Test book2", "Test author", i2);

    Library library("Test Library");
    auto& books = library.GetBooks();
    books.push_back(book);
    books.push_back(book2);
    books.push_back(book3);
    books.push_back(book4);

    EXPECT_EQ(book.GetName(), books[0].GetName());
    EXPECT_EQ(book2.GetName(), books[1].GetName());
    EXPECT_EQ(book3.GetName(), books[2].GetName());
    EXPECT_EQ(book4.GetName(), books[3].GetName());
}

PREREQ_TEST(Library, GetCustomers, 1, 21) {
    Customer customer("Pertti Kovanen", "45647658657");
    Customer customer2("Satu Kivinen", "95871034857");
    Library library("Test Library");
    auto& customers = library.GetCustomers();
    customers.push_back(customer);
    customers.push_back(customer2);

    EXPECT_EQ(customer.GetName(), customers[0].GetName());
    EXPECT_EQ(customer2.GetName(), customers[1].GetName());
}

PREREQ_TEST(Library, FindBookByName, 1, 22) {
    Book book("The C++ programming language", "Stroustrup, Bjarne", "978-0-321-56384-2");
    Book book2("C++ Primer", "Lippman, Stanley B.", "978-0-321-71411-4");
    auto i = GenerateISBN();
    auto i2 = GenerateISBN();
    Book book3("Test book", "Test author", i);
    Book book4("Test book2", "Test author", i2);

    Library library("Test Library");
    auto& books = library.GetBooks();
    books.push_back(book);
    books.push_back(book2);
    books.push_back(book3);
    books.push_back(book4);

    EXPECT_EQ(book2.GetISBN(), library.FindBookByName("C++ Primer").GetISBN());
    EXPECT_EQ(book3.GetISBN(), library.FindBookByName("Test book").GetISBN());
}

PREREQ_TEST(Library, FindBooksByAuthor, 1, 22) {
    Book book("The C++ programming language", "Stroustrup, Bjarne", "978-0-321-56384-2");
    Book book2("C++ Primer", "Lippman, Stanley B.", "978-0-321-71411-4");
    auto i = GenerateISBN();
    auto i2 = GenerateISBN();
    Book book3("Test book", "Test author", i);
    Book book4("Test book2", "Test author", i2);

    Library library("Test Library");
    auto& books = library.GetBooks();
    books.push_back(book);
    books.push_back(book2);
    books.push_back(book3);
    books.push_back(book4);

    EXPECT_EQ(book3.GetISBN(), library.FindBooksByAuthor("Test author")[0].GetISBN());
    EXPECT_EQ(book4.GetISBN(), library.FindBooksByAuthor("Test author")[1].GetISBN());
}

PREREQ_TEST(Library, FindAllLoanedBooks, 1, 22) {
    Book book("The C++ programming language", "Stroustrup, Bjarne", "978-0-321-56384-2");
    Book book2("C++ Primer", "Lippman, Stanley B.", "978-0-321-71411-4");
    auto i = GenerateISBN();
    auto i2 = GenerateISBN();
    Book book3("Test book", "Test author", i);
    Book book4("Test book2", "Test author", i2);

    Customer customer("Pertti Kovanen", "45647658657");
    Customer customer2("Satu Kivinen", "95871034857");
    
    customer.LoanBook(book2);
    customer2.LoanBook(book4);

    Library library("Test Library");
    auto& books = library.GetBooks();
    books.push_back(book);
    books.push_back(book2);
    books.push_back(book3);
    books.push_back(book4);

    std::vector<Customer>& customers = library.GetCustomers();
    customers.push_back(customer);
    customers.push_back(customer2);

    ASSERT_TRUE(2 == library.FindAllLoanedBooks().size());
    
    EXPECT_EQ(book2.GetISBN(), library.FindAllLoanedBooks()[0].GetISBN());
    EXPECT_EQ(book4.GetISBN(), library.FindAllLoanedBooks()[1].GetISBN());
}

PREREQ_TEST(Library, FindCustomer, 1, 22) {
    Customer customer("Pertti Kovanen", "45647658657");
    Customer customer2("Satu Kivinen", "95871034857");
    Customer customer3("Santeri Sankala", "95576031857");
    Library library("Test Library");
    std::vector<Customer>& v = library.GetCustomers();
    v.push_back(customer);
    v.push_back(customer2);
    v.push_back(customer3);

    EXPECT_EQ(customer.GetName(), library.FindCustomer("45647658657").GetName());
    EXPECT_EQ(customer3.GetName(), library.FindCustomer("95576031857").GetName());
    EXPECT_EQ(customer2.GetName(), library.FindCustomer("95871034857").GetName());
}
