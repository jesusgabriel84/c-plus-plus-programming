//

#include <iostream>
#include "book.hpp"
#include "customer.hpp"
#include "library.hpp"
#include <string>
#include <vector>


Library::Library(const std::string& name)
	: name_(name)
	{
		std::vector<Book> books;
		books_ = books;
		std::vector<Customer> customers;
		customers_ = customers;
	}


const std::string& Library::GetName() const
{
	return name_;
}

std::vector<Book>& Library::GetBooks()
{
	return books_;
}

std::vector<Customer>& Library::GetCustomers()
{
	return customers_;
}

Book Library::FindBookByName(const std::string& name)
{
	Book find_book = Book("","","");
	for(unsigned int i = 0; i < books_.size(); i++)
	{
		if(books_[i].GetName() == name)
		{
			find_book = books_[i];
		}
	}
	return find_book;
}

std::vector<Book> Library::FindBooksByAuthor(const std::string& author)
{
	std::vector<Book> books_list;
	for(unsigned int i = 0; i < books_.size(); i++)
	{
		if(books_[i].GetAuthor() == author)
		{
			books_list.push_back(books_[i]);
		}
	}
	return books_list;
}

std::vector<Book> Library::FindAllLoanedBooks()
{
	std::vector<Book> loaned_books;
	for(unsigned int i = 0; i < books_.size(); i++)
	{
		if(books_[i].GetStatus() == true)
		{
			loaned_books.push_back(books_[i]);
		}
	}
	return loaned_books;
}

Customer Library::FindCustomer(const std::string& number)
{
	Customer find_customer = Customer("","");
	for(unsigned int i = 0; i < customers_.size(); i++)
	{
		if(customers_[i].GetID() == number)
		{
			find_customer = customers_[i];
		}
	}
	return find_customer;
}