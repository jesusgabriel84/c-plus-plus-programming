#include "customer.hpp"
#include <string>
#include <vector>
#include <iostream>


Customer::Customer(const std::string& name, const std::string& number)
	: name_(name),number_(number)
	{
		std::vector<Book> book_list;
		book_list_ = book_list;
	}

const std::string& Customer::GetName() const
{
	return name_;
}

const std::string& Customer::GetID() const
{
	return number_;
}

int Customer::GetLoanAmount() const
{
	return book_list_.size();
}

const std::vector<Book>& Customer::GetLoans() const
{
	return book_list_;
}

bool Customer::LoanBook(Book& book)
{
	// First validate if the book is not loaned so it can be assigned to the customer
	if(book.GetStatus() == true)
	{
		return false;
	}
	else
	{
		book.Loan();
		book_list_.push_back(book);
		return true;
	}
	
}

void Customer::ReturnBook(Book& book)
{
	unsigned int pos = 0;

	for(unsigned int i = 0; i < book_list_.size(); i++)
	{
		if(book.GetName() == book_list_[i].GetName())
		{
			pos = i;
		}
	}

	book_list_.erase(book_list_.begin() + pos);
	book.Restore();

}

void Customer::Print() const
{
	std::cout << "Customer: " << name_ <<", " << number_ << ", has " << GetLoanAmount() << " books on loan:" << std::endl;
	for(unsigned int i = 0; i < book_list_.size(); i++)
	{
			std::cout << "- ";
			book_list_[i].Print();	
	}
	
}