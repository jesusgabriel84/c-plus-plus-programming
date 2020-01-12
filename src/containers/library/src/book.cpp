#include "book.hpp"
#include <string>
#include <ctime>
#include <iostream>

Book::Book(const std::string& name, const std::string& author, const std::string& ISBN, bool status, Date date)
	: name_(name), author_(author), isbn_(ISBN), loaned_(status), due_date_(date) {}

const std::string& Book::GetName() const
{
	return name_;
}

const std::string& Book::GetAuthor() const
{
	return author_;
}

std::string Book::GetISBN() const
{
	return isbn_;
}

bool Book::GetStatus() const
{
	return loaned_;
}

Date Book::GetDueDate() const
{
	return due_date_;
}

bool Book::Loan()
{
	due_date_ = Date::Today();

	if(due_date_.month == 12)
	{
		due_date_.month = 1;
		due_date_.year++;
	}
	else
	{
		due_date_.month++;
	}
	loaned_ = true;
	return loaned_;
}

void Book::Restore()
{
	due_date_ = {0,0,0};
	loaned_ = false;
}

void Book::Print() const
{
	std::cout << "Book: " << name_ << ", author: " << author_ << ", ISBN: " << isbn_ << ", loaned " << (loaned_? "true" : "false") << ", due date: " << due_date_.day <<"." << due_date_.month << "." << due_date_.year << std::endl;
}