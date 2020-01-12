#include "poly.hpp"

#include <sstream>
#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <vector>

int Poly::operator[](int exp) const {
    Values::const_iterator it = values_.find(exp);
    return it == values_.end() ? 0 : it->second;
}

Poly operator+(const Poly& a, const Poly& b)
{

	Poly c;

	int degree_a = 0;
	int degree_b = 0;

	//Obtaining the degree of polynomial 'a'
	for(auto it = a.begin(); it != a.end(); it++)
	{
		if(it->first > degree_a)
		{
			degree_a = it->first;
		}
	}

	//Obtaining the degree of polynomial 'b'
	for(auto it2 = b.begin(); it2 != b.end(); it2++)
	{
		if(it2->first > degree_b)
		{
			degree_b = it2->first;
		}
	}

	if(degree_a > degree_b)
	{
		for(int i = 0; i <= degree_a; i++)
		{
			if(a[i] != 0 || b[i] != 0)
			{
				c[i] = a[i] + b[i];
			}
			
		}
	}
	else
	{
		for(int i = 0; i <= degree_b; i++)
		{
			if(a[i] != 0 || b[i] != 0)
			{
				c[i] = a[i] + b[i];
			}
		}
	}
	
	return c;
}


Poly operator-(const Poly& p)
{
	Poly p1;
	for(auto it = p.begin(); it != p.end(); it++)
	{
		p1[it->first] = (-1)*(it->second);
	}

	return p1;
}

Poly& Poly::operator+=(const Poly& b)
{
	values_ = b.values_;
	return *this;
}

Poly& Poly::operator-=(const Poly& b)
{
	values_ = b.values_;
	return *this;
}


Poly operator-(const Poly& a, const Poly& b)
{
	Poly c;
	int degree_a = 0;
	int degree_b = 0;

	//Obtaining the degree of polynomial 'a'
	for(auto it = a.begin(); it != a.end(); it++)
	{
		if(it->first > degree_a)
		{
			degree_a = it->first;
		}
	}

	//Obtaining the degree of polynomial 'b'
	for(auto it2 = b.begin(); it2 != b.end(); it2++)
	{
		if(it2->first > degree_b)
		{
			degree_b = it2->first;
		}
	}

	if(degree_a > degree_b)
	{
		for(int i = 0; i <= degree_a; i++)
		{
			if(a[i] != 0 || b[i] != 0)
			{
				c[i] = a[i] - b[i];
			}
			
		}
	}
	else
	{
		for(int i = 0; i <= degree_b; i++)
		{
			if(a[i] != 0 || b[i] != 0)
			{
				c[i] = a[i] - b[i];
			}
		}
	}

	
	return c;
}

bool operator<(const Poly& a, const Poly& b)
{
	
	
	int degree_a = 0;
	int degree_b = 0;

	//Obtaining the degree of polynomial 'a'
	for(auto it = a.begin(); it != a.end(); it++)
	{
		if(it->first > degree_a)
		{
			degree_a = it->first;
		}
	}

	//Obtaining the degree of polynomial 'b'
	for(auto it2 = b.begin(); it2 != b.end(); it2++)
	{
		if(it2->first > degree_b)
		{
			degree_b = it2->first;
		}
	}


	if(degree_a == degree_b)
	{
		return a[degree_a] < b[degree_b];
	}
	else
	{
		return degree_a < degree_b;
	}


}

bool operator==(const Poly& a, const Poly& b)
{
	int degree_a = 0;
	int degree_b = 0;

	//Obtaining the degree of polynomial 'a'
	for(auto it = a.begin(); it != a.end(); it++)
	{
		if(it->first > degree_a)
		{
			degree_a = it->first;
		}
	}

	//Obtaining the degree of polynomial 'b'
	for(auto it2 = b.begin(); it2 != b.end(); it2++)
	{
		if(it2->first > degree_b)
		{
			degree_b = it2->first;
		}
	}

	if(degree_b == degree_a)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool operator>(const Poly& a, const Poly& b)
{
	int degree_a = 0;
	int degree_b = 0;

	//Obtaining the degree of polynomial 'a'
	for(auto it = a.begin(); it != a.end(); it++)
	{
		if(it->first > degree_a)
		{
			degree_a = it->first;
		}
	}

	//Obtaining the degree of polynomial 'b'
	for(auto it2 = b.begin(); it2 != b.end(); it2++)
	{
		if(it2->first > degree_b)
		{
			degree_b = it2->first;
		}
	}

	if(degree_a == degree_b)
	{
		return a[degree_a] > b[degree_b];
	}
	else
	{
		return degree_a > degree_b;
	}
}

bool operator!=(const Poly& a, const Poly& b)
{
	int degree_a = 0;
	int degree_b = 0;

	//Obtaining the degree of polynomial 'a'
	for(auto it = a.begin(); it != a.end(); it++)
	{
		if(it->first > degree_a)
		{
			degree_a = it->first;
		}
	}

	//Obtaining the degree of polynomial 'b'
	for(auto it2 = b.begin(); it2 != b.end(); it2++)
	{
		if(it2->first > degree_b)
		{
			degree_b = it2->first;
		}
	}

	if(degree_b != degree_a)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::istream& operator>>(std::istream& is, Poly& p)
{

	std::string poly_input, mon;
	unsigned int i = 0;
	std::vector<std::string> mon_v;
	std::vector<int> numbers;
	is >> poly_input;

	while(i < poly_input.size())
	{
		while(poly_input[i] != 'x' && i < poly_input.size())
		{
			mon.push_back(poly_input[i]);
			i++;
		}

		mon_v.push_back(mon);
		mon.clear();
		i++;

	}
	
	if(mon_v.size() > 0)
	{

	unsigned int ii = 0;
	numbers.push_back(stoi(mon_v[0]));
	for(unsigned int j = 1; j<mon_v.size()-1; j++)
	{

			while(mon_v[j][ii] != '+' && mon_v[j][ii] != '-')
			{
				mon.push_back(mon_v[j][ii]);
				ii++;
			}
			numbers.push_back(stoi(mon));
			mon.clear();

			while(ii < mon_v[j].size())
			{
				mon.push_back(mon_v[j][ii]);
				ii++;
			}
			numbers.push_back(stoi(mon));
			mon.clear();

			ii = 0;
		
	}

	numbers.push_back(stoi(mon_v[mon_v.size()-1]));


	for(unsigned int iii = 0; iii < numbers.size(); iii+=2)
	{
		if(numbers[iii] != 0)
		p[numbers[iii+1]] = numbers[iii];
	}

	}

    return is;
}

std::ostream& operator<<(std::ostream& os, const Poly& p)
{
	auto it = p.begin();
    for(; it != p.end(); it++)
    {
    	if(it == p.begin() && it->second != 0)
    	{
    		os << it->second << "x" << it->first;
    	}
    	else
    	{
    		if(it->second < 0)
    		{
    			os << it->second << "x" << it->first;
    		}
    		if(it->second > 0)
    		{
    			os << "+" << it->second  << "x" << it->first;
    		}
    	}
    	
    }
    return os;
}